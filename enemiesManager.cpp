#include <vector>
#include <cmath>
#include "objClasses.h"
#include "terrain.h"
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include <stdlib.h>

using namespace std;

// loop across an enemy vector and update they positions
void updateEnemies(float dt, vector<Enemy>& enemyList,float playerx, float playerz)
{
	char lifeBar[300];
	// Debugg Strings

	//std::cout << "TEAPOTS HEALTH";
	
	for(int i =0; i < enemyList.size(); i++)
	{
		// Debugg Strings
		//std::cout << " | " ;
		//std::cout << enemyList[i].healthpoints;
		
		enemyList[i].physics(dt);
		enemyList[i].run(playerx,playerz);
	}
	//std::cout << "\n";

	if(enemyList.size() < TEAPOTS_AMOUNT)
	{
		enemyList.push_back(Enemy(rand() % 100 -50,rand() % 100 -50,50,100,0.07));
	}

}


// Loop across a vector of enemies and verify if they were attacked. if positive, throwback enemy and remove healthpoints
// From target
void checkhit(vector<Enemy>& enemyList, Player &player)
{

	for(int i =0; i < enemyList.size(); i++)
	{	

		// Set a vector pointing to the position where it must go
		float directionx = enemyList[i].x - player.x;
		float directionz = enemyList[i].z - player.z;

		// compute the distance to the final position
		float module = sqrt(directionx*directionx + directionz*directionz);

		if(module < 5)
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

			//std::cout << angle;
			
			// Check Angle
			if( angle < 20 )
			{
				enemyList[i].throwback(player.x,player.z);
				enemyList[i].healthpoints -= player.attackpoints;

			}

			// erase the enemy from the enemylist if healpoints inferior than zero
			if(enemyList[i].healthpoints <= 0)	
				{
					enemyList.erase(enemyList.begin()+i);
					player.experience += 100;
				}
		}		
	}
}