#include "Enemy.h"
#include <GL/glut.h>

Enemy::Enemy(void) : GameObject()
{
	setCollider(-25, -25, -25, 35, 25, 35, 25, -25);
}

Enemy::~Enemy(void)
{

}

void Enemy::drawSkin()
{
	//Body
	glBegin(GL_LINE_LOOP);
		glVertex2f(-25,-25);
		glVertex2f(-25, 25);
		glVertex2f(-15, 35);
		glVertex2f(-05, 25);
		glVertex2f( 05, 25);
		glVertex2f( 15, 35);
		glVertex2f( 25, 25);
		glVertex2f( 25,-25);
	glEnd();

	//Mouth
	glBegin(GL_LINE_LOOP);
		glVertex2f(-05,-15);
		glVertex2f(-10,-05);
		glVertex2f( 10,-05);
		glVertex2f( 05,-15);
		glVertex2f( 05,-05);
		glVertex2f(-05,-05);
	glEnd();

	//Left eye
	glBegin(GL_LINE_LOOP);
		glVertex2f(-05, 05);
		glVertex2f(-05, 15);
		glVertex2f(-15, 15);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(-10, 10);
		glVertex2f(-10, 15);
		glVertex2f(-15, 25);
		glVertex2f(-05, 15);
	glEnd();

	//Right eye
	glBegin(GL_LINE_LOOP);
		glVertex2f( 05, 05);
		glVertex2f( 05, 15);
		glVertex2f( 15, 15);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f( 10, 10);
		glVertex2f( 10, 15);
		glVertex2f( 15, 25);
		glVertex2f( 05, 15);
	glEnd();
}
