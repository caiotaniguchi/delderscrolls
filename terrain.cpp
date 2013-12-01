#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "objClasses.h"
#include <vector>
using namespace std;
void loadTerrain(vector<Object>& objectsList)
{

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glTranslatef(20,0,20);
	glRotatef(-90,1,0,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();
	objectsList.push_back(Object(20.0f,20.0f,3));

	glPushMatrix();
	glColor3f(1.0,1.0,0.2);
	glTranslatef(-10,0,20);
	glRotatef(-90,1,0,0);
	glutSolidCone(2, 10, 20, 20);
	glPopMatrix();
	objectsList.push_back(Object(-10,20,3));

}

void writeText(char * string, float x, float y)
{
	glMatrixMode( GL_PROJECTION ) ;
	glPushMatrix() ; 					// save
	glLoadIdentity();					// and clear
	glMatrixMode( GL_MODELVIEW ) ;
	glPushMatrix() ;
	glLoadIdentity() ;
	glDisable( GL_DEPTH_TEST ) ; 		// also disable the depth test so renders on top
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	
	glRasterPos2f( x,y ) ;				// center of screen. (-1,0) is center left.
	glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
	const char * p = string ;
	do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); 
	while( *(++p) );
	
	glEnable( GL_DEPTH_TEST ) ; 		// Turn depth testing back on
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glMatrixMode( GL_PROJECTION ) ;
	glPopMatrix() ; 					// revert back to the matrix I had before.
	glMatrixMode( GL_MODELVIEW ) ;
	glPopMatrix();

}