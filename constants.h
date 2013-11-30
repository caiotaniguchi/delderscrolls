// CONSTANTES 

#define KEY_ESCAPE 27
#define FRONT 1
#define BACK  2
#define LEFT  3
#define RIGHT 4

#define W_KEY	119
#define S_KEY	115
#define A_KEY	97
#define D_KEY	100

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Structs 
// Struct da janela
typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

// struct da posicao do mouse
typedef struct {
	float x;
	float y;
	int w;
	int h;
} mousePos;