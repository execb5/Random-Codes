#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>


GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ =200, obsX_ini, obsY_ini, obsZ_ini;
GLfloat fAspect = 1, angle = 44;
int x_ini,y_ini,bot;

int rings = 6, nsides = 6, slices = 20, stacks = 10;




#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	30.0




void PosicionaObservador(void)
{

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//glTranslatef(-obsX,-obsY,-obsZ);

	//glRotatef(rotX,1,0,0);
	//glRotatef(rotY,0,1,0);


	//gluLookAt(0.0,80.0,200.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
	gluLookAt(obsX,obsY,obsZ, 0.0,0.0,0.0, 0.0,1.0,0.0);
}
void EspecificaParametrosVisualizacao(void)
{

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();


	gluPerspective(angle,fAspect,0.5,500);

    PosicionaObservador();

}
void desenhaChao()
    {
        glColor3f(1,0,1);
        glLineWidth(3);
        glBegin(GL_LINES);
        for(float z=-1000; z<=1000; z+=10)
        {
            glVertex3f(-1000,-0.1f,z);
            glVertex3f( 1000,-0.1f,z);
        }
        for(float x=-1000; x<=1000; x+=10)
        {
            glVertex3f(x,-0.1f,-1000);
            glVertex3f(x,-0.1f,1000);
        }
        glEnd();
        glLineWidth(1);
    }
void Desenha(void)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	EspecificaParametrosVisualizacao();


	glColor3f(0.0f, 0.0f, 1.0f);


	glPushMatrix();
	glTranslatef(0,28,0);

	//glutWireTeapot(35);
	//glutWireCube(35);
	//glutWireOctahedron();
	//glColor3f(1, 0, 1);
	//glutWireSphere(35, 51, 51);
	//glColor3f(1, 1, 1);
	//glutWireSphere(35, 49, 49);

	glutWireTorus(10, 50, nsides, rings);

	glPopMatrix();

	desenhaChao();


	glFlush();
}



void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void teclasEspeciais(int key, int x, int y)
{
    switch (key)

    {

        case GLUT_KEY_LEFT: obsX -=10;
                            break;

        case GLUT_KEY_RIGHT: obsX +=10;
                             break;

        case GLUT_KEY_UP: obsY +=10;
                          break;

        case GLUT_KEY_DOWN: obsY -=10;
                            break;

        case GLUT_KEY_HOME: obsZ +=10;
                            break;

        case GLUT_KEY_END: obsZ -=1;
                           break;

        case GLUT_KEY_F1: nsides++;
			  rings++;
                            break;
        case GLUT_KEY_F2: nsides--;
			  rings--;
                            break;
        case GLUT_KEY_F3: rings++;
                            break;
        case GLUT_KEY_F4: rings--;
                            break;
    }

    glutPostRedisplay();
}

void Inicializa (void)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLineWidth(2.0);
}

void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}
void GerenciaMovim(int x, int y)
{

	if(bot==GLUT_LEFT_BUTTON)
	{

		int deltax = x_ini - x;
		int deltay = y_ini - y;

		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}

	else if(bot==GLUT_RIGHT_BUTTON)
	{

		int deltaz = y_ini - y;

		obsZ = obsZ_ini + deltaz/SENS_OBS;


	}

	else if(bot==GLUT_MIDDLE_BUTTON)
	{

		int deltax = x_ini - x;
		int deltay = y_ini - y;

		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}


int main(void)
{

	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


	glutInitWindowPosition(5,5);


	glutInitWindowSize(450,450);


	glutCreateWindow("Camera, Projecao");


	glutDisplayFunc(Desenha);


	glutReshapeFunc(AlteraTamanhoJanela);

	glutKeyboardFunc (Teclado);

    glutSpecialFunc(teclasEspeciais);

	glutMotionFunc(GerenciaMovim);

	glutMouseFunc(GerenciaMouse);

	Inicializa();

	glutMainLoop();

	return 0;
}
