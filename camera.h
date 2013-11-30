#ifndef CMAERA_H
#define CAMERA_H "camera.h"
#endif

/* Description */
// Classe para posicionamento da camera principal. 
// Guarda as informacoes de posicao especial e de direcao para onde esta olhando
// seus metodos servem para achar as novas coordenadas e para setar a camera nesses valores
// tambem possui uma funcao que verifica se nescessita deslocar espacialmente
class Camera
{	
public:
	float theta;
	float phi; 

	float x; 
	float y; 
	float z; 
	bool walkbuffer[10];

	Camera();
	void yaw      (int pixels);
	void pitch    (int pixels);
	void position ();
	void updatePosition();
	
};
