#ifndef OBJCLASSES_H  
#define OBJCLASSES_H "objClasses.h"


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
		float colisionRadius;				// Radius value for colission evaluation
		float colisionHeight;				// Height value for colission evaluation

		Object(float Posx,float Posz);	// Constructor function: set Object X,Z with PosX and PosZ
		Object(float Posx, float Posz, float radius);
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
// Dinamic Object Class. For Player, Ennimies, projectiles etc.
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
		void attack();					       			 // Attack Method (not implemented yet)
		void physics(float dt);							 // Physics Component (Just gravity for now)
														 	// Changes the upSpeedMomentum and the Object::Y component using dt (time) value
		void jump();									 // Set the upSpeedMomentum if the Object is on the ground
		void throwback(float playerx, float playerz);    // Function that throw the Enemy backward and upward
		bool detectColision();							 // Colission Detection Function
		bool detectMovingColision();
	private:

};

/***************************************************************/
/* 			          Player Object Class       			   */
/***************************************************************/
class Player : public DinamicObj
{
public:
	Player(float Posx, float Posz,int hp, int ap, float sp);		// Constructor, start the object
	bool walkbuffer[10];
	bool shiftBuffer;												// Movement Buffer
	bool jumpBuffer;
	float theta;													// Used for horizontal rotation
	float phi; 														// Used for vertical rotation
	int   experience;

	// Methods
	void yaw      (int pixels);		// Function that changes the looking direction rotates horizontally									
	void pitch    (int pixels);		// Function that changes the looking direction rotates vertically
	void LookAt();					// Function that position the player and the direction where is looking at
	void updatePosition();			// Update the position of the character in the space.
	void attack();
};


/***************************************************************/
/* 			          Enemy Object Class       			   */
/***************************************************************/
class Enemy : public DinamicObj
{
private:
	bool wanderflag;  // Flag used to determine if the Enemy is wandering of following the player
	float wanderX;	  // X component of a random wandering final position 	
	float wanderZ;	  // Z component of a random wandering final position
	float lastAttackTime;
public:
	// Constructor of the Enemy. Set position, HP, Attack, Speed
	Enemy(float Posx, float Posz, float radius, int hp, int ap, float sp);

	// Methods
	void wander();								// Wandering function (change the wanderX, wanderZ if not set)
	void attackPlayer();						// AttackPlayer Function (not implemented yet)
	void run(Player &player);		// Run the Enemy object. Make the function calls depending the case.
													// It make wander() call if too far from player and follow player 
													// If close enough.

};
#endif