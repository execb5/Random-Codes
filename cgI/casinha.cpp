#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

float translacaoX = 0.0;
float translacaoY = 0.0;

void desenhaCasinha()
{
    // Define a cor de desenho: azul
    glColor3f(1,0,0);

	glLineWidth(3);
    // Determina a espessura da linha que será desenhada
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.2f,0.1f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f,0.22f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.2f,0.1f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.2f,-0.1f);
        glVertex2f( 0.2f,-0.1f);
        glVertex2f( 0.2f, 0.1f);
    glEnd();
}

void desenhaEixos()
{
    glColor3f(1,1,1);

    glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f( 1.0f, 0.0f);
        glVertex2f( 0.0f, -1.0f);
        glVertex2f( 0.0f,  1.0f);
    glEnd();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor preta
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glLoadIdentity();

    desenhaEixos();

    glPopMatrix();

    glLoadIdentity();

    glTranslatef(translacaoX, translacaoY, 0.0f);

    desenhaCasinha();

	//Executa os comandos OpenGL
	glFlush();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
    if (key == 'w')
		translacaoY += 0.1;
    if (key == 'a')
		translacaoX -= 0.1;
    if (key == 's')
		translacaoY -= 0.1;
    if (key == 'd')
		translacaoX += 0.1;

    //precisa para criar evento de teclado.
    glutPostRedisplay();

}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
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

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
