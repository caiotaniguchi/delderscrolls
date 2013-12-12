#include <cmath>
#include <stdlib.h>		   // Std Library
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include "constants.h"	   // Constant File
#include "objClasses.h"	   // Object classes File
#include <vector>
#include <iostream>
#include "loadObj.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

/***************************************************************/
/* 			General Object Class Methods Definition			   */
/***************************************************************/

Object::Object(float Posx, float Posz)
{
	x = Posx;
	z = Posz;
		legCounter = 0;

}

Object::Object(float Posx, float Posz, float radius, float height)
{
	x = Posx;
	z = Posz;
	colisionRadius = radius;
	colisionHeight = height;
	legCounter = 0;

}

void Object::draw()
{
	using namespace std;
	extern vector<vector<vector<vertex> > > objModel;




	glPushMatrix();

		glColor3f(1.0,0.0,0.0);
		glTranslatef(x,y,z);
		//glRotatef(directionAngle,0,1,0);
		glRotatef(directionAngle+150,0,1,0);


	for (int i = 0; i < objModel.size(); i++){
        glPushMatrix();

        switch (i) {
            case 0:
                glColor3f(1.0,1.0,0.0);
                break;
            case 1:
                glColor3f(1.0,0.0,0.0);
                break;
            case 2:
                glColor3f(0.0,0.0,1.0);
                break;
            case 3:
                glColor3f(1.0,0.0,0.0);
                break;
            case 4:
                glColor3f(1.0,1.0,0.0);
                break;
            case 5:
                glColor3f(0.827,0.827,0.827);
                break;
            case 6:
                glColor3f(0.0,0.0,1.0);
                glTranslatef(0,1,0);
                glRotatef(legCounter2,1,0,1);
                glTranslatef(0,-1,0);
                break;
            case 7:
                glColor3f(1.0,0.0,0.0);
                break;
            case 8:
                glColor3f(1.0,1.0,0.0);
                break;
            case 9:
                glColor3f(0.0,0.0,1.0);
                glTranslatef(0,1,0);
                glRotatef(-legCounter2,1,0,1);
                glTranslatef(0,-1,0);
                break;
          }

    glBegin(GL_TRIANGLES);

        for (int j = 0; j < objModel[i].size(); j++)
            for (int k = 0; k < objModel[i][j].size(); k++)
                glVertex3f(objModel[i][j][k].x, objModel[i][j][k].y, objModel[i][j][k].z);
    glEnd();

    glPopMatrix();
    }


	glPopMatrix();
}


void Object::draw3()
{
	glPushMatrix();
		glColor3f(1.0,1.0,1.0);
			glTranslatef(x,y,z);
		    glRotatef(directionAngle,0,1,0);
		    glutSolidTeapot(1);
	glPopMatrix();
}



void Object::draw2()
{
	glPushMatrix();
		glColor3f(1.0,0,0);
			glTranslatef(x,y,z);
		    glRotatef(directionAngle,0,1,0);
		    glutSolidSphere(0.5,10,10);
	glPopMatrix();
}


/***************************************************************/
/* 			Dynamic Object Class Methods Definition			   */
/***************************************************************/

// Constructor
DinamicObj::DinamicObj(float Posx, float Posz, int hp, int ap, float sp) : Object(Posx,Posz)
{
	healthpoints = hp;
	attackpoints = ap;
	speed 		 = sp;
}

DinamicObj::DinamicObj(float Posx, float Posz, float Posy,float upBall, float xBall, float zBall, float currenttime) : Object(Posx,Posz)
{
	creationTime = currenttime;
	y = Posy;
	upSpeedMomentum = upBall;		// Upward speed (for jumping)
	throwbackx = -xBall;
	throwbackz = -zBall;

}

// Collision Detection:
bool DinamicObj::detectColision()
{
	extern std::vector<Object> objectsList;

	float radiusx;
	float radiusz;
	float lastx = x;
	float lastz = z;

	// Check invisble wall
	if(abs(x)>GROUND_AREA-2)
		{
			x = lastx;
			return true;
		}

	if(abs(z)>GROUND_AREA-2)
		{
			z = lastz;
			return true;
		}


	// evaluates for fixed objects
	for(int i =0 ; i < objectsList.size(); i++)
	{
		radiusx = x - objectsList[i].x;
		radiusz = z - objectsList[i].z;

		float module = sqrt(radiusx*radiusx + radiusz*radiusz);

		if (module <= objectsList[i].colisionRadius && y < objectsList[i].colisionHeight)
		{
			x += radiusx/module;
			z += radiusz/module;
			return true;
			// std::cout << "yey\n";//return true;
		}
	}


	return false;
}

// Detection Collision for moving objects
bool DinamicObj::detectMovingColision(bool doesHit)
{
	extern std::vector<Enemy> enemyList;

	float radiusx;
	float radiusz;

	// evaluates for moving objects
	for(int i =0 ; i < enemyList.size(); i++)
	{
		radiusx = x - enemyList[i].x;
		radiusz = z - enemyList[i].z;

		float module = sqrt(radiusx*radiusx + radiusz*radiusz);

		// skip if enmylist is yourself
		if(module == 0) continue;

		if (module <= enemyList[i].colisionRadius && enemyList[i].y < GROUNDLIMIT && (enemyList[i].colisionHeight > y > enemyList[i].y) )
		{
			if(doesHit == true) enemyList[i].healthpoints -= BALLHITPOINTS;

			x = enemyList[i].x + enemyList[i].colisionRadius*(radiusx/module);
			z = enemyList[i].z + enemyList[i].colisionRadius*(radiusz/module);
			return true;
			//std::cout << "yey\n";//return true;
		}
	}

	return false;
}

// Movement Method
void DinamicObj::move(float dirx, float dirz)
{
	float angle;
	float lastx = x;
	float lastz = z;
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
		directionAngle += 60*speed;
	if(directionAngle - angle > 0)
		directionAngle -= 60*speed;

	// If the Object is close enough he stop moving
	if(module < 3){return;}

	// If the Object is not close enough, make a step
	if(sqrt(throwbackx*throwbackx + throwbackz*throwbackz) == 0)
	{
		x += speed*directionx/module;
		z += speed*directionz/module;
		if(detectColision() || detectMovingColision(NOHIT))
		{
			x -= THROWPOWER*directionx/module;
			z -= THROWPOWER*directionz/module;
		}
	}
}

// Jumping function. Set a Upward momentum if object is on the ground
void DinamicObj::jump()
{
	if(y < GROUNDLIMIT +0.5)					// Ground Stat at 4.0
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
	if(y<GROUNDLIMIT)
	{
		y=GROUNDLIMIT;
		upSpeedMomentum = 0;
	}

	// Controls Throwback
	if(y > GROUNDLIMIT)
	{
		// Only add vector if throwback is different than zero
		if(throwbackx != 0 || throwbackz != 0)
		{
			if(!detectColision())
			{
				x -= throwbackx/(AIRFRICTION*thowbackmodule);
				z -= throwbackz/(AIRFRICTION*thowbackmodule);
			}
		}
	}
	else // Null throwback if object thouch the ground
	{
		throwbackx = 0;
		throwbackz = 0;
	}
}

// Function to throw and object back
void DinamicObj::throwback(float playerx, float playerz)
{
	float directionx = playerx - x;
	float directionz = playerz - z;
	float module = sqrt(directionx*directionx + directionz*directionz);

	if(module <6)
	{
		upSpeedMomentum = 200;

		throwbackx = 3*(playerx - x)/module;
		throwbackz = 3*(playerz - z)/module;
	}
}

/***************************************************************/
/* 			Enemy Object Class Methods Definition			   */
/***************************************************************/

// Classe Enemy Constructor
Enemy::Enemy(float Posx, float Posz, float radius,int hp, int ap, float sp, float height) : DinamicObj(Posx,Posz, hp, ap, sp)
{
	colisionHeight = height;
	wanderflag = false;
	y=GROUNDLIMIT;
	colisionRadius = radius;

}

// Enemy main function. Controls decitions based on players position
void Enemy::run(Player &player)
{
	extern int MODEL_TYPE;

	float directionx = player.x - x;
	float directionz = player.z - z;
	float module = sqrt(directionx*directionx + directionz*directionz);

	// Set the Enemy on wander mode if too far away from player
	if(module < ATTACK_DISTANCE && (glutGet(GLUT_ELAPSED_TIME) - lastAttackTime) > COOLDOWNTIME_MS)
		{
			lastAttackTime = glutGet(GLUT_ELAPSED_TIME);
			player.healthpoints -=1;
		}

	if(module >20)
		wander();
	//1==1;
	else
	{
		wanderflag = false;		// Turn off wandering
		move(player.x,player.z);	// Follow Player
		    legCounter2 = 30*sin(legCounter/8);
    		legCounter++;
	}

	if(MODEL_TYPE == LOADED_MODEL)
		draw();						// Draw Enemy
	if(MODEL_TYPE == TEAPOT_MODEL)
		draw3();
}

// Wandering method. Set a random position to move if not yet setted.
void Enemy::wander()
{

	float module = sqrt((wanderX-x)*(wanderX-x) + (wanderZ-z)*(wanderZ-z));
	if(module <3) wanderflag = false;

	if(wanderflag == false)
	{
		wanderX = (rand()%(2*GROUND_AREA-10))- GROUND_AREA;
		wanderZ = (rand()%(2*GROUND_AREA-10)) -GROUND_AREA;
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
	y = GROUNDLIMIT;
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
	// position and points the camera to the desired position
	gluLookAt(x, y+4, z, x + cos(theta), y+ 4 + sin(phi), z + sin(theta),0,1,0);
}

// Change the position of the camera on the space
void Player::updatePosition()
{
	// Keep the last position in case of colision
	float lastx = x;
	float lastz = z;

	if(jumpBuffer == true)	jump();

	// Increases Speed
	if(shiftBuffer == true)
		speed = SPRINT_SPEED;
	else speed = 1;

	// Keep a certain height from the ground
	if(y<GROUNDLIMIT) y=GROUNDLIMIT;

	// Check if there is any movment to be done
	if (walkbuffer[FRONT] == true)
	{
		x += speed*cos(theta)/9.0;
		z += speed*sin(theta)/9.0;
	}

	if (walkbuffer[BACK] == true)
	{
		x -= speed*cos(theta)/9.0;
		z -= speed*sin(theta)/9.0;
	}

	if (walkbuffer[LEFT] == true)
	{
		x += speed*sin(theta)/9.0;
		z -= speed*cos(theta)/9.0;
	}

	if (walkbuffer[RIGHT] == true)
	{
		x -= speed*sin(theta)/9.0;
		z += speed*cos(theta)/9.0;
	}

	// Chcek if there is a colision
	if(detectColision()  || detectMovingColision(NOHIT))
	{
		x = lastx;
		z = lastz;
	}
}
