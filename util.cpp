
// Include
#include <GL/gl.h>		   	   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		  	   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	  	   // The GL Utility Toolkit (GLUT) Header
#include <iostream>		  	    
#include <stdio.h>
#include "constants.h"

// Function for writing HUD on screen
void writeText(char * string, float x, float y, int FONT)
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
	
	glScalef(3.0f,3.0f,3.0f);
	const char * p = string ;
		if (FONT == TITLE_TEXT)
			{
				glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
				do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p );
				while( *(++p) );
			} 
		if (FONT == POP_UP)
			{
				glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
				glBegin(GL_QUADS);
					glVertex2f(-0.1,-0.02);
					glVertex2f(-0.1,0.02);
					glVertex2f(0.11,0.02);
					glVertex2f(0.11,-0.02);
				glEnd();

				glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
				do glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p );
				while( *(++p) );
			} 
		if(FONT == HUD_TEXT)
		{	
				glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
				// glBegin(GL_QUADS);
				// 	glVertex2f(-0.2,-0.02);
				// 	glVertex2f(-0.1,0.02);
				// 	glVertex2f(0.2,0.02);
				// 	glVertex2f(0.11,-0.02);
				// glEnd();

				glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
				do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p );
				while( *(++p) );			
		}


;		
	
	glEnable( GL_DEPTH_TEST ) ; 			// Turn depth testing back on
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glMatrixMode( GL_PROJECTION ) ;
	glPopMatrix() ; 						// revert back to the matrix I had before.
	glMatrixMode( GL_MODELVIEW ) ;
	glPopMatrix();

}



/*
 public void drawBackground( GL gl) 
 {
	gl.glMatrixMode(GL.GL_PROJECTION);
	gl.glPushMatrix();
	gl.glOrtho(0, 1, 0, 1, 0, 1);

	gl.glMatrixMode(GL.GL_MODELVIEW);
	gl.glPushMatrix();
	gl.glLoadIdentity();
	
	// No depth buffer writes for background.
	gl.glDepthMask( false );

	gl.glBindTexture( GL.GL_TEXTURE_2D, textureId[4] );
	gl.glBegin( GL.GL_QUADS ); {
	  gl.glTexCoord2f( 0f, 0f );
	  gl.glVertex2f( 0, 0 );
	  gl.glTexCoord2f( 0f, 1f );
	  gl.glVertex2f( 0, 1.0f );
	  gl.glTexCoord2f( 1.0f, 1.0f );
	  gl.glVertex2f( 1.0f, 1.0f );
	  gl.glTexCoord2f( 1.0f, 0.0f );
	  gl.glVertex2f( 1.0f, 0.0f );
	} gl.glEnd();

	gl.glDepthMask( true );

	gl.glPopMatrix();
	gl.glMatrixMode(GL.GL_PROJECTION);
	gl.glPopMatrix();
	gl.glMatrixMode(GL.GL_MODELVIEW);
      }

      */