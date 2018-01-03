#include "fish.h"
#include <stdlib.h>
#include<time.h>
#include<Windows.h>
#include <GL/glut.h>
#include"texture.h"


fish::fish()
{
	initpos();
	fish_head = -1;
}


fish::~fish()
{
}

void fish::drawfish(){
	
	//cout << x << "," << y << endl;
	glTranslatef(init_x, init_y, 1.0);
	glScalef(a, a, 1.0);
	glRotatef(angle, 0, 1, 0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-0.25f, 0.0f, 0.0f);
		glVertex3f(0.0, 0.125, 0.0);
		glVertex3f(0.25, 0.0, 0.0);
		glVertex3f(0.0, -0.125, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.25, 0.0, 0.0);
		glVertex3f(-0.05, 0.0, 0.0);
		glVertex3f(0.1, 0.2, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.25, 0.0, 0.0);
	glVertex3f(-0.05, 0.0, 0.0);
	glVertex3f(0.1, -0.2, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(0.35, 0.125, 0.0);
		glVertex3f(0.35, -0.125, 0.0);
		glVertex3f(0.23, 0.0, 0.0);
	glEnd();
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	/*glPointSize(10);
	glScalef(a, a, 1.0);
	glTranslatef(init_x, init_y, 0.0);
	glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();*/
}

void fish::bigger(){
	if (a<1.6)
		a = a + 0.2;
	
	//glutPostRedisplay();
}

void fish::initpos(){
	srand(time(NULL));
	init_x = (rand() % 7) - 3;
	Sleep(1000);
	init_y = (rand() % 7) - 3;
}

double fish::fish_left(){
	return 4 + init_x - (0.5*a);
}

double fish::fish_top(){
	return 4 - init_y - (0.25*a);
}
