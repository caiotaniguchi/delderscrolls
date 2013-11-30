#ifndef OBJCLASSES_H  
#define OBJCLASSES_H "objClasses.h"
#endif

#include <cmath> 
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include "constants.h"
#include "objClasses.h"
#include <stdlib.h>

// Constructor
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

/***********************end of object*********************/

// DinamicObj:
// Constructor
DinamicObj::DinamicObj(float Posx, float Posz, int hp, int ap, float sp) : Object(Posx,Posz)
{
	healthpoints = hp;
	attackpoints = ap;
	speed 		 = sp;
}

void DinamicObj::move(float dirx, float dirz)
{
	directionx = dirx - x;
	directionz = dirz - z;

	float modulo = sqrt(directionx*directionx + directionz*directionz);
	float angle;
	
	if(directionz > 0)
		angle = int(-360*acos(directionx/modulo)/(2*M_PI))%360;
	else
		angle = int(360*acos(directionx/modulo)/(2*M_PI))%360;

	if(directionAngle - angle < 0)
		directionAngle += 30*speed;
	if(directionAngle - angle > 0)
		directionAngle -= 30*speed;

	if (modulo < 2){ return;}

	x += speed*directionx/modulo;
	z += speed*directionz/modulo;
}

void DinamicObj::jump()
{
	if(y < 4.5)
	directiony = 200;
}

void DinamicObj::physics(float dt)
{
	dt = dt/1000;
	float gravity = -5000;	
	y += directiony*dt + gravity*dt*dt/2;
	directiony += gravity*dt;

	if(y<4) y=4;
	if(y<4) directiony =0;
}

/*********************************enddinami*******************/

// Classe ennemy
Ennemy::Ennemy(float Posx, float Posz, int hp, int ap, float sp) : DinamicObj(Posx,Posz, hp, ap, sp)
{
	wanderflag = false;
}

void Ennemy::run(float playerx, float playerz)
{
	directionx = playerx - x;
	directionz = playerz - z;
	float modulo = sqrt(directionx*directionx + directionz*directionz);

	// controla qual tipo de movimento vai fazer
	if(modulo >20)
	//	wander(); 				// movimenteo aleatorio
	1==1;
	else
	{	
		wanderflag = false;
		move(playerx,playerz);	// vai atras do jogador
	}

	draw();
}

void Ennemy::wander()
{

	float modulo = sqrt((wanderX-x)*(wanderX-x) + (wanderZ-z)*(wanderZ-z));
	if(modulo <3) wanderflag = false;

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


/***********************END ENNEMY****************************/

//Player
Player::Player(float Posx, float Posz, int hp, int ap, float sp) : DinamicObj(Posx,Posz, hp, ap, sp)
{
	y = 4;
}

// Movimentacao Horizontal da camera
void Player::yaw(int pixels)
{
	theta += pixels/180.0;
}
// Movimentacao Vertical da camera
void Player::pitch(int pixels)
{
	phi -= pixels/180.0;
	if (phi < -M_PI) { phi = -M_PI/2; }
	if (phi > M_PI) { phi =  M_PI/2; }
}

// Funcao que posiciona e aponta a camera
void Player::position()
{
	gluLookAt(x, y, z, x + cos(theta), y + sin(phi), z + sin(theta),0,1,0);
}

// Altera a posicao espacial da camera
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