#ifndef DINAMICOBJMANAGER_H  
#define DINAMICOBJMANAGER_H "dinamicObjManager.h"

#include <vector>
using namespace std;

/***************************************************************/
/* 						ENEMY MANAGER					       */
/***************************************************************/

// Loop across a vector of ennemies and update they posisitons and physics effects
void updateEnemies(float dt, vector<Enemy> &enemyList, Player &player);
void checkEnemyStatus(vector<Enemy>& enemyList, Player &player);

// Loop across a vector of ennemies and verify if they were atacked. if positive, throwback enemy and remove healthpoints
// From target
void checkhit(vector<Enemy>& enemyList, Player &player);

/***************************************************************/
/* 						BALL MANAGER 					       */
/***************************************************************/

void throwball(Player player);
void updateBalls(float dt);

#endif