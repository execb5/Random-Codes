#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GL/glut.h"

#define SENS_ROT	5.0
#define SENS_OBS	1.0
#define SENS_TRANSL	1.0

unsigned int LOD = 15;
int x_ini,y_ini,bot;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ =200, obsX_ini, obsY_ini, obsZ_ini;
GLfloat fAspect = 1, angle = 45;

bool bezier = false, hermite = false, bspline = false;
bool p1 = false, p2 = false, p3 = false, p4 = false;

// 4 control points for our cubic bezier curve
float BezierPoints[4][3] =
{
	{ 30,5,-2},
	{ 35,0,0 },
	{ 45,10,2 },
	{ 50,10,0 }
};
//Control points for Hermite curve
float HermitePoints[4][3] =
{
	{-10,5,-2 },	//	Point1
	{ 10,10,0 },	//	Point2
	{ -12,15,0  },	//	Tangent1
	{ 5,0,0  }		//	Tangent2
};
/// the control points for the bSpline curve
float BSplinePoints[4][3] =
{
	{ -50,5,-2},
	{ -45,0,0 },
	{ -35,10,2 },
	{ -30,10,0 }
};

void PosicionaObservador(void)
{
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

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
	glColor3f(0,0,1);
	glLineWidth(1);
	glBegin(GL_LINES);
	for(float z=-1000; z<=1000; z+=8)
	{
		glVertex3f(-1000,-0.1f,z);
		glVertex3f( 1000,-0.1f,z);
	}
	for(float x=-1000; x<=1000; x+=8)
	{
		glVertex3f(x,-0.1f,-1000);
		glVertex3f(x,-0.1f,1000);
	}
	glEnd();

	glLineWidth(1);
}

void desenhaPontosDeControle()
{
	char* strP0 = "P1";	char* strP1 = "P2"; char* strP2 = "P3"; char* strP3 = "P4";
	char* strT0 = "T1"; char* strT1 = "T2";
	glColor3d(1,0,0);

	//Hermite
	glRasterPos3d(HermitePoints[0][0], HermitePoints[0][1], HermitePoints[0][2]);
	for(int l=0; l<strlen(strP0); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP0[l]);
	glRasterPos3d(HermitePoints[1][0], HermitePoints[1][1], HermitePoints[1][2]);
	for(int l=0; l<strlen(strP1); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP1[l]);
	glRasterPos3d(HermitePoints[2][0], HermitePoints[2][1], HermitePoints[2][2]);
	for(int l=0; l<strlen(strT0); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strT0[l]);
	glRasterPos3d(HermitePoints[3][0], HermitePoints[3][1], HermitePoints[3][2]);
	for(int l=0; l<strlen(strT1); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strT1[l]);

	//Bezier
	glRasterPos3d(BezierPoints[0][0], BezierPoints[0][1], BezierPoints[0][2]);
	for(int l=0; l<strlen(strP0); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP0[l]);
	glRasterPos3d(BezierPoints[1][0], BezierPoints[1][1], BezierPoints[1][2]);
	for(int l=0; l<strlen(strP1); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP1[l]);
	glRasterPos3d(BezierPoints[2][0], BezierPoints[2][1], BezierPoints[2][2]);
	for(int l=0; l<strlen(strP2); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP2[l]);
	glRasterPos3d(BezierPoints[3][0], BezierPoints[3][1], BezierPoints[3][2]);
	for(int l=0; l<strlen(strP3); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP3[l]);

	//BSpline
	glRasterPos3d(BSplinePoints[0][0], BSplinePoints[0][1], BSplinePoints[0][2]);
	for(int l=0; l<strlen(strP0); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP0[l]);
	glRasterPos3d(BSplinePoints[1][0], BSplinePoints[1][1], BSplinePoints[1][2]);
	for(int l=0; l<strlen(strP1); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP1[l]);
	glRasterPos3d(BSplinePoints[2][0], BSplinePoints[2][1], BSplinePoints[2][2]);
	for(int l=0; l<strlen(strP2); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP2[l]);
	glRasterPos3d(BSplinePoints[3][0], BSplinePoints[3][1], BSplinePoints[3][2]);
	for(int l=0; l<strlen(strP3); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,strP3[l]);
}

void desenhaNomes()
{
	char* str_Bezier = "Bezier"; char* str_BSpline = "BSpline"; char* str_Hermite = "Hermite";
	glColor3d(1,1,0);

	//Hermite
	glRasterPos3d(HermitePoints[0][0], HermitePoints[0][1] + 8, HermitePoints[0][2]);
	for(int l=0; l<strlen(str_Hermite); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str_Hermite[l]);

	//Bezier
	glRasterPos3d(BezierPoints[0][0], BezierPoints[0][1] + 8, BezierPoints[0][2]);
	for(int l=0; l<strlen(str_Bezier); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str_Bezier[l]);

	//BSpline
	glRasterPos3d(BSplinePoints[0][0], BSplinePoints[0][1] + 8, BSplinePoints[0][2]);
	for(int l=0; l<strlen(str_BSpline); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str_BSpline[l]);

}

void desenhaBezier()
{
	glColor3f(1,0,1);
	glLineWidth(3);

	glBegin(GL_LINE_STRIP);

	for(int i=0;i!=LOD;++i) {

		// use the parametric time value 0 to 1
		float t = (float)i/(LOD-1);

		// nice to pre-calculate 1.0f-t because we will need it frequently
		float it = 1.0f-t;

		// calculate blending functions
		float b0 = t*t*t;
		float b1 = 3*t*t*it;
		float b2 = 3*t*it*it;
		float b3 =  it*it*it;

		// calculate the x,y and z of the curve point by summing
		// the Control vertices weighted by their respective blending
		// functions
		//
		float x = b0*BezierPoints[0][0] +
			b1*BezierPoints[1][0] +
			b2*BezierPoints[2][0] +
			b3*BezierPoints[3][0] ;

		float y = b0*BezierPoints[0][1] +
			b1*BezierPoints[1][1] +
			b2*BezierPoints[2][1] +
			b3*BezierPoints[3][1] ;

		float z = b0*BezierPoints[0][2] +
			b1*BezierPoints[1][2] +
			b2*BezierPoints[2][2] +
			b3*BezierPoints[3][2] ;

		// specify the point
		glVertex3f( x,y,z );
	}
	glEnd();

	// draw the Control Vertices
	glColor3f(0,1,0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for(int i=0;i!=4;++i) {
		glVertex3fv( BezierPoints[i] );
	}
	glEnd();

	// draw the hull of the curve
	glColor3f(0,1,1);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	for(int i=0;i!=4;++i) {
		glVertex3fv( BezierPoints[i] );
	}
	glEnd();
}

void desenhaBSpline()
{
	glColor3f(1,0,1);
	glLineWidth(3);

	glBegin(GL_LINE_STRIP);

	// use the parametric time value 0 to 1
	for(int i=0;i!=LOD;++i) {

		float t = (float)i/(LOD-1);

		// the t value inverted
		float it = 1.0f-t;

		// calculate blending functions
		float b0 = it*it*it/6.0f;
		float b1 = (3*t*t*t - 6*t*t +4)/6.0f;
		float b2 = (-3*t*t*t +3*t*t + 3*t + 1)/6.0f;
		float b3 =  t*t*t/6.0f;

		// sum the control points mulitplied by their respective blending functions
		float x = b0*BSplinePoints[0][0] +
			b1*BSplinePoints[1][0] +
			b2*BSplinePoints[2][0] +
			b3*BSplinePoints[3][0] ;

		float y = b0*BSplinePoints[0][1] +
			b1*BSplinePoints[1][1] +
			b2*BSplinePoints[2][1] +
			b3*BSplinePoints[3][1] ;

		float z = b0*BSplinePoints[0][2] +
			b1*BSplinePoints[1][2] +
			b2*BSplinePoints[2][2] +
			b3*BSplinePoints[3][2] ;

		// specify the point
		glVertex3f( x,y,z );
	}
	glEnd();

	// draw the control points
	glColor3f(0,1,0);
	glPointSize(3);
	glBegin(GL_POINTS);
	for(int i=0;i!=4;++i) {
		glVertex3fv( BSplinePoints[i] );
	}
	glEnd();

	// draw the hull of the curve
	glColor3f(0,1,1);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	for(int i=0;i!=4;++i) {
		glVertex3fv( BSplinePoints[i] );
	}
	glEnd();
}

void desenhaHermite()
{
	glColor3f(1,0,1);
	glLineWidth(3);

	glBegin(GL_LINE_STRIP);
		// use the parametric time value 0 to 1
		for(int i=0;i!=LOD;++i)
		{
			float t = (float)i/(LOD-1);

			// calculate blending functions
			float b0 =  2*t*t*t - 3*t*t + 1;
			float b1 = -2*t*t*t + 3*t*t;
			float b2 = t*t*t - 2*t*t + t;
			float b3 = t*t*t - t*t;

			// calculate the x,y and z of the curve point
			float x = b0*HermitePoints[0][0] +
				b1*HermitePoints[1][0] +
				b2*HermitePoints[2][0] +
				b3*HermitePoints[3][0] ;

			float y = b0*HermitePoints[0][1] +
				b1*HermitePoints[1][1] +
				b2*HermitePoints[2][1] +
				b3*HermitePoints[3][1] ;

			float z = b0*HermitePoints[0][2] +
				b1*HermitePoints[1][2] +
				b2*HermitePoints[2][2] +
				b3*HermitePoints[3][2] ;

			// specify the point
			glVertex3f( x,y,z );
		}
	glEnd();
	//Desenha pontos de controle
	glColor3f(0,1,0.5);
	glPointSize(3);
	glBegin(GL_POINTS);
		glVertex3fv( HermitePoints[0] );
		glVertex3fv( HermitePoints[1] );
	glEnd();
	//Desenha tangentes
	glColor3f(0.5,1,0.5);
	glLineWidth(1);
	glPushMatrix();
	//glTranslatef(HermitePoints[0][0],HermitePoints[0][1],HermitePoints[0][2]);
	glBegin(GL_LINES);
		glVertex3fv( HermitePoints[0] );
		glVertex3fv( HermitePoints[2] );
	glEnd();
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(HermitePoints[1][0],HermitePoints[1][1],HermitePoints[1][2]);
	glBegin(GL_LINES);
		glVertex3fv( HermitePoints[1] );
		glVertex3fv( HermitePoints[3] );
	glEnd();
	glPopMatrix();
}

void OnDraw()
{
	// clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	EspecificaParametrosVisualizacao();
	desenhaChao();

	desenhaBezier();
	desenhaBSpline();
	desenhaHermite();

	desenhaPontosDeControle();
	desenhaNomes();

	glutSwapBuffers();
}

void OnInit() {
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
}

void OnReshape(int w, int h)
{
	if (h==0) h = 1;

	// set the drawable region of the window
	glViewport(0,0,w,h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
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

void GerenciaTeclado(unsigned char key,int,int) {
	if (key == 27)
		exit(0);
	switch(key)
	{
		case '+':
			++LOD;
			break;
		case '-':
			--LOD;
			if (LOD<2)
				LOD=2;
			break;
		case '1':
			p1 = true; p2 = false; p3 = false; p4 = false;
			printf("\nP1 selected.");
			break;
		case '2':
			p1 = false;
			p2 = true;
			p3 = false;
			p4 = false;
			printf("\nP2 selected.");
			break;
		case '3':
			p1 = false; p2 = false;
			p3 = true; p4 = false;
			printf("\nP3 selected.");
			break;
		case '4':
			p1 = false; p2 = false; p3 = false; p4 = true;
			printf("\nP4 selected.");
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void GerenciaTecladoEspecial(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_F1:
			bezier = false; hermite = false;
			bspline = true;
			printf("\nBSplineactive.");
			break;
		case GLUT_KEY_F2:
			bezier = false;
			hermite = true;
			bspline = false;
			printf("\nHermite active.");
			break;
		case GLUT_KEY_F3:
			bezier =true;
			hermite = false; bspline = false;
			printf("\nBezieractive.");
			break;
		case GLUT_KEY_LEFT:
			if (bezier)
			{
				if (p1) BezierPoints[0][0]-= 0.2;
				if (p2) BezierPoints[1][0]-= 0.2;
				if (p3) BezierPoints[2][0]-= 0.2;
				if (p4) BezierPoints[3][0]-= 0.2;
			}
			if (hermite)
			{
				if (p1) HermitePoints[0][0]-= 0.2;
				if (p2) HermitePoints[1][0]-= 0.2;
				if (p3) HermitePoints[2][0]-= 0.2;
				if (p4) HermitePoints[3][0]-= 0.2;
			}
			if (bspline)
			{
				if (p1) BSplinePoints[0][0]-= 0.2;
				if (p2) BSplinePoints[1][0]-= 0.2;
				if (p3) BSplinePoints[2][0]-= 0.2;
				if (p4) BSplinePoints[3][0]-= 0.2;
			}
			break;
		case GLUT_KEY_RIGHT:
			if (bezier)
			{
				if (p1) BezierPoints[0][0] += 0.2;
				if (p2) BezierPoints[1][0] += 0.2;
				if (p3) BezierPoints[2][0] += 0.2;
				if (p4) BezierPoints[3][0] += 0.2;
			}
			if (hermite)
			{
				if (p1) HermitePoints[0][0] += 0.2;
				if (p2) HermitePoints[1][0] += 0.2;
				if (p3) HermitePoints[2][0] += 0.2;
				if (p4) HermitePoints[3][0] += 0.2;
			}
			if (bspline)
			{
				if (p1) BSplinePoints[0][0] += 0.2;
				if (p2) BSplinePoints[1][0] += 0.2;
				if (p3) BSplinePoints[2][0] += 0.2;
				if (p4) BSplinePoints[3][0] += 0.2;
			}
			break;
		case GLUT_KEY_UP:
			if (bezier)
			{
				if (p1) BezierPoints[0][1] += 0.2;
				if (p2) BezierPoints[1][1] += 0.2;
				if (p3) BezierPoints[2][1] += 0.2;
				if (p4) BezierPoints[3][1] += 0.2;
			}
			if (hermite)
			{
				if (p1) HermitePoints[0][1] += 0.2;
				if (p2) HermitePoints[1][1] += 0.2;
				if (p3) HermitePoints[2][1] += 0.2;
				if (p4) HermitePoints[3][1] += 0.2;
			}
			if (bspline)
			{
				if (p1) BSplinePoints[0][1] += 0.2;
				if (p2) BSplinePoints[1][1] += 0.2;
				if (p3) BSplinePoints[2][1] += 0.2;
				if (p4) BSplinePoints[3][1] += 0.2;
			}
			break;
		case GLUT_KEY_DOWN:
			if (bezier)
			{
				if (p1) BezierPoints[0][1]-= 0.2;
				if (p2) BezierPoints[1][1]-= 0.2;
				if (p3) BezierPoints[2][1]-= 0.2;
				if (p4) BezierPoints[3][1]-= 0.2;
			}
			if (hermite)
			{
				if (p1) HermitePoints[0][1]-= 0.2;
				if (p2) HermitePoints[1][1]-= 0.2;
				if (p3) HermitePoints[2][1]-= 0.2;
				if (p4) HermitePoints[3][1]-= 0.2;
			}
			if (bspline)
			{
				if (p1) BSplinePoints[0][1]-= 0.2;
				if (p2) BSplinePoints[1][1]-= 0.2;
				if (p3) BSplinePoints[2][1]-= 0.2;
				if (p4) BSplinePoints[3][1]-= 0.2;
			}
			break;
	}
	glutPostRedisplay();
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

int main(int argc,char** argv)
{
	// initialize glut
	glutInit(&argc,argv);

	// request a depth buffer, RGBA display mode, and we want double buffering
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);

	// set the initial window size
	glutInitWindowSize(800,600);

	// create the window
	glutCreateWindow("Curves");

	// set the function to use to draw our scene
	glutDisplayFunc(OnDraw);

	// set the function to handle changes in screen size
	glutReshapeFunc(OnReshape);

	// set the function for the key presses
	glutMotionFunc(GerenciaMovim);
	glutMouseFunc(GerenciaMouse);
	glutKeyboardFunc(GerenciaTeclado);
	glutSpecialFunc(GerenciaTecladoEspecial);

	// run our custom initialization
	OnInit();

	// this function runs a while loop to keep the program running.
	glutMainLoop();
}
