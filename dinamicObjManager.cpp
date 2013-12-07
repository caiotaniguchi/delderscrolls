#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <vector>
#include <cmath>
#include "objClasses.h"
#include "terrain.h"
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include <stdlib.h>
#include "loadObj.h"

using namespace std;

/***************************************************************/
/* 							 Enemies Manager			       */
/***************************************************************/

// loop across an enemy vector and update they positions
void updateEnemies(float dt, vector<Enemy>& enemyList, Player &player)
{
	
	for(int i =0; i < enemyList.size(); i++)
	{
		enemyList[i].physics(dt);		// Updates Physics events
		enemyList[i].run(player);		// Take decsions and draw enemy 
	}

	// Enemy Generator
	if(enemyList.size() < TEAPOTS_AMOUNT + player.level*LEVEL_FACTOR)
		enemyList.push_back(Enemy(rand() % (2*GROUND_AREA) -GROUND_AREA,rand() % (2*GROUND_AREA) -GROUND_AREA,2,50,100,ENEMY_SPEED, 2));
}


// Loop across a vector of enemies and verify if they were attacked. 
//if positive, throwback enemy and remove healthpoints from target
void checkEnemyStatus(vector<Enemy>& enemyList, Player &player)
{

	for(int i =0; i < enemyList.size(); i++)
	{	
					// erase the enemy from the enemylist if healpoints inferior than zero
			if(enemyList[i].healthpoints <= 0)	
				{
					enemyList.erase(enemyList.begin()+i);
					player.experience += 100;

					if(player.experience >= LEVEL_UP_EXPERIENCE)
					{
						player.level++;
						player.experience =0;
					}
				}	
		
	}
}
void checkhit(vector<Enemy>& enemyList, Player &player)
{

	for(int i =0; i < enemyList.size(); i++)
	{	

		// Set a vector pointing to the position where it must go
		float directionx = enemyList[i].x - player.x;
		float directionz = enemyList[i].z - player.z;

		// compute the distance to the final position
		float module = sqrt(directionx*directionx + directionz*directionz);

		if(module < ATTACK_DISTANCE)
		{
			// Evaluate the inner product between the vector Enemy-Player and Player Eyes Direction
			// If the ARCOS of this product is bigger than a specific angle the attack wont happen
			float playerDirectionx = cos(player.theta);
			float playerDirectionz = sin(player.theta);
			
			float auxVectorx = enemyList[i].x - player.x;
			float auxVectorz = enemyList[i].z - player.z;

			float modulePlayerDirection = sqrt(playerDirectionz*playerDirectionz+ playerDirectionx*playerDirectionx);
			float moduleAuxVector = sqrt(auxVectorx*auxVectorx+ auxVectorz*auxVectorz);
			
			// inner product
			float angle = 360/(2*M_PI)*acos((playerDirectionx*auxVectorx + playerDirectionz*auxVectorz)/(moduleAuxVector*modulePlayerDirection));
			
			// Check Angle
			// If the direction of the player to the enemy is inferior than
			if( angle < ATTACK_ANGLE )
			{
				enemyList[i].throwback(player.x,player.z);
				enemyList[i].healthpoints -= player.attackpoints;

			}


		}	
					// erase the enemy from the enemylist if healpoints inferior than zero
			if(enemyList[i].healthpoints <= 0)	
				{
					enemyList.erase(enemyList.begin()+i);
					player.experience += 100;

					if(player.experience >= LEVEL_UP_EXPERIENCE)
					{
						player.level++;
						player.experience =0;
					}
				}	
	}
}


/***************************************************************/
/* 						BALL MANAGER					       */
/***************************************************************/
void throwball(Player player)
{
	extern std::vector<DinamicObj> ballList;
	//DinamicObj(float Posx, float Posz, int hp, int ap, float sp, float upSpeedMomentum, float throwbackx, float throwbacky);
	float module = sqrt(player.x*player.x +player.z + player.z);

	ballList.push_back(DinamicObj(player.x, player.z, player.y +3+ 4*sin(player.phi), 100, 100*cos(player.theta), 100*sin(player.theta), glutGet(GLUT_ELAPSED_TIME)));
}

void updateBalls( float dt)
{
	extern std::vector<DinamicObj> ballList;
	float lastUpMomentum;
	float lastthrowbackx;
	float lastthrowbackz;



	for(int i =0; i < ballList.size(); i++)
	{	
		if(glutGet(GLUT_ELAPSED_TIME) - ballList[i].creationTime > BALLTIMEOUT)	
		{	
		ballList.erase(ballList.begin()+i);
		}

		lastUpMomentum = ballList[i].upSpeedMomentum;
		lastthrowbackx = ballList[i].throwbackx;
		lastthrowbackz = ballList[i].throwbackz;

		if(ballList[i].detectMovingColision(HIT))
		{
			ballList.erase(ballList.begin()+i);
		}

		if(ballList[i].detectColision())
		{
			ballList[i].throwbackx = -ballList[i].throwbackx*ELASTIC_COEFFICIENT ;
			ballList[i].throwbackz = -ballList[i].throwbackz*ELASTIC_COEFFICIENT;

		}

		ballList[i].physics(dt);
		
		if (ballList[i].y < GROUNDLIMIT)
			{
				ballList[i].upSpeedMomentum = -lastUpMomentum*ELASTIC_COEFFICIENT;
				ballList[i].throwbackx = lastthrowbackx*ELASTIC_COEFFICIENT;
				ballList[i].throwbackz = lastthrowbackz*ELASTIC_COEFFICIENT;
			}
		ballList[i].draw2();
	}
	//enemyList[i].run(player)
}