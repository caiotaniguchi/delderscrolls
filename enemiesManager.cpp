#include <vector>
#include <cmath>
#include "objClasses.h"
#include "terrain.h"
#include <stdio.h>
#include <string.h>

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

}


// Loop across a vector of enemies and verify if they were attacked. if positive, throwback enemy and remove healthpoints
// From target
void checkhit(vector<Enemy>& enemyList,float playerx, float playerz, float playerattackpoints,float theta)
{

	for(int i =0; i < enemyList.size(); i++)
	{	

		// Set a vector pointing to the position where it must go
		float directionx = enemyList[i].x - playerx;
		float directionz = enemyList[i].z - playerz;

		// compute the distance to the final position
		float module = sqrt(directionx*directionx + directionz*directionz);

		if(module < 5)
		{
			// Evaluate the inner product between the vector Enemy-Player and Player Eyes Direction
			// If the ARCOS of this product is bigger than a specific angle the attack wont happen
			float playerDirectionx = cos(theta);
			float playerDirectionz = sin(theta);
			
			float auxVectorx = enemyList[i].x - playerx;
			float auxVectorz = enemyList[i].z - playerz;

			float modulePlayerDirection = sqrt(playerDirectionz*playerDirectionz+ playerDirectionx*playerDirectionx);
			float moduleAuxVector = sqrt(auxVectorx*auxVectorx+ auxVectorz*auxVectorz);
			
			// inner product
			float angle = 360/(2*M_PI)*acos((playerDirectionx*auxVectorx + playerDirectionz*auxVectorz)/(moduleAuxVector*modulePlayerDirection));

			//std::cout << angle;
			
			// Check Angle
			if( angle < 20 )
			{
				enemyList[i].throwback(playerx,playerz);
				enemyList[i].healthpoints -= playerattackpoints;

			}

			// erase the enemy from the enemylist if healpoints inferior than zero
			if(enemyList[i].healthpoints <= 0)	enemyList.erase(enemyList.begin()+i);
	
		}		
	}
}