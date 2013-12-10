#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "objClasses.h"
#include <vector>
#include "loadObj.h"

using namespace std;

/***************************************************************/
/* 					 Terrain Generator					 	  */
/***************************************************************/
void loadTerrain(vector<Object>& objectsList)
{
	extern float xpostree[TREEAMOUNT];
	extern float zpostree[TREEAMOUNT];

	extern float xposrock[ROCKAMOUNT];
	extern float zposrock[ROCKAMOUNT];

	// randomgen trees
	for(int i=0; i <TREEAMOUNT+1; i++)
	{
		glPushMatrix();
		glTranslatef(xpostree[i],0,zpostree[i]);
		glColor3f(0.545, 0.271, 0.075);
		glRotatef(-90,1,0,0);
		gluCylinder(gluNewQuadric(),0.5,0.5,5,5,5);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0,1,0.0);
		glTranslatef(xpostree[i],4,zpostree[i]);
		glRotatef(-90,1,0,0);
		glutSolidCone(2, 10, 10, 10);
		glPopMatrix();

		objectsList.push_back(Object(xpostree[i],zpostree[i],2,6));
	}		

	
	for(int i=0; i<ROCKAMOUNT; i++)
	{
/*
	extern vector <vector<vertex> > rockModel;
	glPushMatrix();
		glColor3f(1.0,1.0,1.0);
		glTranslatef(xposrock[i],zposrock[i],0);
		
			glBegin(GL_QUADS);
	for (unsigned i = 0; i < rockModel.size(); i++) 
		{
			for (unsigned j = 0; j < rockModel[i].size(); j++){
				glVertex3f(rockModel[i][j].x,rockModel[i][j].y,rockModel[i][j].z);
			}
		}
			glEnd();	
	glPopMatrix();	
		objectsList.push_back(Object(xposrock[i],zposrock[i],1,1));
*/
		glPushMatrix();
		glColor3f(0.3,0.3,0.3);
		glTranslatef(xposrock[i],0,zposrock[i]);
		glutSolidSphere(2,10,10);
		objectsList.push_back(Object(xposrock[i],zposrock[i],2,2));
		glPopMatrix();
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
