#ifndef OBJCLASSES_H  
#define OBJCLASSES_H "objClasses.h"
#endif

#include <iostream>

/***************************************************************/
/* 			 			General Object Class       			   */
/***************************************************************/
// General Propurse Object
class Object
{
	public:
		float x;						// Object X Position 
		float y;						// Object Y Position
		float z;						// Object Z Position
		float directionAngle;			// Object Rotation Angle
		int colisionRadius;				// Radius value for colission evaluation
		int colisionHeight;				// Height value for colission evaluation

		Object(float Posx,float Posz);	// Constructor function: set Object X,Z with PosX and PosZ
		void draw(); 					// Drawing function on the x,y,z position and with directionAngle rotation
		void loadModel();				// LoadModel function (not implemented yet)
};

/***************************************************************/
/* 			          Static Object Class       			   */
/***************************************************************/
// Static ObjectClass. For trees, rocks etc
class StaticObj : public Object
{
	public:
};

/***************************************************************/
/* 					Dinamic Object Class         			   */
/***************************************************************/
// Dinamic Object Class. For Player, Enemies, projectiles etc.
class DinamicObj : public Object
{
	public:
		int healthpoints;			// Object Healthpoints
		int attackpoints;			// Object Attack Power
		float speed;				// Object Movement Speed
		float upSpeedMomentum;		// Upward speed (for jumping)

		float throwbackx;
		float throwbackz;

		// Dinamic Object Constructor: Position x, Position Z, Healtpoints, AtackPower, Speed
		DinamicObj(float Posx, float Posz, int hp, int ap, float sp);

		// Methods
		void changeDirection(float x, float z);			 // Change the direction where the object is looking at
		void move(float x, float z);   					 // Move the Object to a specific place using its speed, x, z position as parameters
														 	// It also rotate to the direction using the speed as a parameter
		void attack();					       			 // NAO IMPLEMENTADO
		void physics(float dt);							 // Physics Component (Just gravity for now)
														 	// Changes the upSpeedMomentum and the Object::Y component using dt (time) value
		void jump();									 // Set the upSpeedMomentum if the Object is on the ground
		void throwback(float playerx, float playerz);    // Function that throw the enemy backward and upward

	private:
		void detectColision();							 // NAO IMPLEMENTADO
};

/***************************************************************/
/* 			          Player Object Class       			   */
/***************************************************************/
class Player : public DinamicObj
{
public:
	Player(float Posx, float Posz, int hp, int ap, float sp);		// Constructor, start the object
	bool walkbuffer[10];											// Movement Buffer
	float theta;													// Used for horizontal rotation
	float phi; 														// Used for vertical rotation
	
	// Methods
	void yaw      (int pixels);		// Function that changes the looking direction rotates horizontally									
	void pitch    (int pixels);		// Function that changes the looking direction rotates vertically
	void LookAt();					// Function that position the player and the direction where is looking at
	void updatePosition();			// Update the position of the character in the space.
	void attack();					// NAO IMPLEMENTADO E VAI DAR MERDA COM O ATTACK DO DYNAMICOBJ
};


/***************************************************************/
/* 			          Enemy Object Class       			   */
/***************************************************************/
class Enemy : public DinamicObj
{
private:
	bool wanderflag;  // Flag used to determine if the enemy is wandering of following the player
	float wanderX;	  // X component of a random wandering final position 	
	float wanderZ;	  // Z component of a random wandering final position
public:
	// Constructor of the enemy. Set position, HP, Attack, Speed
	Enemy(float Posx, float Posz, int hp, int ap, float sp);

	// Methods
	void wander();								// Wandering function (change the wanderX, wanderZ if not set)
	void attackPlayer();						// NAO IMPLEMENTADO E POR QUE ISSO EXISTE??????
	void run(float playerx, float playerz);		// Run the enemy object. Make the function calls depending the case.
													// It make wander() call if too far from player and follow player 
													// If close enough.

};
