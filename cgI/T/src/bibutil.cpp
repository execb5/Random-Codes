//*****************************************************
//
// bibutil.cpp
// Biblioteca de rotinas auxiliares que inclui funções
// para realizar as seguintes tarefas:
// - Normalizar um vetor;
// - Calcular o produto vetorial entre dois vetores;
// - Calcular um vetor normal a partir de três vértices;
// - Rotacionar um vértice ao redor de um eixo (x, y ou z);
// - Ler um modelo de objeto 3D de um arquivo no formato
//		OBJ e armazenar em uma estrutura;
// - Desenhar um objeto 3D recebido por parâmetro;
// - Liberar a memória ocupada por um objeto 3D;
// - Calcular o vetor normal de cada face de um objeto 3D;
// - Decodificar e armazenar numa estrutura uma imagem JPG
//		para usar como textura;
// - Armazenar em uma estrutura uma imagem JPG para usar
//		como textura.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objetiva"
//
// (Levemente modificado por Rossana Baptista Queiroz)
//*****************************************************

#include <string.h>
#include "bibutil.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define DEBUG

using namespace std;

// Lista de objetos
vector<OBJ*> _objetos(0);

// Lista de materiais
vector<MAT*> _materiais(0);

// Lista de texturas
vector<TEX*> _texturas(0);

// Modo de desenho
char _modo = 't';

// Variáveis para controlar a taxa de quadros por segundo
int _numquadro =0, _tempo, _tempoAnterior = 0;
float _ultqps = 0;

//Flags
bool desenhaNormais = false;

void setaDesenhaNormais(bool flag) {
    desenhaNormais = flag;
}

#ifndef __FREEGLUT_EXT_H__
// Função para desenhar um texto na tela com fonte bitmap
void glutBitmapString(void *fonte,const unsigned char *texto) {
    // Percorre todos os caracteres
    while (*texto)
        glutBitmapCharacter(fonte, *texto++);
}
#endif

// Calcula e retorna a taxa de quadros por segundo
float CalculaQPS(void) {
    // Incrementa o contador de quadros
    _numquadro++;

    // Obtém o tempo atual
    _tempo = glutGet(GLUT_ELAPSED_TIME);
    // Verifica se passou mais um segundo
    if (_tempo - _tempoAnterior > 1000) {
        // Calcula a taxa atual
        _ultqps = _numquadro*1000.0/(_tempo - _tempoAnterior);
        // Ajusta as variáveis de tempo e quadro
        _tempoAnterior = _tempo;
        _numquadro = 0;
    }
    // Retorna a taxa atual
    return _ultqps;
}

// Escreve uma string na tela, usando uma projeção ortográfica
// normalizada (0..1, 0..1)
void Escreve2D(float x, float y, const unsigned char *str) {
    glMatrixMode(GL_PROJECTION);
    // Salva projeção perspectiva corrente
    glPushMatrix();
    glLoadIdentity();
    // E cria uma projeção ortográfica normalizada (0..1,0..1)
    gluOrtho2D(0,1,0,1);

    glMatrixMode(GL_MODELVIEW);
    // Salva modelview corrente
    glPushMatrix();
    glLoadIdentity();

    // Posiciona no canto inferior esquerdo da janela
    glRasterPos2f(x,y);
    glColor3f(0,0,0);
    // "Escreve" a mensagem
    glutBitmapString(GLUT_BITMAP_9_BY_15,str);

    glMatrixMode(GL_PROJECTION);
    // Restaura a matriz de projeção anterior
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    // ... e a modelview anterior
    glPopMatrix();
}

// Normaliza o vetor recebido por parâmetro.
void Normaliza(VERT &norm) {
    float tam = sqrt(norm.x*norm.x
                     +norm.y*norm.y
                     +norm.z*norm.z);
    if (tam == 0) return;
    norm.x /= tam;
    norm.y /= tam;
    norm.z /= tam;
}

// Rotina que recebe dois vetores e retorna por parâmetro,
// através de vresult, o produto vetorial entre eles.
void ProdutoVetorial (VERT &v1, VERT &v2, VERT &vresult) {
    vresult.x = v1.y * v2.z - v1.z * v2.y;
    vresult.y = v1.z * v2.x - v1.x * v2.z;
    vresult.z = v1.x * v2.y - v1.y * v2.x;
}

// Esta rotina recebe três vértices coplanares e calcula
// o vetor normal a eles (n).
void VetorNormal(VERT vert1, VERT vert2, VERT vert3, VERT &n) {
    VERT vet1, vet2;

    vet1.x = vert1.x - vert2.x;
    vet1.y = vert1.y - vert2.y;
    vet1.z = vert1.z - vert2.z;
    vet2.x = vert3.x - vert2.x;
    vet2.y = vert3.y - vert2.y;
    vet2.z = vert3.z - vert2.z;
    ProdutoVetorial(vet2, vet1, n);
    Normaliza(n);
}

// Rotaciona um vértice em torno de Z por <ang> graus
void RotaZ(VERT &in, VERT &out, float ang) {
    float arad = ang*M_PI/180.0;
    out.x =  in.x * cos(arad) + in.y * sin(arad);
    out.y = -in.x * sin(arad) + in.y * cos(arad);
    out.z =  in.z;
}

// Rotaciona um vértice em torno de Y por <ang> graus
void RotaY(VERT &in, VERT &out, float ang) {
    float arad = ang*M_PI/180.0;
    out.x = in.x * cos(arad) - in.z * sin(arad);
    out.y = in.y;
    out.z = in.x * sin(arad) + in.z * cos(arad);
}

// Rotaciona um vértice em torno de X por <ang> graus
void RotaX(VERT &in, VERT &out, float ang) {
    float arad = ang*M_PI/180.0;
    out.x =  in.x;
    out.y =  in.y * cos(arad) + in.z * sin(arad);
    out.z = -in.y * sin(arad) + in.z * cos(arad);
}

// Função interna, usada por CarregaObjeto para
// interpretar a definição de uma face em um
// arquivo .OBJ
//
// Recebe um apontador para a posição corrente na
// string e devolve o valor numérico encontrado
// até o primeiro / ou -1 caso não exista
//
// Também retorna em sep o separador encontrado
int leNum(char **face, char *sep) {
    char temp[10];
    int pos = 0;
    while (**face) {
        if (**face == '/' || **face==' ') { // achamos o separador
            *sep = **face;
            (*face)++;
            break;
        }
        temp[pos++] = **face;
        (*face)++;
    }
    temp[pos]=0;
    if (!pos) // string vazia ?
        return -1;
    return atoi(temp);
}

// Procura um material pelo nome na lista e devolve
// o índice onde está, ou -1 se não achar
int _procuraMaterial(string nome) {
    unsigned int i;
    for (i=0;i<_materiais.size();++i)
        if (nome == _materiais[i]->nome)
            return i;
    return -1;
}

// Procura um material pelo nome e devolve um
// apontador para ele ou NULL caso não ache
MAT *ProcuraMaterial(string nome) {
    int pos = _procuraMaterial(nome);
    if (pos == -1) return NULL;
    else return _materiais[pos];
}

// Procura uma textura pelo nome na lista e devolve
// o índice onde está, ou -1 se não achar
int _procuraTextura(string nome) {
    unsigned int i;
    for (i=0;i<_texturas.size();++i)
        if (nome == _texturas[i]->nome)
            return i;
    return -1;
}

// Lê um arquivo que define materiais para um objeto 3D no
// formato .OBJ
void _leMateriais(string nomeArquivo, string caminho, bool mipmap) {
    string aux;
    ifstream fp;
    MAT *ptr;
    TEX *texPtr;

    string nomeCompleto = caminho+nomeArquivo;

    //cout << "_leMateriais >>> " << nomeCompleto << endl;

    fp.open(nomeCompleto.c_str(), ios::in);

    if (!fp.is_open()) {
        cout << "Erro na leitura do arquivo de materiais!" << endl;
        return;
    }

    /* Especificação do arquivo de materiais (.mtl):
     *
     * #,!,$  - comentário
     * newmtl - nome do novo material(sem espaços)
     * Ka	  - Cor ambiente, especificada como 3 floats
     * Kd	  - Cor difusa, idem
     * Ks	  - Cor especular, idem
     * Ns	  - Coeficiente de especularidade, entre 0 and 1000
     *          (convertido para a faixa válida em OpenGL (0..128) durante a leitura)
     * d	  - Transparência - mesmo significado que o alpha em OpenGL: 0.0 a 1.0 (0.0 = transparente)
     *
     * Os demais campos são ignorados por este leitor:
     * Tr	  - Transparência (0 = opaco, 1 = transparente)
     * map_Kd - Especifica arquivo com a textura a ser mapeada como material difuso
     * refl	  - Especifica arquivo com um mapa de reflexão
     * Ni	  - Índice de refração, 1.0 ou maior, onde 1.0 representa sem refração
     * bump	  - Especifica arquivo para "bump mapping"
     * illum  - Modelo de iluminação (1 = apenas cores, 2 = textura, 3 = reflexões e raytracing)
     * map_Ka - Especifica arquivo com a textura a ser mapeada como cor ambiente
     * map_Ks - Especifica arquivo com a textura a ser mapeada como cor especular
     * map_Ns - Especifica arquivo com a textura a ser mapeada como reflexão especular
     * map_d  - Especifica arquivo cmo a textura a ser mapeada como transparência (branco é opaco, preto é transparente)
     *
     */

    while (fp.good()) {
        getline(fp, aux);


        if (fp.fail()) break;

		std::cout << "aux = \"" << aux << "\" size = " << aux.size() << "\n";

		if (aux.size() == 0) continue;
        //if (aux.size()>1)
        if (aux[aux.size()-1] == '\r')
            aux = aux.substr(0, aux.size()-1);	// elimina o \r lido do arquivo

        //cout << "_leMateriais: " << aux << endl;

        if (aux[0]=='#') continue;
		if (aux[0]=='\0') continue;
        if (aux.substr(0,6) == "newmtl") { // Novo material ?
            // Se material já existe na lista, pula para o
            // próximo
            string nomeMat = aux.substr(7);
            if (_procuraMaterial(nomeMat)!=-1) {
                ptr = NULL;
                continue;
            }
            ptr = new MAT;
            if (ptr == NULL) {
                printf("Sem memória para novo material!"); getchar();
                exit(1);
            }
            //cout << "Novo material" << endl;
            // Adiciona à lista
            _materiais.push_back(ptr);
            // Copia nome do material
            ptr->nome = nomeMat;
            // Não existe "emission" na definição do material
            // mas o valor pode ser setado mais tarde,
            // via SetaEmissaoMaterial(..)
            ptr->ke[0] = ptr->ke[1] = ptr->ke[2] = 0.0;
        }
        if (aux.substr(0,3) == "Ka ") { // Ambiente
            if (ptr==NULL) continue;
            istringstream aux_a(aux.substr(3));
            aux_a >> ptr->ka[0] >> ptr->ka[1] >> ptr->ka[2];
        }
        if (aux.substr(0,3) == "Kd ") { // Difuso
            if (ptr==NULL) continue;
            istringstream aux_d(aux.substr(3));
            aux_d >> ptr->kd[0] >> ptr->kd[1] >> ptr->kd[2];
        }
        if (aux.substr(0,3) == "Ks ") { // Especular
            if (ptr==NULL) continue;
            istringstream aux_s(aux.substr(3));
            aux_s >> ptr->ks[0] >> ptr->ks[1] >> ptr->ks[2];
        }
        if (aux.substr(0,3) == "Ns ") { // Fator de especularidade
            if (ptr==NULL) continue;
            istringstream aux_n(aux.substr(3));
            aux_n >> ptr->spec;
            // Converte da faixa lida (0...1000) para o intervalo
            // válido em OpenGL (0...128)
            ptr->spec = ptr->spec/1000.0 * 128;
        }
        if (aux.substr(0,2) == "d ") { // Alpha
            if (ptr==NULL) continue;
            // Não existe alpha na definição de cada componente
            // mas o valor é lido em separado e vale para todos
            istringstream aux_a(aux.substr(3));
            float alpha;
            aux_a >> alpha;
            ptr->ka[3] = alpha;
            ptr->kd[3] = alpha;
            ptr->ks[3] = alpha;
        }
        if (aux.substr(0,7) == "map_Kd ") { // textura
            if (ptr==NULL) continue;
            texPtr = CarregaTextura(caminho+aux.substr(7), mipmap);
            ptr->texid = texPtr->texid;
        }
    }

    if (fp.bad() || !fp.eof()) {
        cout << "Erro de leitura!" << endl; getchar();
        exit(1);
    }

    fp.close();
}

// Extrai e retorna o diretório contido em um pathname
// Usado pelas funções de leitura de objetos, materiais e texturas
string ObtemCaminho(string nomeArq) {
    string::size_type pos = nomeArq.find_last_of('/');

    // Se não encontrar, retorna uma string vazia
    if (pos == string::npos)
        return "";

    // Caso contrário, retorna a string até este ponto
    return nomeArq.substr(0,pos+1);
}

// Cria e carrega um objeto 3D que esteja armazenado em um
// arquivo no formato OBJ, cujo nome é passado por parâmetro.
// É feita a leitura do arquivo para preencher as estruturas
// de vértices e faces, que são retornadas através de um OBJ.
//
// O parâmetro mipmap indica se deve-se gerar mipmaps a partir
// das texturas (se houver)
OBJ *CarregaObjeto(string nomeArquivo, bool mipmap) {
    int i;
    //int vcont,ncont,fcont,tcont;
    int material, texid;
    ifstream fp1, fp;
    int vertOffset, normOffset, texcoordOffset;
    TEX *ptr;
    OBJ *obj;
    MESH *mesh;
    string aux;

    // Zera os offsets (usados para ler mais objetos com
    // mais de um modelo)
    vertOffset = normOffset = texcoordOffset = 0;

    string caminho = ObtemCaminho(nomeArquivo);

    // Abre arquivo texto para leitura
    fp1.open(nomeArquivo.c_str(), ios::in);

    // Se houver erro, retorna NULL
    if (!fp1.is_open())
        return NULL;

#ifdef DEBUG
    cout << "*** Objeto: " << nomeArquivo << endl;
#endif

    /* Especificação do formato .obj para objetos poligonais:
     *
     * # - commentário
     * v x y z - vértice
     * vn x y z - normal
     * vt x y z - texcoord
     * f a1 a2 ... - face com apenas índices de vértices
     * f a1/b1/c1 a2/b2/c2 ... - face com índices de vértices, normais e texcoords
     * f a1//c1 a2//c2 ... - face com índices de vértices e normais (sem texcoords)
     *
     * Campos ignorados:
     * g nomegrupo1 nomegrupo2... - especifica que o objeto é parte de um ou mais grupos
     * s numerogrupo ou off - especifica um grupo de suavização ("smoothing")
     * o nomeobjeto: define um nome para o objeto
     *
     * Biblioteca de materiais e textura:
     * mtllib - especifica o arquivo contendo a biblioteca de materiais
     * usemtl - seleciona um material da biblioteca
     * usemat - especifica o arquivo contendo a textura a ser mapeada nas próximas faces
     *
     */

    obj = new OBJ;
    if (obj == NULL)
        return NULL;

    mesh = NULL;

    // A princípio não temos normais por vértice...
    obj->normais_por_vertice = false;
    // E também não temos materiais...
    obj->tem_materiais = false;
    obj->textura = -1;  // sem textura associada

    fp.open(nomeArquivo.c_str(), ios::in);

    // Material corrente = nenhum
    material = -1;
    // Textura corrente = nenhuma
    texid = -1;

    // Utilizadas para determinar os limites do objeto
    // em x,y e z
    float minx,miny,minz;
    float maxx,maxy,maxz;



    while (fp.good()) {
        getline(fp, aux);
        if (fp.fail()) break;



        // Se houver um \r no final da linha, remove
        if (aux[aux.size()-1] == '\r')
            aux = aux.substr(0,aux.size()-1);



        // Pula comentários
        if (aux[0]=='#') continue;
		if (aux[0]==' ') continue;

        // Novo modelo ?
        if (aux.substr(0,2) == "g ") {
            // Mesh não vazio ? Significa que já foi lido


            if (mesh != NULL) {
                // Mostra os dados carregados

#ifdef DEBUG
                cout << "Vertices: " << mesh->vertices.size() << endl;
                cout << "Faces:    " << mesh->faces.size() << endl;
                cout << "Normais:  " << mesh->normais.size() << endl;
                cout << "Texcoords:" << mesh->texcoords.size() << endl;
#endif
                // Ajusta os offsets...
                vertOffset += mesh->vertices.size();
                normOffset += mesh->normais.size();
                texcoordOffset += mesh->texcoords.size();
            }



            // E cria novo
            mesh = new MESH();
            if (mesh == NULL)
                return NULL;


            // Adiciona a mesh vazia ao objeto
            obj->meshes.push_back(mesh);
            // Obtém id do novo modelo e armazena
            string id = aux.substr(2);
            mesh->id = id;
            cout << "Novo modelo: " << id << endl;
        }

        // Definição da biblioteca de materiais ?
        if (aux.substr(0,6) == "mtllib") {

            // Chama função para ler e interpretar o arquivo
            // que define os materiais
            _leMateriais(aux.substr(7),caminho,mipmap);

            // Indica que o objeto possui materiais
            obj->tem_materiais = true;
        }

        // Seleção de material ?
        if (aux.substr(0,6) == "usemtl") {
            // Procura pelo nome e salva o índice para associar
            // às próximas faces
            material = _procuraMaterial(aux.substr(7));
            if (material == -1) {
                cout << "Erro! Material " << aux.substr(7) << " não encontrado!" << endl;
                return NULL;
            }
            texid = _materiais[material]->texid;
        }
        // Seleção de uma textura (.jpg)
        if (aux.substr(0,6) == "usemat") {
            // Às vezes, é especificado o valor (null) como textura
            // (especialmente em se tratando do módulo de exportação
            // do Blender)
            if (aux.substr(7) == "(null)") {
                texid = -1;
                continue;
            }
            // Tenta carregar a textura
            ptr = CarregaTextura(caminho+aux.substr(7), mipmap);
            texid = ptr->texid;
        }
        // Vértice ?
        if (aux.substr(0,2) == "v ") {
            // Se não temos um mesh, cria e dá um nome
            // genérico
            if (mesh == NULL) {
                mesh = new MESH();
                if (mesh == NULL)
                    return NULL;
                mesh->id = "objeto";
                obj->meshes.push_back(mesh);
            }
            istringstream auxv(aux.substr(2));
            VERT vaux;
            auxv >> vaux.x >> vaux.y >> vaux.z;
            mesh->vertices.push_back(vaux);
            //cout << "Vértices: " << mesh->vertices[vcont].x << " " << mesh->vertices[vcont].y << " " << mesh->vertices[vcont].z << endl;

            if (mesh->vertices.size() == 1) {
                minx = maxx = mesh->vertices[0].x;
                miny = maxy = mesh->vertices[0].y;
                minz = maxz = mesh->vertices[0].z;
            } else {
                if (vaux.x < minx) minx = vaux.x;
                if (vaux.y < miny) miny = vaux.y;
                if (vaux.z < minz) minz = vaux.z;
                if (vaux.x > maxx) maxx = vaux.x;
                if (vaux.y > maxy) maxy = vaux.y;
                if (vaux.z > maxz) maxz = vaux.z;
            }
        }
        // Normal ?
        if (aux.substr(0,3) == "vn ") {
            istringstream auxn(aux.substr(3));
            VERT naux;
            auxn >> naux.x >> naux.y >> naux.z;
            mesh->normais.push_back(naux);
//            auxn >> mesh->normais[ncont].x >> mesh->normais[ncont].y >> mesh->normais[ncont].z;
            // Registra que o arquivo possui definição de normais por
            // vértice
            obj->normais_por_vertice = true;
        }
        // Texcoord ?
        if (aux.substr(0,3) == "vt ") {
            istringstream auxt(aux.substr(3));
            TEXCOORD taux;
            auxt >> taux.s >> taux.t >> taux.r;
            mesh->texcoords.push_back(taux);
//            auxt >> mesh->texcoords[tcont].s >> mesh->texcoords[tcont].t >> mesh->texcoords[tcont].r;
        }
        // Face ?
        // f 1/2/3 3/4/5 5/7/8
        if (aux.substr(0,2) == "f ") {
            // Pula "f "

            istringstream auxface(aux.substr(2));

            //cout << "FACE: " << auxface.str() << endl;

            // Associa à face o índice do material corrente, ou -1 se
            // não houver
            FACE faux;
            faux.mat = material;
//			mesh->faces[fcont].mat = material;

            // Associa à face o texid da textura selecionada ou -1 se
            // não houver
            //mesh->faces[fcont].texid = texid;

            // Temporários para armazenar os índices desta face
            int vi[100],ti[100],ni[100];

            faux.nv = 0;

            int nv = 0;
            bool tem_t = false;
            bool tem_n = false;

            // Interpreta a descrição da face
            string face;
            // Enquanto houver vértices:
            while (getline(auxface, face, ' ')) {
                //cout << "Vértice: " << face << endl;

                istringstream auxvert(face);
                string vert;
                int pos = 0;
                while (getline(auxvert, vert, '/')) {
                    //cout << "Token: " << vert << " (" << vert.size() << ")" << endl;
					//if (vert.size()){
                    switch (pos) {
                    case 0: // índice do vértice
                        vi[nv] = atoi(vert.c_str());
                        break;
                    case 1: // índice da texcoord
                        ti[nv] = atoi(vert.c_str());
                        tem_t  = true;
                        break;
                    case 2: // índice da normal
                        ni[nv] = atoi(vert.c_str());
                        tem_n  = true;
                    }
                    pos++;
					//}
                }
                //cout << "facevert: " << vi[nv] << "/" << ti[nv] << "/" << ni[nv] << endl;
                // Prepara para próximo vértice
                nv++;
            }
            // Fim da face, aloca memória para estruturas e preenche com
            // os valores lidos
            faux.nv = nv;
            faux.vert.resize(nv);
            // Só aloca memória para normais e texcoords se for necessário
            if (tem_n) faux.norm.resize(nv); //(int *) malloc(sizeof(int)*nv);
            if (tem_t) faux.tex.resize(nv); //(int *) malloc(sizeof(int)*nv);
            // Copia os índices dos arrays temporários para a face
            for (i=0;i<nv;++i) {
                // Subtraímos -1 dos índices porque o formato OBJ começa
                // a contar a partir de 1, não 0
                //
                // Também subtraímos os offsets atuais (se houver mais
                // de um modelo no .obj)
                faux.vert[i] = vi[i]-1-vertOffset;
                if (tem_n) faux.norm[i] = ni[i]-1-normOffset;
                if (tem_t) faux.tex[i]  = ti[i]-1-texcoordOffset;
            }
            // Inclui a face no modelo
            mesh->faces.push_back(faux);
        }
    }

    if (fp.bad() || !fp.eof()) {
        cout << "Erro de leitura!!!" << endl;
        return NULL;
    }

    cout << "Vertices: " << mesh->vertices.size() << endl;
    cout << "Faces:    " << mesh->faces.size() << endl;
    cout << "Normais:  " << mesh->normais.size() << endl;
    cout << "Texcoords:" << mesh->texcoords.size() << endl;

#ifdef DEBUG
    cout << "Limites: " << minx << " " << miny << " " << minz
    << " - " << maxx << " " << maxy << " " << maxz << endl;
#endif
    // Fim, fecha arquivo e retorna apontador para objeto
    fp.close();

    // Adiciona na lista
    _objetos.push_back(obj);
    return obj;
}

// Seta o modo de desenho a ser utilizado para os objetos
// 'w' - wireframe
// 's' - sólido
// 't' - sólido + textura
void SetaModoDesenho(char modo) {
    if (modo!='w' && modo!='s' && modo!='t') return;
    _modo = modo;
}

void DesenhaMesh(MESH* mesh, bool temMateriais, bool normaisPorVertice, GLint textura) {
    int i;	// contador
    GLint ult_texid, texid;	// última/atual textura
    GLenum prim = GL_POLYGON;	// tipo de primitiva
    GLfloat branco[4] = { 1.0, 1.0, 1.0, 1.0 };	// constante para cor branca

    if (mesh->dlist >= 1000)
        glNewList(mesh->dlist-1000,GL_COMPILE_AND_EXECUTE);
    // Ou chama a display list já associada...
    else if (mesh->dlist > -1) {
        glCallList(mesh->dlist);
        return;
    }

    // Seleciona GL_LINE_LOOP se o objetivo
    // for desenhar o objeto em wireframe
    if (_modo=='w') prim = GL_LINE_LOOP;

    // Salva atributos de iluminação e materiais
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_TEXTURE_2D);
    // Se objeto possui materiais associados a ele,
    // desabilita COLOR_MATERIAL - caso contrário,
    // mantém estado atual, pois usuário pode estar
    // utilizando o recurso para colorizar o objeto
    if (temMateriais)
        glDisable(GL_COLOR_MATERIAL);

    // Armazena id da última textura utilizada
    // (por enquanto, nenhuma)
    ult_texid = -1;
    // Varre todas as faces do objeto
    for (i=0; i<mesh->faces.size(); i++) {
        // Usa normais calculadas por face (flat shading) se
        // o objeto não possui normais por vértice
        //if (!normaisPorVertice) {
        //    glNormal3f(mesh->normais[i].x,mesh->normais[i].y,mesh->normais[i].z);
            //std::cout << "Não possui normais por vértice!\n";
        //}
        //else std::cout << "Possui normais por vértice!\n";
        // Existe um material associado à face ?
        if (mesh->faces[i].mat != -1) {
            // Sim, envia parâmetros para OpenGL
            int mat = mesh->faces[i].mat;
            glMaterialfv(GL_FRONT,GL_AMBIENT,_materiais[mat]->ka);
            // Se a face tem textura, ignora a cor difusa do material
            // (caso contrário, a textura é colorizada em GL_MODULATE)
            if (_materiais[mesh->faces[i].mat]->texid != -1 && _modo == 't')
                //if(mesh->faces[i].texid != -1 && _modo=='t')
                glMaterialfv(GL_FRONT,GL_DIFFUSE,branco);
            else
                glMaterialfv(GL_FRONT,GL_DIFFUSE,_materiais[mat]->kd);
            glMaterialfv(GL_FRONT,GL_SPECULAR,_materiais[mat]->ks);
            glMaterialfv(GL_FRONT,GL_EMISSION,_materiais[mat]->ke);
            glMaterialf(GL_FRONT,GL_SHININESS,_materiais[mat]->spec);
        }

        // Se o objeto possui uma textura associada, utiliza
        // o seu texid ao invés da informação em cada face
        if (textura != -1)
            texid = textura;
        //else
            // Lê o texid associado à face (-1 se não houver)
        //    texid = _materiais[mesh->faces[i].mat]->texid;
        //texid = mesh->faces[i].texid;

        // Se a última face usou textura e esta não,
        // desabilita
        if (texid == -1 && ult_texid != -1)
            glDisable(GL_TEXTURE_2D);

        // Ativa texturas 2D se houver necessidade
        if (texid != -1 && texid != ult_texid && _modo=='t') {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,texid);
        }

        // Inicia a face
        glBegin(prim);
        // Para todos os vértices da face
        for (int vf=0; vf<mesh->faces[i].nv;++vf) {
            // Se houver normais definidas para cada vértice,
            // envia a normal correspondente
			//cout << "aqui mesmo?\n";
            if (normaisPorVertice){
				//cout << mesh->normais.size() << "\n";
				//cout << mesh->normais[mesh->faces[i].norm[vf]].x << "," << mesh->normais[mesh->faces[i].norm[vf]].y << "," << mesh->normais[mesh->faces[i].norm[vf]].z << "\n";
                glNormal3f(mesh->normais[mesh->faces[i].norm[vf]].x,
                           mesh->normais[mesh->faces[i].norm[vf]].y,
                           mesh->normais[mesh->faces[i].norm[vf]].z);

			}
            // Se houver uma textura associada...
			//cout << mesh->texcoords.size() << "\n";
            if (texid!=-1 && mesh->texcoords.size())
                // Envia as coordenadas associadas ao vértice
                glTexCoord2f(mesh->texcoords[mesh->faces[i].tex[vf]].s,
                             mesh->texcoords[mesh->faces[i].tex[vf]].t);
            // Envia o vértice em si
			//cout << mesh->vertices.size() << "\n";
            glVertex3f(mesh->vertices[mesh->faces[i].vert[vf]].x,
                       mesh->vertices[mesh->faces[i].vert[vf]].y,
                       mesh->vertices[mesh->faces[i].vert[vf]].z);
        }
        // Finaliza a face
        glEnd();

        // Finalmente, desabilita as texturas
        glDisable(GL_TEXTURE_2D);

        if (desenhaNormais && normaisPorVertice) {

            float fator = 5.0;
            // Inicia a face - desenho das normais
            glBegin(GL_LINES);
            // Para todos os vértices da face
            for (int vf=0; vf<mesh->faces[i].nv;++vf) {

                //glPushMatrix();
                //glColor3f(0.0,0.0,0.0);
                float vx = mesh->vertices[mesh->faces[i].vert[vf]].x;
                float vy = mesh->vertices[mesh->faces[i].vert[vf]].y;
                float vz = mesh->vertices[mesh->faces[i].vert[vf]].z;

                glVertex3f(vx,vy,vz);

                float vx2 = fator*mesh->normais[mesh->faces[i].norm[vf]].x + vx;
                float vy2 = fator*mesh->normais[mesh->faces[i].norm[vf]].y + vy;
                float vz2 = fator*mesh->normais[mesh->faces[i].norm[vf]].z + vz;

                glVertex3f(vx2,vy2,vz2);
                //glPopMatrix();
            }
            // Finaliza as normais
            glEnd();
        }

        // Finalmente, desabilita as texturas
        glEnable(GL_TEXTURE_2D);

        // Salva a última texid utilizada
        ult_texid = texid;
    } // fim da varredura de faces


    // Restaura os atributos de iluminação e materiais
    glPopAttrib();

    // Se for uma nova display list...
    if (mesh->dlist >= 1000) {
        // Finaliza a display list
        glEndList();
        // E armazena a identificação correta
        mesh->dlist-=1000;
    }
}

// Desenha um objeto 3D passado como parâmetro.
// (desenha todos os modelos)
void DesenhaObjeto(OBJ *obj) {
    for (int o=0; o<obj->meshes.size(); o++) {
        // Obtém a mesh
        MESH* mesh = obj->meshes[o];
        // Gera nova display list se for o caso
        DesenhaMesh(mesh,false,false);
    }
}

// Função interna para liberar a memória ocupada
// por um objeto
void _liberaObjeto(OBJ *obj) {
    // Para cada mesh...
    for (int o=0; o<obj->meshes.size(); o++) {
        MESH* mesh = obj->meshes[o];
        delete mesh;
    }
    // Finalmente, libera a estrutura principal
    delete obj;
}

// Libera memória ocupada por um objeto 3D
void LiberaObjeto(OBJ *obj) {
    unsigned int o;
    if (obj==NULL) {	// se for NULL, libera todos os objetos
        for (o=0;o<_objetos.size();++o)
            _liberaObjeto(_objetos[o]);
        _objetos.clear();
    } else {
        // Procura pelo objeto no vector
        vector<OBJ*>::iterator it = _objetos.begin();
        for (it = _objetos.begin(); it<_objetos.end(); ++it)
            // e sai do loop quando encontrar
            if (*it == obj)
                break;
        // Apaga do vector
        _objetos.erase(it);
        // E libera as estruturas internas
        _liberaObjeto(obj);
    }
}

// Libera memória ocupada pela lista de materiais e texturas
void LiberaMateriais() {
    unsigned int i;
#ifdef DEBUG
    printf("Total de materiais: %d\n",_materiais.size());
#endif
    // Para cada material
    for (i=0;i<_materiais.size();++i) {
#ifdef DEBUG
        cout << _materiais[i]->nome << " a: (" << _materiais[i]->ka[0] << "," << _materiais[i]->ka[1] << "," << _materiais[i]->ka[2]
        << " d: (" << _materiais[i]->kd[0] << "," << _materiais[i]->kd[1] << "," << _materiais[i]->kd[2]
        << " e: (" << _materiais[i]->ke[0] << "," << _materiais[i]->ke[1] << "," << _materiais[i]->ke[2]
        << " - " << _materiais[i]->spec << endl;
#endif
        // Libera material
        delete _materiais[i];
    }
    // Limpa lista
    _materiais.clear();
#ifdef DEBUG
    printf("Total de texturas: %d\n",_texturas.size());
#endif
    // Para cada textura
    for (i=0;i<_texturas.size();++i) {
        // Libera textura - não é necessário liberar a imagem, pois esta já
        // foi liberada durante a carga da textura - ver CarregaTextura
#ifdef DEBUG
        printf("%s: %d x %d (id: %d)\n",_texturas[i]->nome.c_str(),_texturas[i]->dimx,
               _texturas[i]->dimy,_texturas[i]->texid);
#endif
        delete _texturas[i];
    }
    // Limpa lista
    _texturas.clear();
}

// Calcula o vetor normal de cada face de uma mesh
void CalculaNormaisPorFace(MESH * mesh) {
    // Aloca memória para as normais (uma por face)
    mesh->normais.clear();
    mesh->normais.resize(mesh->faces.size());
    // Varre as faces e calcula a normal, usando os 3 primeiros vértices de
    // cada uma
    for (int i=0; i<mesh->faces.size(); i++)
        VetorNormal(mesh->vertices[mesh->faces[i].vert[0]],
                    mesh->vertices[mesh->faces[i].vert[1]],
                    mesh->vertices[mesh->faces[i].vert[2]],mesh->normais[i]);
}

// Calcula o vetor normal de cada face de um objeto 3D.
void CalculaNormaisPorFace(OBJ *obj) {
    // Retorna se o objeto já possui normais por vértice
    //if (obj->normais_por_vertice) return;
    for (int o=0; o<obj->meshes.size(); o++) {
        MESH* mesh = obj->meshes[o];
        CalculaNormaisPorFace(mesh);
    }
}

// Função para ler um arquivo JPEG e criar uma
// textura OpenGL
// mipmap = true se deseja-se utilizar mipmaps
TEX *CarregaTextura(string arquivo, bool mipmap) {
    //cout << "CarregaTextura: tentando ler " << arquivo << "*\n";
    GLenum formato;

    if (arquivo=="")		// retornamos NULL caso nenhum nome de arquivo seja informado
        return NULL;

    int indice = _procuraTextura(arquivo);
    // Se textura já foi carregada, retorna
    // apontador para ela
    if (indice!=-1)
        return _texturas[indice];

    TEX *pImage = CarregaJPG(arquivo);	// carrega o arquivo JPEG
    //std::cout << "passa aqui\n\n";

    if (pImage == NULL)	// se não foi possível carregar o arquivo, finaliza o programa
	{
		cout << "Textura não pode ser carregada\n"; getchar();
        exit(0);
	}

    pImage->nome = arquivo;

    //std::cout << "passa aqui 2\n\n";
    // Gera uma identificação para a nova textura
    glGenTextures(1, &pImage->texid);

    // Informa o alinhamento da textura na memória
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Informa que a textura é a corrente
    glBindTexture(GL_TEXTURE_2D, pImage->texid);

    if (pImage->ncomp==1) formato = GL_LUMINANCE;
    else formato = GL_RGB;

    if (mipmap) {
        // Cria mipmaps para obter maior qualidade
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, pImage->dimx, pImage->dimy,
                          formato, GL_UNSIGNED_BYTE, pImage->data);
        // Ajusta os filtros iniciais para a textura
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    } else {
        // Envia a textura para OpenGL, usando o formato RGB
        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, pImage->dimx, pImage->dimx,
                      0, formato, GL_UNSIGNED_BYTE, pImage->data);
        // Ajusta os filtros iniciais para a textura
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // Finalmente, libera a memória ocupada pela imagem (já que a textura já foi enviada para OpenGL)

    //free(pImage->data); 	// libera a memória ocupada pela imagem
    delete [] pImage->data; 	// libera a memória ocupada pela imagem

    // Inclui textura na lista
    _texturas.push_back(pImage);
    // E retorna apontador para a nova textura
    return pImage;
}

// Identificadores OpenGL para cada uma das faces
// do cubemap
GLenum faces[6] = {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

string nomes[] = {
    "posx", "negx", "posy", "negy", "posz", "negz"
};

// Função para ler 6 arquivos JPEG e criar
// texturas para cube mapping
// mipmap = true se for utilizar mipmaps
TEX *CarregaTexturasCubo(char *nomebase, bool mipmap) {
    GLenum formato;
    TEX *primeira;

    if (!nomebase)		// retornamos NULL caso nenhum nome de arquivo seja informado
        return NULL;

    // Informa o alinhamento da textura na memória
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Carrega as texturas do cubemap e envia para OpenGL
    for (int i=0;i<6;++i) {
        char arquivo[100];
        sprintf(arquivo,"%s_%s.jpg",nomebase,nomes[i].c_str());

        int indice = _procuraTextura(nomebase);
        // Se textura já foi carregada, retorna
        if (indice!=-1)
            return _texturas[indice];

        // Carrega o arquivo JPEG, sem inverter a
        // ordem das linhas (necessário para a
        // textura não ficar de cabeça para baixo
        // no cube map)
        TEX *pImage = CarregaJPG(arquivo,false);

        if (pImage == NULL)	// se não foi possível carregar o arquivo, finaliza o programa
            exit(0);

        // Se for a primeira textura...
        if (!i) {
            // Salva apontador para retornar depois
            primeira = pImage;
            // Gera uma identificação para a nova textura
            glGenTextures(1, &pImage->texid);
            glBindTexture(GL_TEXTURE_CUBE_MAP, pImage->texid);
            pImage->nome = arquivo;
        }

        if (pImage->ncomp==1) formato = GL_LUMINANCE;
        else formato = GL_RGB;

        if (mipmap)
            // Cria mipmaps para obter maior qualidade
            gluBuild2DMipmaps(faces[i], GL_RGB, pImage->dimx, pImage->dimy,
                              formato, GL_UNSIGNED_BYTE, pImage->data);
        else
            // Envia a textura para OpenGL, usando o formato RGB
            glTexImage2D (faces[i], 0, GL_RGB, pImage->dimx, pImage->dimx,
                          0, formato, GL_UNSIGNED_BYTE, pImage->data);

        // Finalmente, libera a memória ocupada pela imagem (já que a textura já foi enviada para OpenGL)

        //free(pImage->data); 	// libera a memória ocupada pela imagem
        delete [] pImage->data; 	// libera a memória ocupada pela imagem

        // Inclui somente a primeira textura na lista
        if (!i) _texturas.push_back(pImage);
        else delete pImage; //free(pImage);
    }

    // Ajusta os filtros iniciais para o cube map
    if (mipmap) {
        glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    } else {
        glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // Retorna apontador para a primeira imagem (que contém a id)
    return primeira;
}

// Seta o filtro de uma textura específica
// ou de todas na lista (se for passado o argumento -1)
void SetaFiltroTextura(GLint tex, GLint filtromin, GLint filtromag) {
    glEnable(GL_TEXTURE_2D);
    if (tex!=-1) {
        glBindTexture(GL_TEXTURE_2D,tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtromin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtromag);
    } else
        for (unsigned int i=0;i<_texturas.size();++i) {
            glBindTexture(GL_TEXTURE_2D,_texturas[i]->texid);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtromin);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtromag);
        }
    glDisable(GL_TEXTURE_2D);
}

// Desabilita a geração de uma display list
// para o objeto especificado
void DesabilitaDisplayList(OBJ *ptr) {
    if (ptr == NULL) return;
    for (int o=0; o < ptr->meshes.size(); o++) {
        MESH* mesh = ptr->meshes[o];

        if (mesh->dlist > 0 && mesh->dlist < 1000) { // já existe uma dlist ?
            // Libera dlist existente
            glDeleteLists(mesh->dlist,1);
        }
        // O valor especial -2 indica que não queremos
        // gerar dlist para esse objeto
        mesh->dlist = -2;
    }
}

// Função interna para criar uma display list
// (na verdade, a display list em si é gerada durante a
// primeira vez em que o objeto é redesenhado)
void _criaDList(OBJ *ptr) {
    for (int o=0; o<ptr->meshes.size(); o++) {
        MESH* mesh = ptr->meshes[o];
        // Se o modelo não possui display list, gera uma identificação nova
        if (mesh->dlist == -1) mesh->dlist = glGenLists(1);
        // Adiciona 1000 ao valor, para informar à rotina de desenho
        // que uma nova display list deve ser compilada
        mesh->dlist = mesh->dlist + 1000;
    }
}

// Cria uma display list para o objeto informado
// - se for NULL, cria display lists para TODOS os objetos
// (usada na rotina de desenho, se existir)
void CriaDisplayList(OBJ *ptr) {
    if (ptr==NULL) {
        for (unsigned int i=0;i<_objetos.size();++i) {
            ptr = _objetos[i];
            // Pula os objetos que não devem usar dlists
            if (ptr->meshes[0]->dlist == -2) continue;
            _criaDList(ptr);
        }
    } else if (ptr->meshes[0]->dlist != -2)_criaDList(ptr);
}

// Decodifica uma imagem JPG e armazena-a em uma estrutura TEX.
void DecodificaJPG(jpeg_decompress_struct* cinfo, TEX *pImageData, bool inverte) {
    // Lê o cabeçalho de um arquivo jpeg
    jpeg_read_header(cinfo, TRUE);

    // Começa a descompactar um arquivo jpeg com a informação
    // obtida do cabeçalho
    jpeg_start_decompress(cinfo);

    // Pega as dimensões da imagem e varre as linhas para ler os dados do pixel
    pImageData->ncomp = cinfo->num_components;
    pImageData->dimx  = cinfo->image_width;
    pImageData->dimy  = cinfo->image_height;

    int rowSpan = pImageData->ncomp * pImageData->dimx;
    // Aloca memória para o buffer do pixel
    pImageData->data = new unsigned char[rowSpan * pImageData->dimy];

    // Aqui se usa a variável de estado da biblioteca cinfo.output_scanline
    // como o contador de loop

    // Cria um array de apontadores para linhas
    int height = pImageData->dimy - 1;
    unsigned char** rowPtr = new unsigned char*[pImageData->dimy];
    if (inverte)
        for (int i = 0; i <= height; i++)
            rowPtr[height - i] = &(pImageData->data[i*rowSpan]);
    else
        for (int i = 0; i <= height; i++)
            rowPtr[i] = &(pImageData->data[i*rowSpan]);

    // Aqui se extrai todos os dados de todos os pixels
    int rowsRead = 0;
    while (cinfo->output_scanline < cinfo->output_height) {
        // Lê a linha corrente de pixels e incrementa o contador de linhas lidas
        rowsRead += jpeg_read_scanlines(cinfo, &rowPtr[rowsRead], cinfo->output_height - rowsRead);
    }

    // Libera a memória
    delete [] rowPtr;

    // Termina a decompactação dos dados
    jpeg_finish_decompress(cinfo);
}

// Carrega o arquivo JPG e retorna seus dados em uma estrutura tImageJPG.
TEX *CarregaJPG(string filename, bool inverte) {

    struct jpeg_decompress_struct cinfo;
    TEX *pImageData = NULL;
    FILE *pFile;

    // Abre um arquivo JPG e verifica se não ocorreu algum problema na abertura
    if ((pFile = fopen(filename.c_str(), "rb")) == NULL) {
        // Exibe uma mensagem de erro avisando que o arquivo não foi encontrado
        // e retorna NULL
        cout << "Impossível carregar arquivo JPG: " << filename << endl;
        return NULL;
    }

    // Cria um gerenciado de erro
    jpeg_error_mgr jerr;

    // Objeto com informações de compactação para o endereço do gerenciador de erro
    cinfo.err = jpeg_std_error(&jerr);

    // Inicializa o objeto de decompactação
    jpeg_create_decompress(&cinfo);

    // Especifica a origem dos dados (apontador para o arquivo)
    jpeg_stdio_src(&cinfo, pFile);

    // Aloca a estrutura que conterá os dados jpeg
    pImageData = new TEX;

    // Decodifica o arquivo JPG e preenche a estrutura de dados da imagem
    DecodificaJPG(&cinfo, pImageData, inverte);

    // Libera a memória alocada para leitura e decodificação do arquivo JPG
    jpeg_destroy_decompress(&cinfo);

    // Fecha o arquivo
    fclose(pFile);

    // Retorna os dados JPG (esta memória deve ser liberada depois de usada)
    return pImageData;
}

void escalaObjeto(OBJ *obj, float scaleFactor){
	 for (int o=0; o<obj->meshes.size(); o++) {
        MESH* mesh = obj->meshes[o];
		for(int i=0; i<mesh->vertices.size(); i++){
			mesh->vertices[i].x *= scaleFactor;
			mesh->vertices[i].y *= scaleFactor;
			mesh->vertices[i].z *= scaleFactor;
		}
    }
}
