#include <stdio.h>
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include "camera.h" 
#include <iostream>
#include "constants.h"
#include "objClasses.h"

//inicializa variaveis globais
glutWindow win;
mousePos mouse;
Camera camera;
float Rotation;

//inicia inimigos
Ennemy enemmy1(-12,-12,100,100,0.05);
Ennemy enemmy2(-20,29,100,100,0.05);
Ennemy enemmy3(34,-29,100,100,0.05);

// funcao de callback para movimento do mouse sobre a janela
void mouseMotion(int x, int y)
{
	float snapThreshold = 300;

	camera.yaw(x -mouse.x);
	camera.pitch(y-mouse.y);
	
	mouse.x = x;
	mouse.y = y;
	
	// prende o mouse dentro da janela num espaco de 100x100pixels
	if(abs(x - mouse.w/2) > snapThreshold || abs(y-mouse.h/2) > snapThreshold)
	{
		mouse.x = mouse.w/2;
		mouse.y = mouse.h/2;
		// Forca o mouse a ficar no centro da janela
		glutWarpPointer(mouse.w/2, mouse.h/2);
	}
	
	glutPostRedisplay();
}

// funcao de callback de desenho principal
void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	// Modifica a posicao da camera e para onde ela aponta	
	camera.position();

	/* desenhador generico pra teste*/
	// Desenha inimigos

	enemmy1.run(camera.x,camera.z);
	enemmy2.run(camera.x,camera.z);
	enemmy3.run(camera.x,camera.z);
	

	std::cout << enemmy1.x;
	std::cout << " | ";
	std::cout << enemmy1.z ;
	std::cout << " | " ;
	std::cout << enemmy1.directionAngle;
	std::cout << "\n";
	// end desenha inimigos
	
	// Desenha chao
	glPushMatrix();
	glColor3f(0.0,1.0,0.2);
	glBegin(GL_QUADS);
		glVertex4f(-500,0,-500,1);
		glVertex4f(-500,0,500,1);
		glVertex4f(500,0,500,1);
		glVertex4f(500,0,-500,1);
	glEnd();
	glPopMatrix();
	
	// Roda bule de cha
	Rotation++;
	glPopMatrix();
	/*fim do desenhador */

	glutSwapBuffers();
}

// Funcao que configura o openGL
void initialize () 
{
	glutSetCursor(GLUT_CURSOR_NONE);
/*
    glMatrixMode(GL_PROJECTION);												// select projection matrix
    glViewport(0, 0, win.width, win.height);									// set the viewport
    glMatrixMode(GL_PROJECTION);												// set matrix mode
    glLoadIdentity();															// reset projection matrix
    GLfloat aspect = (GLfloat) win.width / win.height;
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		// set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);													// specify which matrix is the current matrix
    //glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );														// specify the clear value for the depth buffer
    glEnable( GL_DEPTH_TEST );
    //glDepthFunc( GL_LEQUAL );
    //glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints

	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 
	
/**/
    // Configura Luz
    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    // Liga Luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Liga MISC
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_COLOR_MATERIAL );
	glClearColor(0.0, 0.0, 0.6, 1.0);
    //glEnable(GL_POLYGON_OFFSET_FILL);
    ///glPolygonOffset(2.0,2.0);
    //glHint (GL_FOG_HINT, GL_NICEST);
    //glLineWidth(1);

}

// Funcao de callback para evento de pressionar botao
void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
  switch ( key ) 
  {
    case KEY_ESCAPE:        
      exit ( 0 );   
     case 'w':
        camera.walkbuffer[FRONT] = true;
        break;
     case 's':
     	camera.walkbuffer[BACK] = true;
     	break;
     case 'a':
     	camera.walkbuffer[LEFT] = true;
     	break;
     case 'd':
     	camera.walkbuffer[RIGHT] = true;
     	break;

  }
  glutPostRedisplay();
}

// Funcao de callback para evento de despressionar botao
void keyboardup ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
  switch ( key ) 
  {  
     case 'w':
     	camera.walkbuffer[FRONT] = false;
     	break;
     case 's':
     	camera.walkbuffer[BACK] = false;
     	break;
     case 'a':
     	camera.walkbuffer[LEFT] = false;
     	break;
     case 'd':
     	camera.walkbuffer[RIGHT] = false;
     	break;
  }
  glutPostRedisplay();
}

// Callback timer
void simulate(int lol){

	camera.updatePosition();
	glutPostRedisplay();
	glutTimerFunc(5,simulate,1);
}

// Callback de Redesenho do viewport
void reshape(int w, int h)
{
	mouse.w = w;
	mouse.h = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,1.0,1.5,80.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main Loop
int main(int argc, char **argv) 
{
	// set window values
	win.width = WIN_WIDTH;
	win.height = WIN_HEIGHT;
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	mouse.x = 0;
	mouse.y = 0;
	mouse.w = WIN_WIDTH;
	mouse.h = WIN_HEIGHT;

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);					// set window size
	glutCreateWindow("delderscrolls");	
	initialize();												// create Window
	glutPassiveMotionFunc(mouseMotion);	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);									// register Display Function
	glutTimerFunc(10,simulate,1);
    glutKeyboardFunc( keyboard );								// register Keyboard Handler
	glutKeyboardUpFunc(keyboardup);
	glutMainLoop();												// run GLUT mainloop
	return 0;
}
