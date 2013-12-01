#ifndef ENEMIESMANAGER_H  
#define ENEMIESMANAGER_H "enemiesManager.h"
#endif

#include <vector>
#include <cmath>
#include "objClasses.h"

using namespace std;

// loop across an enemy vector and update they positions
void updateEnemies(float dt, vector<Ennemy>& enemmyList,float playerx, float playerz)
{
	for(int i =0; i < enemmyList.size(); i++)
	{
		enemmyList[i].physics(dt);
		enemmyList[i].run(playerx,playerz);
	}
}

// Loop across a vector of enemies and verify if they were attacked. if positive, throwback enemy and remove healthpoints
// From target
void checkhit(vector<Ennemy>& enemmyList,float playerx, float playerz, float playerattackpoints,float theta)
{
	for(int i =0; i < enemmyList.size(); i++)
	{	
		// Set a vector pointing to the position where it must go
		float directionx = enemmyList[i].x - playerx;
		float directionz = enemmyList[i].z - playerz;

		// compute the distance to the final position
		float module = sqrt(directionx*directionx + directionz*directionz);

		if(module < 5)
		{
			// Evaluate the inner product between the vector Enemy-Player and Player Eyes Direction
			// If the ARCOS of this product is bigger than a especific angle the atack wont happen
			float playerDirectionx = cos(theta);
			float playerDirectionz = sin(theta);
			
			float auxVectorx = enemmyList[i].x - playerx;
			float auxVectorz = enemmyList[i].z - playerz;

			float modulePlayerDirection = sqrt(playerDirectionz*playerDirectionz+ playerDirectionx*playerDirectionx);
			float moduleAuxVector = sqrt(auxVectorx*auxVectorx+ auxVectorz*auxVectorz);
			
			// inner product
			float angle = 360/(2*M_PI)*acos((playerDirectionx*auxVectorx + playerDirectionz*auxVectorz)/(moduleAuxVector*modulePlayerDirection));

			//std::cout << angle;
			
			// Check Angle
			if( angle < 20 )
			{
				enemmyList[i].throwback(playerx,playerz);
				enemmyList[i].healthpoints -= playerattackpoints;
			}

			// erase the enemmy from the enemmylist if healpoints inferior than zero
			if(enemmyList[i].healthpoints <= 0)	enemmyList.erase(enemmyList.begin()+i);
	
		}		
	}
}