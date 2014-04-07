#include <stdlib.h>
#include <GL/glut.h>
#include "Instancia.h"
#include <vector>
#include <iostream>

using namespace std;

vector<Instancia> casas;
int instanciaSelecionada = 0;

float translacaoX=0, translacaoY=0;
float lleft, rright, top, bottom, panX, panY;

void desenhaTexto(void *font, char *string)
{
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void desenhaEixos()
{
	glColor3f(1,1,1);
	glLineWidth(1);

	glBegin(GL_LINES);
		glVertex2f(lleft + panX,0.0 + panY);
		glVertex2f(rright + panX, 0.0 + panY);
		glVertex2f(0.0 + panX,bottom + panY);
		glVertex2f(0.0 + panX,top + panY);
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
	gluOrtho2D (lleft+panX, rright+panX, bottom+panY, top+panY);
	glMatrixMode(GL_MODELVIEW);

	// Limpa a janela de visualização com a cor branca
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0,0,1);

	glPushMatrix();

	glLoadIdentity();

	desenhaEixos();

	glPopMatrix();

	for(int i =0; i <casas.size();i++)
	{
		glPushMatrix();

		glTranslatef(casas[i].getTx(), casas[i].getTy(), 0.0f);

		glScalef(casas[i].getEx(), casas[i].getEy(), 1.0f);

		glRotatef(casas[i].getAngulo(), 0.0f, 0.0f, 1.0f);

		if (instanciaSelecionada==i)
			glColor3f(1,1,1);
		else
			glColor3f(0,0,1);

		desenhaCasinha();

		glPopMatrix();
	}

	glColor3f(1,1,1);

	glPushMatrix();

	glTranslatef(0,0,0);
	glScalef(0.2,0.2,0.2);
	glLineWidth(100);
	glRasterPos2f(0,0);

	desenhaTexto(GLUT_BITMAP_TIMES_ROMAN_24, "Casinha");

	glPopMatrix();

	glutSwapBuffers();

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
		lleft-=0.1;
		rright+=0.1;
		top+=0.1;
		bottom-=0.1;
	 }

	if(key == GLUT_KEY_HOME){
		lleft+=0.1;
		rright-=0.1;
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
		if(instanciaSelecionada > casas.size() - 1)
			instanciaSelecionada = 0;
	}
	if(key == GLUT_KEY_F1)
	{
		Instancia casinha;
		casas.push_back(casinha);
		instanciaSelecionada = casas.size() - 1;
	}

	if(key == GLUT_KEY_F3)
		casas[instanciaSelecionada].decrementaAngulo();

	if(key == GLUT_KEY_F4)
		casas[instanciaSelecionada].incrementaAngulo();

	if(key == GLUT_KEY_F5)
	{
		casas[instanciaSelecionada].incrementaEx();
		casas[instanciaSelecionada].incrementaEy();
	}

	if(key == GLUT_KEY_F6)
	{
		casas[instanciaSelecionada].decrementaEx();
		casas[instanciaSelecionada].decrementaEy();
	}	

	glutPostRedisplay();
}


// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	lleft=-1.0;
	rright=1.0;
	top=1.0;
	bottom=-1.0;
	gluOrtho2D(lleft+panX,rright+panX,bottom+panY,top+panY);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{
	cout << "Page Up - muda para a proxima casinha" << endl;
	cout << "Page Down - muda para a casinha anterior" << endl;
	cout << "Setas - Translada a casinha selecionada" << endl;
	cout << "Home - Faz ZOOM IN na janela de seleção" << endl;
	cout << "End - Faz ZOOM OUT na janela de seleção" << endl;
	cout << "F1 - Adiciona uma nova casinha" << endl;
	cout << "F2 - Rotaciona a casinha para a esquerda" << endl;
	cout << "F3 - Rotaciona a casinha para a direita" << endl;
	cout << "F5 - Reduz escala da casinha selecionada" << endl;
	cout << "F6 - Aumenta a escala da casinha selecionada" << endl;
	cout << "F9/F10 - PAN para direita/esquerda" << endl;
	cout << "F11/F12 - PAN para cima/baixo" << endl;

	Instancia casa;
	casas.push_back(casa);

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

	return 0;
}
