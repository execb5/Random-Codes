#include <stdlib.h>
#include <GL/glut.h>
#include "Instancia.h"
#include <vector>

using namespace std;

vector<Instancia> casas;
int instanciaSelecionada = 0;

float translacaoX=0, translacaoY=0;
float left, right, top, bottom, panX, panY;

void desenhaEixos()
{
	glColor3f(1,1,1);
	glLineWidth(1);

	glBegin(GL_LINES);
		glVertex2f(left,0.0);
		glVertex2f(right, 0.0);
		glVertex2f(0.0,bottom);
		glVertex2f(0.0,top);
	glEnd();
}

void desenhaCasinha()
{
	glLineWidth(3);

	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.2f,0.1f);
		glVertex2f(-0.2f,-0.2f);
		glVertex2f(0.2f,-0.2f);
		glVertex2f(0.2f,0.1f);
	glEnd();


	glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-0.2f,0.1f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(0.0f,0.22f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.2f,0.1f);
	glEnd();
}

void Desenha(void)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (left+panX, right+panX, bottom+panY, top+panY);
	glMatrixMode(GL_MODELVIEW);

	// Limpa a janela de visualização com a cor branca
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	glLoadIdentity();

	desenhaEixos();

	glPopMatrix();

	glLoadIdentity();

	glTranslatef(translacaoX,translacaoY,0);

	desenhaCasinha();

	// Define a cor de desenho: azul
	//glColor3f(1,0,1);

	// Desenha um triângulo no centro da janela
	//	glBegin(GL_TRIANGLES);
	//		glVertex3f(-0.5,-0.5,0);
	//		glVertex3f( 0.0, 0.5,0);
	//		glVertex3f( 0.5,-0.5,0);
	//	glEnd();

	//Executa os comandos OpenGL
	glFlush();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
	exit(0);
}

void TeclasEspecias(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT)
		casas[instanciaSelecionada].decrementaTx();

	if(key == GLUT_KEY_RIGHT)
		casas[instanciaSelecionada].incrementaTx();

	if(key == GLUT_KEY_UP)
		casas[instanciaSelecionada].incrementaTy();

	if(key == GLUT_KEY_DOWN)
		casas[instanciaSelecionada].decrementaTy();

	if(key == GLUT_KEY_END){
		left-=0.1;
		right+=0.1;
		top+=0.1;
		bottom-=0.1;
	 }

	if(key == GLUT_KEY_HOME){
		left+=0.1;
		right-=0.1;
		top-=0.1;
		bottom+=0.1;
	}

	if(key == GLUT_KEY_F9)
		panX+=0.1;
	if(key == GLUT_KEY_F10)
		panX-=0.1;
	if(key == GLUT_KEY_F11)
		panY+=0.1;
	if(key == GLUT_KEY_F12)
		panY-=0.1;

	if(key == GLUT_KEY_PAGE_DOWN)
	{
		instanciaSelecionada--;
		if(instanciaSelecionada < 0)
			instanciaSelecionada = casas.size()-1;
	}
	if(key == GLUT_KEY_PAGE_UP)
	{
		instanciaSelecionada++;
		if(instanciaSelecionada < casas.size())
			instanciaSelecionada = 0;
	}
	if(key == GLUT_KEY_F1)
	{
		Instancia casinha;
		casas.push_back(casinha);
		instanciaSelecionada++;
	}

	if(key == GLUT_KEY_F3)
		casas[instanciaSelecionada].decrementaAngulo();
	if(key == GLUT_KEY_F4)
		casas[instanciaSelecionada].incrementaAngulo();
	if(key == GLUT_KEY_F5)
		casas[instanciaSelecionada].incrementaEx();
	if(key == GLUT_KEY_F6)
		casas[instanciaSelecionada].incrementaAngulo();

	glutPostRedisplay();
}


// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	left=-1.0;
	right=1.0;
	top=1.0;
	bottom=-1.0;
	gluOrtho2D(left+panX,right+panX,bottom+panY,top+panY);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,500);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho de um triângulo em 2D");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	glutSpecialFunc (TeclasEspecias);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();


	Instancia casa;
	casas.push_back(casa);

	return 0;
}
