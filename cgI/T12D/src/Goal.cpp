#include "Goal.h"
#include <GL/glut.h>

Goal::Goal(void) : GameObject()
{
	setCollider(-25, -10, -25, 10, 25, 10, 25, -10);
	setOriginalPosition(-25, -10, -25, 10, 25, 10, 25, -10);
}

Goal::~Goal(void)
{

}

void Goal::drawSkin()
{
	glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 1);
		glVertex2f(-25,-10);
		glColor3f(0, 1, 0);
		glVertex2f(  0, 20);
		glColor3f(1, 0, 0);
		glVertex2f( 25,-10);
	glEnd();
}
