#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "objClasses.h"
#include <vector>

using namespace std;

/***************************************************************/
/* 					 Terrain Generator					 	  */
/***************************************************************/
void loadTerrain(vector<Object>& objectsList)
{
	extern float xpos[TREEAMOUNT];
	extern float zpos[TREEAMOUNT];

	// randomgen trees
	for(int i=0; i <TREEAMOUNT+1; i++)
	{
		glPushMatrix();
		glTranslatef(xpos[i],0,zpos[i]);
		glColor3f(0.545, 0.271, 0.075);
		glRotatef(-90,1,0,0);
		gluCylinder(gluNewQuadric(),0.5,0.5,5,5,5);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0,1,0.0);
		glTranslatef(xpos[i],4,zpos[i]);
		glRotatef(-90,1,0,0);
		glutSolidCone(2, 10, 10, 10);
		glPopMatrix();

		objectsList.push_back(Object(xpos[i],zpos[i],2));
	}		

	// Draw ground
	glPushMatrix();
	glColor3f(0.0,0.4,0.0);
	glBegin(GL_QUADS);
		glVertex4f(-GROUND_AREA,0,-GROUND_AREA,1);
		glVertex4f(-GROUND_AREA,0,GROUND_AREA,1);
		glVertex4f(GROUND_AREA,0,GROUND_AREA,1);
		glVertex4f(GROUND_AREA,0,-GROUND_AREA,1);
	glEnd();
	glPopMatrix();
}
