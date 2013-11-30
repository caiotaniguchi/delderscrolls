#include "camera.h"
#include <cmath>
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include "constants.h"
#include <iostream>

// Constructor
Camera::Camera()
{
	theta = 0.0;
	phi   = 0.0;
	x     = 0;
	y     = 4;
	z     = 0;
}

// Movimentacao Horizontal da camera
void Camera::yaw(int pixels)
{
	theta += pixels/180.0;
}
// Movimentacao Vertical da camera
void Camera::pitch(int pixels)
{
	phi -= pixels/180.0;
	if (phi < -M_PI) { phi = -M_PI/2; }
	if (phi > M_PI) { phi =  M_PI/2; }
}

// Funcao que posiciona e aponta a camera
void Camera::position()
{
	gluLookAt(x, y, z, x + cos(theta), y + sin(phi), z + sin(theta),0,1,0);
}

// Altera a posicao espacial da camera
void Camera::updatePosition()
{
	if (walkbuffer[FRONT] == true)
	{
		x += cos(theta)/9.0;
		z += sin(theta)/9.0;
		std::cout << "FRONT | ";
	}
	
	if (walkbuffer[BACK] == true)
	{
		x -= cos(theta)/9.0;
		z -= sin(theta)/9.0;
		std::cout << "BACK | ";
	}

	if (walkbuffer[LEFT] == true)
	{
		x += sin(theta)/9.0;
		z -= cos(theta)/9.0;
		std::cout << "LEFT | ";
	}

	if (walkbuffer[RIGHT] == true)
	{
		x -= sin(theta)/9.0;
		z += cos(theta)/9.0;
		std::cout << "RIGHT | ";
	}
}