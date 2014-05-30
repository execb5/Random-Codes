//main.cpp

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

#include "reader.h"

Reader obj;

float angle;

void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("WINDOW 3D");

    freopen( "CON", "wt", stdout );
    freopen( "CON", "wt", stderr );

    obj.load("cube.obj");

    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void display(void)
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -2.75f, -5.0f);
    obj.draw("cube.obj");

    glutSwapBuffers();
    angle += .1f;
}

void reshape( int width, int height )
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{

    init(argc, argv);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}
