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
			glTranslatef(x,4,z);
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

void DinamicObj::physics()
{
	//gravidade
	if(y > 4)
	{
		y -= 1; 
	}
	else y = 4;
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
		wander(); 				// movimenteo aleatorio
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
