#pragma once
#include <stdlib.h>
#include <GL/glut.h>

class fish
{
public:
	float a = 1;
	float init_x = 0.0, init_y = 0.0, init_z=1.0;
	float angle;
	int fish_head = -1;//魚頭方向，預設為-1
	GLuint texture;

	fish();
	~fish();

	void drawfish();
	void bigger();

	void initpos();

	double fish_left();
	double fish_top();
};

