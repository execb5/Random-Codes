#include "Enemy.h"
#include <GL/glut.h>

Enemy::Enemy(void) : GameObject()
{

}

Enemy::~Enemy(void)
{

}

void Enemy::drawSkin1()
{
	/*//Body
	glBegin(GL_LINE_LOOP);
		glVertex2f( 1.0f, 1.0f);
		glVertex2f( 6.0f, 1.0f);
		glVertex2f( 6.0f, 6.0f);
		glVertex2f( 5.0f, 7.0f);
		glVertex2f( 4.0f, 6.0f);
		glVertex2f( 3.0f, 6.0f);
		glVertex2f( 2.0f, 7.0f);
		glVertex2f( 1.0f, 6.0f);
	glEnd();

	//Mouth
	glBegin(GL_LINE_LOOP);
		glVertex2f( 3.0f, 2.0f);
		glVertex2f( 2.5f, 3.0f);
		glVertex2f( 4.5f, 3.0f);
		glVertex2f( 4.0f, 2.0f);
		glVertex2f( 4.0f, 3.0f);
		glVertex2f( 3.0f, 3.0f);
	glEnd();

	//Left eye
	glBegin(GL_LINE_LOOP);
		glVertex2f( 3.0f, 5.0f);
		glVertex2f( 2.0f, 5.0f);
		glVertex2f( 3.0f, 4.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f( 2.5f, 4.5f);
		glVertex2f( 2.5f, 5.0f);
		glVertex2f( 2.0f, 6.0f);
		glVertex2f( 3.0f, 5.0f);
	glEnd();

	//Right eye
	glBegin(GL_LINE_LOOP);
		glVertex2f( 4.0f, 5.0f);
		glVertex2f( 5.0f, 5.0f);
		glVertex2f( 4.0f, 4.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f( 4.5f, 4.5f);
		glVertex2f( 4.5f, 5.0f);
		glVertex2f( 5.0f, 6.0f);
		glVertex2f( 4.0f, 5.0f);
	glEnd();*/

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

void Enemy::drawSkin2()
{

}
