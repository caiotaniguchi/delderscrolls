#ifndef ENEMIESMANAGER_H  
#define ENEMIESMANAGER_H "enemiesManager.h"
#endif

#include <vector>
//#include "objClasses.h"

using namespace std;

// Loop across a vector of Enemies and update they posisitons and physics effects
void updateEnemies(float dt, vector<Enemy> &enemyList,float playerx, float playerz);

// Loop across a vector of Enemies and verify if they were atacked. if positive, throwback enemy and remove healthpoints
// From target
void checkhit(vector<Enemy>& enemmyList,float playerx, float playerz, float playerattackpoints, float theta);
