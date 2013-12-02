
/***************************************************************/
/* 							 UTIL.H						       */
/***************************************************************/

void writeText(char * string, float x, float y);


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