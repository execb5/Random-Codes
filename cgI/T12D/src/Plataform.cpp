#include "Plataform.h"
#include <GL/glut.h>

Plataform::Plataform(void) : GameObject()
{
	setCollider(-25, -15, -25, 15, 25, 15, 25, -15);
	setOriginalPosition(-25, -15, -25, 15, 25, 15, 25, -15);
}

Plataform::~Plataform(void)
{

}

void Plataform::drawSkin()
{
	//Body
	glBegin(GL_LINE_LOOP);
		glVertex2f(-25,-15);
		glVertex2f(-25, 15);
		glVertex2f( 25, 15);
		glVertex2f( 25,-15);
	glEnd();
}
