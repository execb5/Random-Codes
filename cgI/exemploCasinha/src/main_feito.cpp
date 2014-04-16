#include <stdlib.h>
#include <GL/glut.h>
#include "Instancia.h"
#include <vector>

using namespace std;

float translacaoX = 0, translacaoY = 0;
float lleft, rright, ttop, bbottom, panX, panY;

vector<Instancia> casas;

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

void desenhaCasinha()
{
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-0.2f,  0.1f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.2f, -0.2f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f( 0.2f, -0.2f);
		glVertex2f( 0.2f,  0.1f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-0.2f, 0.1f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(0.0f, 0.22f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f( 0.2f, 0.1f);
	glEnd();
}

void desenha(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(lleft + panX, rright + panX, bbottom + panY, ttop + panY);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0, 0, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);

	glPushMatrix();

	glLoadIdentity();

	desenhaEixos();

	glPopMatrix();

	for (int i = 0; i < casas.size(); i++)
	{
		glPushMatrix();

		glTranslatef(casas[i].getTx(), casas[i].getTy(), 0.0f);
		glScalef(casas[i].getEx(), casas[i].getEy(), 1.0f);
		glRotatef(casas[i].getAngulo(), 0.0f, 0.0f, 1.0f);

		if (instanciaSelecionada == i)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);

		desenhaCasinha();

		glPopMatrix();
	}

	glColor3f(1, 1, 1);

	glPushMatrix();

	glTranslatef(0, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	glLineWidth(100);
	glRasterPos2f(0, 0);

	desenhaTexto(GLUT_BITMAP_TIMES_ROMAN_24, "Casinha");

	glPopMatrix();

	glutSwapBuffers();

	glFlush();
}

void teclado(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void inicializa(void)
{
	//Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	lleft = -1.0;
	rright = 1.0;
	ttop = 1.0;
	bbottom = -1.0;
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
		casas[instanciaSelecionada].decrementaTx();

	if (key == GLUT_KEY_RIGHT)
		casas[instanciaSelecionada].incrementaTx();

	if (key == GLUT_KEY_UP)
		casas[instanciaSelecionada].incrementaTy();

	if (key == GLUT_KEY_DOWN)
		casas[instanciaSelecionada].decrementaTy();

	if (key == GLUT_KEY_F5)
	{
		casas[instanciaSelecionada].decrementaEy();
		casas[instanciaSelecionada].decrementaEx();
	}

	if (key == GLUT_KEY_F6)
	{
		casas[instanciaSelecionada].incrementaEy();
		casas[instanciaSelecionada].incrementaEx();
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
		panX += 0.1;

	if (key == GLUT_KEY_F10)
		panX -= 0.1;

	if (key == GLUT_KEY_F11)
		panY += 0.1;

	if (key == GLUT_KEY_F12)
		panY -= 0.1;

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
		Instancia casa;
		casas.push_back(casa);
		instanciaSelecionada = casas.size() - 1;
	}

	if (key == GLUT_KEY_F2)
		casas[instanciaSelecionada].incrementaAngulo();

	if (key == GLUT_KEY_F3)
		casas[instanciaSelecionada].decrementaAngulo();

	glutPostRedisplay();
}

int main(void)
{
	Instancia casa;

	casas.push_back(casa);

	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(400, 400);

	glutCreateWindow("Casinha");

	glutDisplayFunc(desenha);

	glutReshapeFunc(alteraTamanhoJanela);

	glutKeyboardFunc(teclado);

	glutSpecialFunc(teclasEspeciais);

	inicializa();

	glutMainLoop();

	return 0;
}
