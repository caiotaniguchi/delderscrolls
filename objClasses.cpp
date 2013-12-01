#ifndef OBJCLASSES_H  
#define OBJCLASSES_H "objClasses.h"
#endif

#include <cmath> 
#include <stdlib.h>		   // Std Library
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include "constants.h"	   // Constant File
#include "objClasses.h"	   // Object classes File	



/***************************************************************/
/* 			General Object Class Methods Definition			   */
/***************************************************************/

Object::Object(float Posx, float Posz)
{
	x = Posx;
	z = Posz;
}

void Object::draw()
{
	glPushMatrix();
		glColor3f(1.0,1.0,1.0);
			glTranslatef(x,y,z);
		    glRotatef(directionAngle,0,1,0);
		    glutSolidTeapot(1);
	glPopMatrix();
}



/***************************************************************/
/* 			Dinamic Object Class Methods Definition			   */
/***************************************************************/

// Constructor
DinamicObj::DinamicObj(float Posx, float Posz, int hp, int ap, float sp) : Object(Posx,Posz)
{
	healthpoints = hp;
	attackpoints = ap;
	speed 		 = sp;
}

// Movement Methoda
void DinamicObj::move(float dirx, float dirz)
{	
	float angle;

	// Set a vector pointing to the position where it must go
	float directionx = dirx - x;
	float directionz = dirz - z;

	// compute the distance to the final position
	float module = sqrt(directionx*directionx + directionz*directionz);
	
	// Evaluates Angle for Rotation	
	if(directionz > 0)
		angle = int(-360*acos(directionx/module)/(2*M_PI))%360;
	else
		angle = int(360*acos(directionx/module)/(2*M_PI))%360;

	// Compute Rotation Speed
	if(directionAngle - angle < 0)
		directionAngle += 30*speed;
	if(directionAngle - angle > 0)
		directionAngle -= 30*speed;

	// If the Object is close enough he stop moving
	if (module < 2 ){ return;}

	// If the Object is not close enough, make a step
	if(sqrt(throwbackx*throwbackx + throwbackz*throwbackz) == 0)
	{
		x += speed*directionx/module;
		z += speed*directionz/module;
	}
}

// Jumping function. Set a Upward momentum if object is on the ground
void DinamicObj::jump()
{
	if(y < 4.5)					// Ground Stat at 4.0
		upSpeedMomentum = 200;
}

// Simulates Gravity
void DinamicObj::physics(float dt)
{
	float thowbackmodule = sqrt(throwbackx*throwbackx + throwbackz*throwbackz); // Calculate throwback module
	dt = dt/1000;																// Convert milliseconds to seconds
	
	// Controls Gravity
	y += upSpeedMomentum*dt + GRAVITY*dt*dt/2;
	upSpeedMomentum += GRAVITY*dt;

	// Groud Limit
	if(y<4) 
	{
		y=4;
		upSpeedMomentum = 0;
	}

	// Controls Throwback
	if(y > 4)
	{	
		// Only addv ector if throwback is different than zero 
		if(throwbackx != 0 || throwbackz != 0)
		{
			x -= throwbackx/(AIRFRICTION*thowbackmodule);
			z -= throwbackz/(AIRFRICTION*thowbackmodule);
		}
	}
	else // Null throwback if object thouch the ground
	{
		throwbackx = 0;
		throwbackz = 0;
	}
}

void DinamicObj::throwback(float playerx, float playerz)
{
	float directionx = playerx - x;
	float directionz = playerz - z;
	float module = sqrt(directionx*directionx + directionz*directionz);

	if(module <6)
	{
		upSpeedMomentum = 250;

		throwbackx = 1*(playerx - x)/module;
		throwbackz = 1*(playerz - z)/module;
	}
}

/***************************************************************/
/* 			Ennemy Object Class Methods Definition			   */
/***************************************************************/

// Classe ennemy Constructor
Ennemy::Ennemy(float Posx, float Posz, int hp, int ap, float sp) : DinamicObj(Posx,Posz, hp, ap, sp)
{
	wanderflag = false;
}

// Ennemy main function. Controls decitions based on players position
void Ennemy::run(float playerx, float playerz)
{
	float directionx = playerx - x;
	float directionz = playerz - z;
	float module = sqrt(directionx*directionx + directionz*directionz);

	// Set the ennemy on wander mode if too far away from player
	if(module >20)
	//	wander();
	1==1;
	else
	{	
		wanderflag = false;		// Turn off wandering
		move(playerx,playerz);	// Follow Player
	}

	draw();						// Draw Ennemy
}

// Wandering method. Set a random position to move if not yet setted.
void Ennemy::wander()
{

	float module = sqrt((wanderX-x)*(wanderX-x) + (wanderZ-z)*(wanderZ-z));
	if(module <3) wanderflag = false;

	if(wanderflag == false)
	{
		wanderX = x + (rand()%40) -20;
		wanderZ = z + (rand()%40) -20;
		wanderflag = true;
	}
	else
	{
		move(wanderX, wanderZ);
	}
}


/***************************************************************/
/* 			Player Object Class Methods Definition			   */
/***************************************************************/

// Player Constructor Function. Set the Teapot Y position on 4
Player::Player(float Posx, float Posz, int hp, int ap, float sp) : DinamicObj(Posx,Posz, hp, ap, sp)
{
	y = 4;
}

// Horizontal Camera Movement
void Player::yaw(int pixels)
{
	theta += pixels/180.0;
}
// Vertical Camera Movement
void Player::pitch(int pixels)
{
	phi -= pixels/180.0;
	if (phi < -M_PI) { phi = -M_PI/2; }
	if (phi > M_PI) { phi =  M_PI/2; }
}

// Camera Setting Function
void Player::LookAt()
{
	gluLookAt(x, y, z, x + cos(theta), y + sin(phi), z + sin(theta),0,1,0);
}

// Change the position of the camera on the space
void Player::updatePosition()
{
	if (walkbuffer[FRONT] == true)
	{
		x += cos(theta)/9.0;
		z += sin(theta)/9.0;
		std::cout << "FRONT | ";
	}
	
	if (walkbuffer[BACK] == true)
	{
		x -= cos(theta)/9.0;
		z -= sin(theta)/9.0;
		std::cout << "BACK | ";
	}

	if (walkbuffer[LEFT] == true)
	{
		x += sin(theta)/9.0;
		z -= cos(theta)/9.0;
		std::cout << "LEFT | ";
	}

	if (walkbuffer[RIGHT] == true)
	{
		x -= sin(theta)/9.0;
		z += cos(theta)/9.0;
		std::cout << "RIGHT | ";
	}
}

// Check all ennemies and attack the ones in codition to be attacked 
void Player::attack()
{

}