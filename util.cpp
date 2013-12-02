
// Include
#include <GL/gl.h>		   	   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		  	   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	  	   // The GL Utility Toolkit (GLUT) Header

#include <iostream>		  	    
#include <stdio.h>

// Function for writing HUD on screen
void writeText(char * string, float x, float y)
{
	glMatrixMode( GL_PROJECTION ) ;
	glPushMatrix() ; 						// save
	glLoadIdentity();						// and clear
	glMatrixMode( GL_MODELVIEW ) ;
	glPushMatrix() ;
	glLoadIdentity() ;
	glDisable( GL_DEPTH_TEST ) ; 			// also disable the depth test so renders on top
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	
	glRasterPos2f( x,y ) ;					// center of screen. (x,y) is center left.
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	const char * p = string ;
	do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); 
	while( *(++p) );
	
	glEnable( GL_DEPTH_TEST ) ; 			// Turn depth testing back on
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glMatrixMode( GL_PROJECTION ) ;
	glPopMatrix() ; 						// revert back to the matrix I had before.
	glMatrixMode( GL_MODELVIEW ) ;
	glPopMatrix();

}