/***************************************************************/
/* 															   */
/* 			DELDERSCROLLS: REVENGE OF THE TEAPOTS			   */
/* 															   */
/* 			by:	Adriano Soares								   */
/* 			    Caio Taniguchi								   */
/* 				Pedro Correa								   */
/* 															   */
/* 															   */
/* 					DEL - UFRJ - 2013/2						   */
/* 															   */
/***************************************************************/

// Include
#include <GL/gl.h>		   	   // Open Graphics Library (OpenGL) header
#include <GL/glu.h>		  	   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	  	   // The GL Utility Toolkit (GLUT) Header

#include <iostream>		  	    
#include <stdio.h>
#include <vector>	

#include "objClasses.h"		   // Classes File
#include "constants.h"		   // Constant File
#include "enemiesManager.h"	   // Enemies Manager Functions
#include "terrain.h"
#include "util.h"

// Global Variable Inizialization 
glutWindow win;
mousePos mouse;
float Rotation;
float dtEndTime;
float dtActualTime;

// Random tree positions array
float xpos[TREEAMOUNT];
float zpos[TREEAMOUNT];

// Create Player object
Player player(0,0,100,10,1);

// Create vector of enemy for listing
std::vector<Enemy> enemyList;
std::vector<Object> objectsList;
std::vector<DinamicObj> ballList;


// Callback function for the main display
void display() 
{	
	char string[300];
	// Keep the actual time that this frame is been rendeered
	dtActualTime = glutGet(GLUT_ELAPSED_TIME);

	//Clear Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	// Modify the position where the player is 
	// and the position where he is lookin at
	player.LookAt();
	
	// Draw Enemies
	player.physics(dtActualTime - dtEndTime);
	updateEnemies(dtActualTime - dtEndTime, enemyList, player);
	updateBalls(dtActualTime - dtEndTime);
	// Draw ennemies
	
	// Load and place objects in the terrain
	loadTerrain(objectsList);


	// Drawer end 
	glPopMatrix();
	// Keep the time when the end of the frame was finished
	dtEndTime = glutGet(GLUT_ELAPSED_TIME);

	// Write text
	//writeText("", 0,0);
	writeText(" ", -1,-1);
	writeText("Player 1", -0.9,0.8);
	sprintf(string,"Health: %i", player.healthpoints);
	writeText(string, -0.9,0.9);
	sprintf(string,"Level: %i", player.level);
	writeText(string, -0.65,0.9);
	sprintf(string,"Experience: %d", player.experience);
	writeText(string, -0.65,0.8);

	// Final flush
	glutSwapBuffers();
	}

// Initialization Function that set some parameters 
void initialize () 
{
	glutSetCursor(GLUT_CURSOR_NONE);

    // Light Configuration
    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Turns lights ON 
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // FOG
	//glEnable (GL_FOG);
    //glFogi (GL_FOG_MODE, GL_EXP2);
    //glFogf (GL_FOG_COLOR,10);
    //fglFogf (GL_FOG_DENSITY, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable( GL_COLOR_MATERIAL );
	glClearColor(0.0, 0.0, 0.6, 1.0);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0,1.0);
    glHint (GL_FOG_HINT, GL_NICEST);
    glLineWidth(1);
}

/***************************************************************/
/* 						INPUTS CALLBACKS 		 	 		   */
/***************************************************************/

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

// Callback funtion for down key keyboard events
void keyboard (unsigned char key, int mousePositionX, int mousePositionY )		
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
     
    }

  if(key == 32) player.jumpBuffer = true;

  switch( glutGetModifiers() )
  {
  	case GLUT_ACTIVE_SHIFT:
  		player.shiftBuffer = true;
   		break;
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

  if(key == 32) player.jumpBuffer = false;

  switch( glutGetModifiers() )
  {
  	case !GLUT_ACTIVE_SHIFT:
  		player.shiftBuffer = false;
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
    	//enemy1.throwback(player.x,player.z);
    	//enemy1.attack();
    	checkhit(enemyList, player);
    	
    	break;
  	case 2:

  		throwball(player);
  		//enemyList[0].jump();
    	//makejump(0, enemyList);
  		//player.jump();// = true;
    	break;
  	}
  	// Request Redisplay
  	glutPostRedisplay();
}

// Timer Callback function
// Request Redisplay without event
void simulate(int lol){

	player.updatePosition();
	//updateEnemies(5, enemyList, player.x, player.y);
	glutPostRedisplay();
	glutTimerFunc(1,simulate,1);
}

/***************************************************************/
/* 						Reshape Callback 					   */
/***************************************************************/
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

/***************************************************************/
/* 							 MAIN  						       */
/***************************************************************/
// Main Loop
int main(int argc, char **argv) 
{
	// Set Windows Values
	win.width = WIN_WIDTH;
	win.height = WIN_HEIGHT;
	win.field_of_view_angle = FIELDOFVIEWANGLE;
	win.z_near = MIN_RENDER_DISTANCE;
	win.z_far = MAX_RENDER_DISTANCE;

	// Set mouse star position
	mouse.x = 0;
	mouse.y = 0;
	mouse.w = WIN_WIDTH;
	mouse.h = WIN_HEIGHT;

	// Generate random tree positions
	for(int i=0; i <TREEAMOUNT+1; i++)
	{
		xpos[i] = rand() % (2*GROUND_AREA) -GROUND_AREA;
		zpos[i] = rand() % (2*GROUND_AREA) -GROUND_AREA;
	}

	// Start OpenGL Machine
	glutInit(&argc, argv);                                  		    // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  		// Display Mode
	glutInitWindowSize(win.width,win.height);							// set window size
	glutCreateWindow("delderscrolls: the revenge of the teapots");		// create Window
	initialize();												
	glutPassiveMotionFunc(mouseMotion);
	glutWarpPointer(mouse.w/2, mouse.h/2);								// Use the pointer position to controle the camera
	glutMouseFunc(mouseClick);											// Mouse click event callback
	glutReshapeFunc(reshape);											// windows distorcion evnet callback
	glutDisplayFunc(display);											// register Display Function
	glutTimerFunc(10,simulate,1);										// Register Timer Function
    glutKeyboardFunc( keyboard );										// register Keyboard DOWN Handler
	glutKeyboardUpFunc(keyboardup);										// register keyboard UP Handler
	glutMainLoop();														// run GLUT mainloop
	return 0;
}
