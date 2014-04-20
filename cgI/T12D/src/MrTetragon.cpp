#include "MrTetragon.h"
#include <GL/glut.h>

MrTetragon::MrTetragon(void) : GameObject()
{
	setCollider(-25, -55, -25, 55, 25, 55, 25, -55);
}

MrTetragon::~MrTetragon(void)
{

}

void MrTetragon::drawSkin()
{
	//Body
	glBegin(GL_LINE_LOOP);
		glVertex2f(-25,-55);
		glVertex2f(-25, 25);
		glVertex2f(-15, 35);
		glVertex2f(-15, 55);
		glVertex2f( 15, 55);
		glVertex2f( 15, 35);
		glVertex2f( 25, 25);
		glVertex2f( 25,-55);
	glEnd();

	//Moustache
	glBegin(GL_LINE_LOOP);
		glVertex2f(-15,-15);
		glVertex2f(-05,-05);
		glVertex2f( 05,-05);
		glVertex2f( 15,-15);
	glEnd();

	//Hair and hat
	glBegin(GL_LINES);
		glVertex2f(-25, 25);
		glVertex2f( 25, 25);
		glVertex2f(-15, 35);
		glVertex2f( 15, 35);
		glVertex2f(-25, 15);
		glVertex2f(-15, 25);
		glVertex2f( 25, 15);
		glVertex2f( 15, 25);
		glVertex2f(-15, 40);
		glVertex2f( 15, 40);
	glEnd();

	//Eyes - left, right and then the middle on both
	glBegin(GL_LINE_LOOP);
		glVertex2f(-15, 05);
		glVertex2f(-15, 15);
		glVertex2f(-05, 15);
		glVertex2f(-05, 05);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f( 05, 05);
		glVertex2f( 05, 15);
		glVertex2f( 15, 15);
		glVertex2f( 15, 05);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(-15, 05);
		glVertex2f(-05, 15);
		glVertex2f( 05, 15);
		glVertex2f( 15, 05);
	glEnd();

	//Shirt and tie
	glBegin(GL_LINE_LOOP);
		glVertex2f(-25,-55);
		glVertex2f(-25,-45);
		glVertex2f(-05,-25);
		glVertex2f( 05,-45);
		glVertex2f( 00,-55);
		glVertex2f(-05,-45);
		glVertex2f( 05,-25);
		glVertex2f( 25,-45);
		glVertex2f( 25,-55);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(-25,-25);
		glVertex2f( 25,-25);
	glEnd();
}
