#ifndef TERRAIN_H  
#define TERRAIN_H "terrain.h"
#endif

#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header

void loadTerrain()
{
	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(20,20,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(-10,20,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(20,-20,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(-20,-20,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(-5,8,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.1);
	glRotatef(-90,1,0,0);
	glTranslatef(40,-10,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(-40,-40,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(10,10,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(-25,-80,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.1);
	glRotatef(-90,1,0,0);
	glTranslatef(-10,40,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(-4,-4,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();
}