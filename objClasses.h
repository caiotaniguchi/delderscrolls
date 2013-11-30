#ifndef OBJCLASSES_H  
#define OBJCLASSES_H "objClasses.h"
#endif

#include <iostream>
//#include "camera.h"
//#include "vector.h"

// Classe de Objetos em Geral
class Object
{
	public:
		float x;
		float y;
		float z;
		float directionAngle;
		int colisionRatio;	// Raio para calculo da colisao
		int colisionHeight;	// altura para calcula da colisao

		Object(float Posx,float Posz);
		void draw(); 		// Funcao Para Desenhar o Modelo
		void loadModel();	// Funcao que carrega o modelo
};

// Classe de Objetos Estaticos: Pedras, arvores, etc
class StaticObj : public Object
{
	public:

};

// Classe de Objetos Dinamicos: Jogador, Inimigos
class DinamicObj : public Object
{
	public:
		int healthpoints;
		int attackpoints;
		float speed;
		float directionx;		//posicao x pra onde ele deve ir
		float directionz;		//
		float directiony;		// direcao do pulo

		DinamicObj(float Posx, float Posz, int hp, int ap, float sp);
		void changeDirection(float x, float z);			 // muda a direção pra qual o objeto esta se deslocando
		void move(float x, float z);   					  	   			 // Move o Objeto para a direcao e velocidade do objeto
		void attack();					       			 // ataque 
		void physics(float dt);									 // gravidade, etc
		void jump();

	private:
		void detectColision();
};

// Classe para jogador
class Player : public DinamicObj
{
public:
	Player(float Posx, float Posz, int hp, int ap, float sp);
	bool walkbuffer[10];
	float theta;
	float phi; 
	void yaw      (int pixels);
	void pitch    (int pixels);
	void position ();
	void updatePosition();

};

class Ennemy : public DinamicObj
{
private:
	bool wanderflag;
	float wanderX;
	float wanderZ;
public:
	Ennemy(float Posx, float Posz, int hp, int ap, float sp);

	void wander();
	void attackPlayer();
	void run(float playerx, float playerz);
};
