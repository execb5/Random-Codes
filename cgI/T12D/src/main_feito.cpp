#include <stdlib.h>
#include <GL/glut.h>
#include "Enemy.h"
#include<vector>
#include<cmath>
#include<iostream>

using namespace std;

typedef struct
{
	float x;
	float y;
} Position;

float translacaoX = 0, translacaoY = 0;
float lleft;
float rright;
float bbottom;
float ttop;
float panX;
float panY;
Position pos;

vector<Enemy> casas;

int instanciaSelecionada = 0;

void desenhaTexto(void *font, char *string)
{
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void desenhaEixos()
{
	glColor3f(1, 1, 1);

	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex2f(lleft + panX, 0.0 + panY);
		glVertex2f(rright + panX, 0.0 + panY);
		glVertex2f(0.0 + panX, bbottom + panY);
		glVertex2f(0.0 + panX, ttop + panY);
	glEnd();
}

void drawStage()
{
	glColor3f(1, 1, 1);

	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex2f(-250, -200);
		glVertex2f( 750, -200);
	glEnd();
}

void desenha(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(lleft + panX, rright + panX, bbottom + panY, ttop + panY);
	//gluOrtho2D(-250, 250, -250, 250);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0, 0, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);

	glPushMatrix();

	glLoadIdentity();

	drawStage();

	glPopMatrix();
	
	glLineWidth(1);

	for (int i = 0; i < casas.size(); i++)
	{
		glPushMatrix();

		glTranslatef(casas[i].getTx(), casas[i].getTy(), 0.0f);
		glScalef(casas[i].getEx(), casas[i].getEy(), 1.0f);
		glRotatef(casas[i].getAngle(), 0.0f, 0.0f, 1.0f);

		if (instanciaSelecionada == i)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);

		casas[i].drawSkin1();


		glPopMatrix();
	}

	glColor3f(1, 1, 1);

	glPushMatrix();

	glTranslatef(0, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	glLineWidth(100);
	glRasterPos2f(0, 0);

	//desenhaTexto(GLUT_BITMAP_TIMES_ROMAN_24, "Casinha");

	glPopMatrix();

	glutSwapBuffers();

	glFlush();
}

void teclado(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == 'w')
		cout << " (" << casas[0].getTx() << ", " << casas[0].getTy() << ")";
}

void inicializa(void)
{
	//Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	lleft = -250;
	rright = 250;
	ttop = 250;
	bbottom = -250;
	gluOrtho2D(lleft + panX, rright + panX, bbottom + panY, ttop + panY);
	glMatrixMode(GL_MODELVIEW);
}

void alteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;
	
	GLsizei largura = w;
	GLsizei altura = h;

	glViewport(0, 0, largura, altura);

	inicializa();
}

void teclasEspeciais(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		casas[instanciaSelecionada].decrementTx();

	if (key == GLUT_KEY_RIGHT)
		casas[instanciaSelecionada].incrementTx();

	if (key == GLUT_KEY_UP)
		casas[instanciaSelecionada].incrementTy();

	if (key == GLUT_KEY_DOWN)
		casas[instanciaSelecionada].decrementTy();

	if (key == GLUT_KEY_F5)
	{
		casas[instanciaSelecionada].decrementEy();
		casas[instanciaSelecionada].decrementEx();
	}

	if (key == GLUT_KEY_F6)
	{
		casas[instanciaSelecionada].incrementEy();
		casas[instanciaSelecionada].incrementEx();
	}

	if (key == GLUT_KEY_END)
	{
		lleft -= 0.1;
		rright += 0.1;
		ttop += 0.1;
		bbottom -= 0.1;
	}

	if (key == GLUT_KEY_HOME)
	{
		lleft += 0.1;
		rright -= 0.1;
		ttop -= 0.1;
		bbottom += 0.1;
	}

	if (key == GLUT_KEY_F9)
		panX += 10;

	if (key == GLUT_KEY_F10)
		panX -= 10;

	if (key == GLUT_KEY_F11)
		panY += 10;

	if (key == GLUT_KEY_F12)
		panY -= 10;

	if (key == GLUT_KEY_PAGE_DOWN)
	{
		instanciaSelecionada--;
		if (instanciaSelecionada < 0)
			instanciaSelecionada = casas.size() - 1;
	}

	if (key == GLUT_KEY_PAGE_UP)
	{
		instanciaSelecionada++;
		if (instanciaSelecionada > casas.size() - 1)
			instanciaSelecionada = 0;
	}

	if (key == GLUT_KEY_F1)
	{
		Enemy casa;
		casas.push_back(casa);
		instanciaSelecionada = casas.size() - 1;
	}

	if (key == GLUT_KEY_F2)
		casas[instanciaSelecionada].incrementAngle();

	if (key == GLUT_KEY_F3)
		casas[instanciaSelecionada].decrementAngle();

	//glutPostRedisplay();
}


//Read later for collision: http://nehe.gamedev.net/tutorial/collision_detection/17005/
//Read later, interesting: http://higherorderfun.com/blog/2012/05/20/the-guide-to-implementing-2d-platformers/
//http://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_Introduction.html
int main(void)
{
	Enemy casa;

	//pos.x = casa.getTx;
	//pos.y = casa.getTy;

	casas.push_back(casa);

	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);

	glutCreateWindow("T12D");

	glutDisplayFunc(desenha);

	glutReshapeFunc(alteraTamanhoJanela);

	glutKeyboardFunc(teclado);

	glutSpecialFunc(teclasEspeciais);

	inicializa();

	//Always draw
	glutIdleFunc(desenha);

	glutMainLoop();

	return 0;
}
