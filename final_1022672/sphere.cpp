#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<cmath>
#include"fish.h"
#include"texture.h"
#define pi 3.14

using namespace std;

int size = 0;
fish num[3];
float fix_initx, fix_inity;
float fix_moving_initx[3] = { 0.0, 0.0, 0.0 }, fix_moving_inity[3] = { 0.0, 0.0, 0.0 };
float min_dis = 8;
int min_index = 0;

float t_touching = 0.0;//按下滑鼠後於移動的時間
float t_moving = 0.0;
bool first_run[3] = { true, true, true };
bool first_initrun = true;
bool mouse_down = false;//控制滑鼠是否按下
bool mouse_canpress = true;//魚在移動中，滑鼠不能按
bool mouse_press = false;
int mousepos_x, mousepos_y;


int x[3], y[3];
int a[3] = { 0, 0, 0 };

GLuint texture;


void display(void)
{
/* Displays all three modes, side by side */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	texture = LoadBitmap("fish.bmp");
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(-4.0, -4.5);
	glTexCoord2d(1.0, 0.0); glVertex2d(+4.0, -4.5);
	glTexCoord2d(1.0, 1.0); glVertex2d(+4.0, +4.0);
	glTexCoord2d(0.0, 1.0); glVertex2d(-4.0, +4.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	


	glPushMatrix();
	num[0].drawfish();
	//cout << "num[0]:" << num[0].init_x << "," << num[0].init_y << endl;
	glPopMatrix();

	
	glPushMatrix();
	num[1].drawfish();
	//cout << "num[1]:" << num[1].init_x << "," << num[1].init_y << endl;
	glPopMatrix();



	glPushMatrix();
	num[2].drawfish();
	//cout << "num[2]:" << num[2].init_x << "," << num[2].init_y << endl;
	glPopMatrix();

	glFlush();
}


/*void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
            4.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
	
    //display();
}*/

/*void getmousepos(){
	POINT apos;
	GetCursorPos(&apos);

}*/

void myinit()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f (0.0, 0.0, 0.0);
}


void mymouse(int button, int state, int x, int y){
	float distance[3] = { 0.0, 0.0, 0.0 };
	if (mouse_canpress){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			mouse_press = true;
			mousepos_x = x;
			mousepos_y = y;
			min_dis = 8;
			min_index = 0;
			for (int i = 0; i < 3; i++){
				distance[i] = sqrt(pow(num[i].init_x - ((x-250)/62.5), 2) + pow(num[i].init_y - ((250-y)/62.5), 2));
				//cout << "(dis)num[" << i << "] =" << distance[i] << endl;
			}
			for (int i = 0; i < 3; i++){
				if (distance[i] < min_dis){
					min_dis = distance[i];
					min_index = i;
				}		
			}
			fix_initx = num[min_index].init_x;
			fix_inity = num[min_index].init_y;
			mouse_down = true;
			mouse_canpress = false;
		
		}

	}
	
}

void resize(int width, int height) {
	// we ignore the params and do:
	glutReshapeWindow(500, 500);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
		glOrtho(-4.0, 4.0, -4.0 * (GLfloat)height / (GLfloat)width,
		4.0 * (GLfloat)height / (GLfloat)width, -10.0, 10.0);
	else
		glOrtho(-4.0 * (GLfloat)width / (GLfloat)height,
		4.0 * (GLfloat)width / (GLfloat)height, -4.0, 4.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	//display();

}


void init_run(){
	for (int i = 0; i < 3; i++){
		a[i] = rand() % 4;
		x[i] = 0;
		y[i] = 0;
		fix_moving_initx[i] = 0;
		fix_moving_inity[i] = 0;
	}

	cout << "a[0]:" << a[0] << endl;
}

void idle(){
	
	t_moving = t_moving + 0.1;
	if (mouse_down){
		//cout << "t=" << t_touching << endl;
		if (t_touching < 4.9998){
			if ((((mousepos_x - 250) / 62.5) > fix_initx) && (num[min_index].fish_head == -1)){
				num[min_index].angle = 180;
				num[min_index].fish_head = 1;
			}
			if (((mousepos_x - 250) / 62.5) < fix_initx && num[min_index].fish_head == 1){
				num[min_index].angle = 0;
				num[min_index].fish_head = -1;
			}
			t_touching = t_touching + 0.2;
			//float t_plus = (-1)*(t-2.5)*(t-2.5)/10+0.625;
			//cout << "t_plus=" << t_plus << endl;
			num[min_index].init_x = fix_initx+((mousepos_x - 250) / 62.5 - fix_initx)*t_touching / 5.0;
			num[min_index].init_y = fix_inity + (((250 - mousepos_y) / 62.5) - fix_inity)*t_touching / 5.0;// +t_plus;
			
			cout << "t=" << t_touching << "," << "x=" << (mousepos_x - 250) / 62.5 << "," << "y=" << ((250 - mousepos_y) / 62.5) << ","
				<< fix_initx << "," << fix_inity << "," << endl;
			glutPostRedisplay();
		}
		else{
			num[min_index].bigger();
			mouse_down = false;
			mouse_canpress = true;
			mouse_press = false;
			glutPostRedisplay();
			t_touching = 0;
			cout << "t=" << t_touching << "," << fix_initx << "," << fix_inity << "," << mouse_down  << endl;
		}
			
	}
	if (first_initrun){
		init_run();
		first_initrun = false;
		//cout << "a[0]=" << a[0] << "a[1]=" << a[1] << "a[2]=" << a[2] << endl;
	}

	if (t_moving < 5){
		for (int i = 0; i < 3; i++){
			switch (a[i]){
				case 0:
					if (mouse_press){
						first_run[i] = true;
						first_initrun = true;
						t_moving = 0;
						break;
					}
					break;
				case 1:
					if (mouse_press){
						first_run[i] = true;
						first_initrun = true;
						t_moving = 0;
						break;
					}
					if (first_run[i]) {
						x[i] = ((rand() % 7) - 3);
						fix_moving_initx[i] = num[i].init_x;
						first_run[i] = false;
						cout << "目標=" << x[0] << "," << "初始點:" << fix_moving_initx[0] << endl;
					}
					if (t_moving <= 4){
						if ((x[i] > fix_moving_initx[i]) && (num[i].fish_head == -1)){
							num[i].angle = 180;
							num[i].fish_head = 1;
						}
						if (x[i] < fix_moving_initx[i] && num[i].fish_head == 1){
							num[i].angle = 0;
							num[i].fish_head = -1;
						}
							
						num[i].init_x = fix_moving_initx[i] + ((x[i] - fix_moving_initx[i])*(t_moving / 4));
						cout << "num[0]=(" << num[0].init_x << "," << num[0].init_y << ")," << endl;
						//cout << "目標=" << x[0] << "," << "初始點:" << fix_moving_initx[0] << endl;
					}

					break;
				case 2:
					if (mouse_press){
						first_run[i] = true;
						first_initrun = true;
						t_moving = 0;
						break;
					}
					if (first_run[i]) {
						y[i] = (rand() % 7) - 3;
						fix_moving_inity[i] = num[i].init_y;
						first_run[i] = false;
					}
					if (t_moving <= 4){
						if ((y[i] > fix_moving_inity[i]) && (num[i].fish_head == -1)){
							num[i].angle = 180;
							num[i].fish_head = 1;
						}
						if (y[i] < fix_moving_initx[i] && num[i].fish_head == 1){
							num[i].angle = 0;
							num[i].fish_head = -1;
						}

						num[i].init_y = fix_moving_inity[i] + (((y[i] - fix_moving_inity[i]))*(t_moving / 4));

					}
					break;
				case 3:
					if (mouse_press){
						first_run[i] = true;
						first_initrun = true;
						t_moving = 0;
						break;
					}
					if (first_run[i]) {
						x[i] = (rand() % 7) - 3;
						if (num[i].init_y >= 3)
							y[i] = 2;
						else if (num[i].init_y <= -3)
							y[i] = -2;
						else
							y[i] = (rand() % 7) - 3;
						fix_moving_initx[i] = num[i].init_x;
						fix_moving_inity[i] = num[i].init_y;
						first_run[i] = false;
					}
					if (t_moving <= 4){
						if ((x[i] > fix_moving_initx[i]) && (num[i].fish_head == -1)){
							num[i].angle = 180;
							num[i].fish_head = 1;
						}
						if (x[i] < fix_moving_initx[i] && num[i].fish_head == 1){
							num[i].angle = 0;
							num[i].fish_head = -1;
						}
						num[i].init_x = fix_moving_initx[i] + (((x[i] - fix_moving_initx[i]))*(t_moving / 4));
						num[i].init_y = fix_moving_inity[i] + (((y[i] - fix_moving_inity[i]))*(t_moving / 4));
					}
					
					break;
				default:
					break;
			}
		}
	}

		if (t_moving + 0.019999999>5){
			t_moving = 0;
			first_run[0] = true;
			first_run[1] = true;
			first_run[2] = true;
			first_initrun = true;
		}

	glutPostRedisplay();
}

void menu(int id){
	if (id == 1){
		for (int i = 0; i < 3; i++){
			num[i].a = 1.0;
			glutPostRedisplay();
		}
	}
}


void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("sphere");
    myinit();


	glutCreateMenu(menu);
	glutAddMenuEntry("restart", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMouseFunc(mymouse);
    glutReshapeFunc(resize);
	glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMainLoop();
}
