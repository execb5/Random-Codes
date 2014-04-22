#include <stdlib.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "MrTetragon.h"
#include "Plataform.h"
#include "Goal.h"
#include<vector>
#include<cmath>
#include<iostream>

using namespace std;

float lleft;
float rright;
float bbottom;
float ttop;

float panX;
float panY;

float maxX;
float maxY;
float minX;
float minY;

int counter = 0;
int counter2 = 0;

GameObject* plataform;
GameObject* player;
GameObject* enemy;
GameObject* goal;

vector<GameObject*> gameObjects;

int selectedObject = 0;

void drawText(void *font, char *string)
{
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void drawAxis()
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

void moveObjects(GameObject* obj)
{
	if (counter < 10)
	{
		obj->incrementTy();
		counter++;
	}
	else
	{
		obj->decrementTy();
		counter++;
		if (counter == 20)
			counter = 0;
	}
}

void moveObjects2(GameObject* obj)
{
	if (counter2 < 20)
	{
		obj->incrementTx();
		counter2++;
	}
	else
	{
		obj->decrementTx();
		counter2++;
		if (counter2 == 40)
			counter2 = 0;
	}
}

void drawStage()
{
	glColor3f(1, 0, 1);

	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex2f(-250, -105);
		glVertex2f(-105, -105);
		glVertex2f(-105, -105);
		glVertex2f(-105, -250);
		glVertex2f(-025, -105);
		glVertex2f(-025, -250);
		glVertex2f(-025, -105);
		glVertex2f( 500, -105);
		glVertex2f( 255,  105);
		glVertex2f( 500,  105);
		glVertex2f( 500, -105);
		glVertex2f(1005, -105);
		glVertex2f(1005, -105);
		glVertex2f(1005, 1000);
	glEnd();

	glColor3f(1, 1, 1);
}

void detectCollision()
{
	if ((player->getMinX() < enemy->getMinX() && player->getMaxX() > enemy->getMinX() && player->getMinY() <= enemy->getMaxY()) || (player->getMinX() < enemy->getMaxX() && player->getMaxX() > enemy->getMaxX() && player->getMinY() <= enemy->getMaxY()))
	{
		cout << "YOU DIED!!!" << endl;
		exit(0);
	}
	if ((player->getMinX() < goal->getMinX() && player->getMaxX() > goal->getMinX() && player->getMinY() <= goal->getMaxY()) || (player->getMinX() < goal->getMaxX() && player->getMaxX() > goal->getMaxX() && player->getMinY() <= goal->getMaxY()))
	{
		cout << "YOU WIN!!!" << endl;
		exit(0);
	}
}

void draw(void)
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

	drawStage();

	glPopMatrix();
	
	glLineWidth(1);

	maxX = gameObjects[selectedObject]->getMaxX();
	maxY = gameObjects[selectedObject]->getMaxY();
	minX = gameObjects[selectedObject]->getMinX();
	minY = gameObjects[selectedObject]->getMinY();

	//Test if the player is on the plataform.
	if ((player->getMinY() >= plataform->getMaxY() && player->getMinY() <= plataform->getMaxY() + 10) && ((player->getMaxX() > plataform->getMinX() && player->getMinX() < plataform->getMinX()) || (player->getMaxX() > plataform->getMaxX() && player->getMinX() < plataform->getMaxX()) || (player->getMinX() >= plataform->getMinX() && player->getMaxX() <= plataform->getMaxX())))
	{
		moveObjects(plataform);
		player->setTy(plataform->getMaxY() + 55);

		moveObjects2(enemy);
	}
	else
	{
		//Activate gravity with higher grounds.
		if (((minX < 255 && maxX > 255) && minY >= 105) || ((minX < 500 && maxX > 500) && minY >= 105) || ((minX >= 255 && maxX <= 500) && minY >= 105))
		{
			if (minY > 105)
				gameObjects[selectedObject]->decrementTy();
		}
		else
		{
			//Activate gravity until the player hits the ground.
			if ((maxX <= -105 || minX >= -25) && minY > -105)
				gameObjects[selectedObject]->decrementTy();
			
			//Activate gravity if the player is in the hole.
			if ((minX >= -105 && maxX <= -25) && minY > -250)
				gameObjects[selectedObject]->decrementTy();
			
			//Activate gravity if the player is between the ground and the hole.
			if (((minX < -105 && maxX > -105) && minY > -105) || ((minX < -25 && maxX > -25) && minY > -105))
				gameObjects[selectedObject]->decrementTy();
		}

		moveObjects(plataform);
		moveObjects2(enemy);
	}

	maxX = gameObjects[selectedObject]->getMaxX();
	maxY = gameObjects[selectedObject]->getMaxY();
	minX = gameObjects[selectedObject]->getMinX();
	minY = gameObjects[selectedObject]->getMinY();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		glPushMatrix();

		glTranslatef(gameObjects[i]->getTx(), gameObjects[i]->getTy(), 0.0f);
		glScalef(gameObjects[i]->getEx(), gameObjects[i]->getEy(), 1.0f);
		glRotatef(gameObjects[i]->getAngle(), 0.0f, 0.0f, 1.0f);

		if (selectedObject == i)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);

		gameObjects[i]->drawSkin();


		glPopMatrix();
	}

	goal->incrementAngle();

	glColor3f(1, 1, 1);

	glPushMatrix();

	glTranslatef(0, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	glLineWidth(100);
	glRasterPos2f(0, 0);

	//drawText(GLUT_BITMAP_TIMES_ROMAN_24, "Casinha");

	glPopMatrix();

	glutSwapBuffers();

	glFlush();

	detectCollision();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == 'w')
		cout << " (" << gameObjects[0]->getTx() << ", " << gameObjects[0]->getTy() << ")";
}

void initialize(void)
{
	//Define the visualization 2D window
	glMatrixMode(GL_PROJECTION);
	lleft = -250;
	rright = 250;
	ttop = 250;
	bbottom = -250;
	gluOrtho2D(lleft + panX, rright + panX, bbottom + panY, ttop + panY);
	glMatrixMode(GL_MODELVIEW);
	//gameObjects[selectedObject]->setTx(-130);
}

void alterWindowSize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;
	
	GLsizei largura = w;
	GLsizei altura = h;

	glViewport(0, 0, largura, altura);

	initialize();
}

void printCollider()
{
	cout << "Collider's Coordenates" << endl;
	cout << "maxX = " << maxX << endl;
	cout << "maxY = " << maxY << endl;
	cout << "minX = " << minX << endl;
	cout << "minY = " << minY << endl;
}

void specialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		//Limit your movements in the first hole
		if ((minX > -105 && maxX <= -25) && minY < -105)
			gameObjects[selectedObject]->decrementTx();

		//Move on the ground
		if (minY >= -105 && minX > -255)
		{
			gameObjects[selectedObject]->decrementTx();
		
			//Move the camera
			if (gameObjects[selectedObject]->getTx() >= 0)
				panX -= 10;
		}

	}

	if (key == GLUT_KEY_RIGHT)
	{
		//Limit your movements in the first hole
		if ((minX >= -105 && maxX < -25) && minY < -105)
			gameObjects[selectedObject]->incrementTx();

		//Move on the ground
		if (minY >= -105 && maxX < 1005)
		{
			gameObjects[selectedObject]->incrementTx();
		
			//Move the camera
			if (gameObjects[selectedObject]->getTx() > 0)
				panX += 10;
		}
	}

	if (key == GLUT_KEY_UP)
	{
		for (int i = 0; i < 15; i++) {
			gameObjects[selectedObject]->incrementTy();
		}
	}

	if (key == GLUT_KEY_DOWN)
	{
		printCollider();
	}

	if (key == GLUT_KEY_F5)
	{
		gameObjects[selectedObject]->decrementEy();
		gameObjects[selectedObject]->decrementEx();
	}

	if (key == GLUT_KEY_F6)
	{
		gameObjects[selectedObject]->incrementEy();
		gameObjects[selectedObject]->incrementEx();
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
		panX += 10;

	if (key == GLUT_KEY_F10)
		panX -= 10;

	if (key == GLUT_KEY_F11)
		panY += 10;

	if (key == GLUT_KEY_F12)
		panY -= 10;

	if (key == GLUT_KEY_PAGE_DOWN)
	{
		selectedObject--;
		if (selectedObject < 0)
			selectedObject = gameObjects.size() - 1;
	}

	if (key == GLUT_KEY_PAGE_UP)
	{
		selectedObject++;
		if (selectedObject > gameObjects.size() - 1)
			selectedObject = 0;
	}

	if (key == GLUT_KEY_F1)
	{
		GameObject* go = new Enemy();
		gameObjects.push_back(go);
		selectedObject = gameObjects.size() - 1;
	}

	if (key == GLUT_KEY_F2)
		gameObjects[selectedObject]->incrementAngle();

	if (key == GLUT_KEY_F3)
		gameObjects[selectedObject]->decrementAngle();

	glutPostRedisplay();
}


//Read later for collision: http://nehe.gamedev.net/tutorial/collision_detection/17005/
//Read later, interesting: http://higherorderfun.com/blog/2012/05/20/the-guide-to-implementing-2d-platformers/
//http://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_Introduction.html
int main(void)
{
	GameObject* go = new MrTetragon();
	player = go;

	//Set MrTetragon's initial position
	go->setTx(-220);
	go->setTy(-50);

	gameObjects.push_back(go);

	go = new Plataform();
	plataform = go;

	go->setTx(220);
	go->setTy(-40);

	gameObjects.push_back(go);

	go = new Enemy();
	enemy = go;

	go->setTx(450);
	go->setTy(-80);

	gameObjects.push_back(go);

	go = new Goal();
	goal= go;

	go->setTx(900);

	gameObjects.push_back(go);

	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);

	glutCreateWindow("T12D");

	glutDisplayFunc(draw);

	glutReshapeFunc(alterWindowSize);

	glutKeyboardFunc(keyboard);

	glutSpecialFunc(specialKeys);

	initialize();

	//Always draw
	//glutIdleFunc(draw);

	glutMainLoop();

	return 0;
}
