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
#include "dinamicObjManager.h"	   // Enemies Manager Functions
#include "terrain.h"
#include "util.h"
#include "loadObj.h"

// Global Variable Inizialization
glutWindow win;
mousePos mouse;
float Rotation;
float dtEndTime;
float dtActualTime;
int gameMode = 0;
int MODEL_TYPE = TEAPOT_MODEL;
vector<string> partsFiles;


// Random tree positions array
float xpostree[TREEAMOUNT];
float zpostree[TREEAMOUNT];

// Random rock positions array
float xposrock[ROCKAMOUNT];
float zposrock[ROCKAMOUNT];

// Create Player object
Player player(0,0,100,10,1);

// Create vector of enemy for listing
std::vector<Enemy> enemyList;
std::vector<Object> objectsList;
std::vector<DinamicObj> ballList;


// Callback function for the main display
void display()
{
	

	if(player.healthpoints <1)
		gameMode = 3;

	if(gameMode == 3)
	{
		char string[300];
		sprintf(string,"GAME OVER", player.healthpoints);
		writeText(string, -0.2,-0.03,POP_UP);
	}


	// Title Screen
	if(gameMode == 0)
	{
		glClearColor(0.6, 0.6, 0.6, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		char string[300];
		sprintf(string,"DELDERSCROLLS:", player.healthpoints);
		writeText(string, -0.4,0.2,TITLE_TEXT);
		sprintf(string,"RAGE OF TEAPOTS", player.healthpoints);
		writeText(string, -0.3,0.1,TITLE_TEXT);
		sprintf(string,"PRESS ENTER TO PLAY", player.healthpoints);
		writeText(string, -0.35,-0.2,TITLE_TEXT);

	}

	// Game Mode
	if(gameMode == 1)
	{
	dtActualTime = glutGet(GLUT_ELAPSED_TIME);
	glClearColor(0.0, 0.0, 0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	char string[300];
	// Keep the actual time that this frame is been rendeered
	

	//Clear Buffers

	player.updatePosition();
	// Modify the position where the player is
	// and the position where he is lookin at
	player.LookAt();

	GLfloat light_position[] = { -GROUND_AREA, 10.0, -GROUND_AREA, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

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
	

	// Write text
	//writeText("", 0,0);
	writeText(" ", -1,-1,HUD_TEXT);
	writeText("Player 1", -0.9,0.8, HUD_TEXT);
	sprintf(string,"Health: %i", player.healthpoints);
	writeText(string, -0.9,0.9 , HUD_TEXT);
	sprintf(string,"Level: %i", player.level);
	writeText(string, -0.65,0.9,HUD_TEXT);
	sprintf(string,"Experience: %d", player.experience);
	writeText(string, -0.65,0.8 , HUD_TEXT);

	dtEndTime = glutGet(GLUT_ELAPSED_TIME);
	}

	if(gameMode == 2)
	{
		char string[300];
		sprintf(string,"GAME PAUSED:", player.healthpoints);
		writeText(string, -0.2,-0.03,POP_UP);
	}

	// Game OVER MODE


	// Final flush
	glutSwapBuffers();
	
	}

// Initialization Function that set some parameters
void initialize ()
{
	glutSetCursor(GLUT_CURSOR_NONE);

    // Light Configuration
    GLfloat amb_light[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat diffuse[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat specular[] = { 0.08, 0.08, 0.08, 1.0 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Turns lights ON
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // FOG
	float FogCol[3]={0.9f,0.9f,0.9f};
	//glEnable (GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR); // Note the 'i' after glFog - the GL_LINEAR constant is an integer.
	glFogf(GL_FOG_START, MAX_RENDER_DISTANCE -10);
 	glFogf(GL_FOG_END, MAX_RENDER_DISTANCE);
	glFogf(GL_FOG_DENSITY, 0.5f);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_COLOR_MATERIAL );
	glClearColor(0.0, 0.0, 0.6, 1.0);
    //glEnable(GL_POLYGON_OFFSET_FILL);
    //glPolygonOffset(1.0,1.0);
    glHint (GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_FASTEST);
    //glLineWidth(1);
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
	//glutPostRedisplay();
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
     case 13:
        if(gameMode == 1)
     		gameMode = 2;

     	else if(gameMode == 2)
     	     gameMode =1;

     	else if(gameMode == 0)
	     	gameMode = 1;
	    else if (gameMode == 3)
	    	{
		    	gameMode = 1;
		    	player.healthpoints = 100;
		    	player.x = 0;
		    	player.z = 0;
		    	for (int i = 0; i < enemyList.size(); i++)
		    		enemyList.erase(enemyList.begin()+i);
		    	}
     	break;
    //case '1':
    // 	import_model ("cube.obj");
    // 	MODEL_TYPE = LOADED_MODEL;
    // 	break;
    case '3':
     	import_model (partsFiles);
     	MODEL_TYPE = LOADED_MODEL;
     	break;
     case '2':
     	MODEL_TYPE = TEAPOT_MODEL;
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
  //glutPostRedisplay();
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
  //glutPostRedisplay();
}

// Callback treating mouseclick event
void mouseClick(int key, int state, int mousePositionX, int mousePositionY)
{
	switch( key )
  	{
    case 0:
    	checkhit(enemyList, player);
	   	break;

  	case 2:
  		throwball(player);
    	break;
  	}

  	// Request Redisplay
  	//glutPostRedisplay();
}

// Timer Callback function
// Request Redisplay without event
void simulate(int lol){
	checkEnemyStatus(enemyList, player);
	//
	//updateEnemies(5, enemyList, player.x, player.y);
	glutPostRedisplay();
	glutTimerFunc(33.3,simulate,33.3);
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
	//gluPerspective(45.f, 800.f / 600.f, 1.f, 60.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/***************************************************************/
/* 							 MAIN  						       */
/***************************************************************/
// Main Loop
int main(int argc, char **argv)
{
    partsFiles.push_back("cabeca.obj");
    partsFiles.push_back("tronco.obj");
    partsFiles.push_back("cintura.obj");
    partsFiles.push_back("braco_esq.obj");
    partsFiles.push_back("mao_esq.obj");
    partsFiles.push_back("espada.obj");
    partsFiles.push_back("perna_esq.obj");
    partsFiles.push_back("braco_dir.obj");
    partsFiles.push_back("mao_dir.obj");
    partsFiles.push_back("perna_dir.obj");


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
		xpostree[i] = rand() % (2*GROUND_AREA) -GROUND_AREA;
		zpostree[i] = rand() % (2*GROUND_AREA) -GROUND_AREA;
	}
// Generate random rock positions
	for(int i=0; i <ROCKAMOUNT+1; i++)
	{
		xposrock[i] = rand() % (2*GROUND_AREA) -GROUND_AREA;
		zposrock[i] = rand() % (2*GROUND_AREA) -GROUND_AREA;
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
