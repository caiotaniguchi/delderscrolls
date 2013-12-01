#include <stdio.h>
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <iostream>		   // 
#include "constants.h"	   // Constant File
#include "objClasses.h"	   // Classes File
#include <vector>
#include "enemiesManager.h"// Enemies Manager Functions

// Global Inizialization 
glutWindow win;
mousePos mouse;
//using namespace std;
float Rotation;
float dtEndTime;
float dtActualTime;

// Create Player object
Player player(0,0,100,10,0.05);

// Create vector of enemmy for listing
std::vector<Ennemy> enemmyList;

// Create ennemies objects
// Ennemy enemmy1(+30,0,100,100,0.05);
// Ennemy enemmy2(-20,29,100,100,0.05);
// Ennemy enemmy3(34,-29,100,100,0.05);

// Callback function for passive mouse movements over the window
void mouseMotion(int x, int y)
{
	float snapThreshold = 10;

	player.yaw(x -mouse.x);
	player.pitch(y-mouse.y);
	
	mouse.x = x;
	mouse.y = y;
	
	// Reset mouse position if pointer moves more than snapThreshold from the center
	if(abs(x - mouse.w/2) > snapThreshold || abs(y-mouse.h/2) > snapThreshold)
	{
		mouse.x = mouse.w/2;
		mouse.y = mouse.h/2;
		// Warp mouse to the center of the window
		glutWarpPointer(mouse.w/2, mouse.h/2);
	}
	// Request redisplay
	glutPostRedisplay();
}

// Callback function for the main display
void display() 
{	
	// Keep the actual time that this frame is been rendeered
	dtActualTime = glutGet(GLUT_ELAPSED_TIME);

	//Clear Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	// Modify the position where the player is 
	// and the position where he is lookin at
	player.LookAt();
	
	// Test Drawings
	// Draw Ennemies
	player.physics(dtActualTime - dtEndTime);
	updateEnemies(dtActualTime - dtEndTime, enemmyList, player.x, player.z);
	//enemmyList[0].run(player.x,player.z);

	// Debugg Strings
	std::cout << "TEAPOTS HEALTH: ";
	std::cout << enemmyList[0].healthpoints;
	std::cout << " | " ;
	std::cout << enemmyList[1].healthpoints;
	std::cout << " | " ;
	std::cout << enemmyList[2].healthpoints;
	std::cout << "\n";
	// Draw ennemies end
	
	// Draw ground
	glPushMatrix();
	glColor3f(0.0,1.0,0.2);
	glBegin(GL_QUADS);
		glVertex4f(-500,0,-500,1);
		glVertex4f(-500,0,500,1);
		glVertex4f(500,0,500,1);
		glVertex4f(500,0,-500,1);
	glEnd();
	glPopMatrix();
	
	glPopMatrix();
	// Drawer end 

	glutSwapBuffers();
	// Keep the time when the end of the frame was finished
	dtEndTime = glutGet(GLUT_ELAPSED_TIME);
}

// Initialization Function that set some parameters 
void initialize () 
{
	glutSetCursor(GLUT_CURSOR_NONE);

    // Light Configuration
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

// Callback funtion for down key keyboard events
void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
  switch ( key ) 
  {
    case KEY_ESCAPE:        
      exit ( 0 );   
     case 'w':
        player.walkbuffer[FRONT] = true;
        break;
     case 's':
     	player.walkbuffer[BACK] = true;
     	break;
     case 'a':
     	player.walkbuffer[LEFT] = true;
     	break;
     case 'd':
     	player.walkbuffer[RIGHT] = true;
     	break;
     case 32:
     	player.jump();

  }
  // Request Redisplay
  glutPostRedisplay();
}

// Callback function for UP key Keyboard events
void keyboardup ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
  switch ( key ) 
  {  
     case 'w':
     	player.walkbuffer[FRONT] = false;
     	break;
     case 's':
     	player.walkbuffer[BACK] = false;
     	break;
     case 'a':
     	player.walkbuffer[LEFT] = false;
     	break;
     case 'd':
     	player.walkbuffer[RIGHT] = false;
     	break;
  }
  // Request Redisplay
  glutPostRedisplay();
}

// Callback treating mouseclick event
void mouseClick(int key, int state, int mousePositionX, int mousePositionY)
{
	switch( key ) 
  	{  
    case 0:
    	//enemmy1.throwback(player.x,player.z);
    	//enemmy1.attack();
    	checkhit(enemmyList, player.x, player.z, player.attackpoints, player.theta);
    	
    	break;
  	case 2:
  		//enemmyList[0].jump();
    	//makejump(0, enemmyList);
    	break;
  	}
  	// Request Redisplay
  	glutPostRedisplay();
}

// Timer Callback function
// Request Redisplay without event
void simulate(int lol){

	player.updatePosition();
	//updateEnemies(5, enemmyList, player.x, player.y);
	glutPostRedisplay();
	glutTimerFunc(1,simulate,1);
}

// Callback for reshaping the window's viewport 
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
	// Set Windows Values
	win.width = WIN_WIDTH;
	win.height = WIN_HEIGHT;
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	// Set mouse star position
	mouse.x = 0;
	mouse.y = 0;
	mouse.w = WIN_WIDTH;
	mouse.h = WIN_HEIGHT;

	// Add the Ennemies to the vector
	enemmyList.push_back(Ennemy(+15,0,100,100,0.05));
	enemmyList.push_back(Ennemy(-25,0,100,100,0.05));
	enemmyList.push_back(Ennemy(+25,-25,100,100,0.05));

	// Start OpenGL Machine
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);					// set window size
	glutCreateWindow("delderscrolls");	
	initialize();												// create Window
	glutPassiveMotionFunc(mouseMotion);							// Use the pointer position to controle the camera
	glutMouseFunc(mouseClick);									// Mouse click event callback
	glutReshapeFunc(reshape);									// windows distorcion evnet callback
	glutDisplayFunc(display);									// register Display Function
	glutTimerFunc(10,simulate,1);								// Register Timer Function
    glutKeyboardFunc( keyboard );								// register Keyboard DOWN Handler
	glutKeyboardUpFunc(keyboardup);								// register keyboard UP Handler
	glutMainLoop();												// run GLUT mainloop
	return 0;
}
