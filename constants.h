/***************************************************************/
/* 							 CONSTANTS					       */
/***************************************************************/

// Keyboard key constants
#define KEY_ESCAPE 27
#define FRONT 1
#define BACK  2
#define LEFT  3
#define RIGHT 4

#define W_KEY	119
#define S_KEY	115
#define A_KEY	97
#define D_KEY	100

// Glut window constants
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Render Constants
#define MAX_RENDER_DISTANCE 10.0f
#define MIN_RENDER_DISTANCE 1.0f
#define FIELDOFVIEWANGLE 45		// graus

// // Game Constants \\ \\
// Physics
#define GRAVITY -6000
#define AIRFRICTION 2
#define GROUNDLIMIT 0.9
#define	ELASTIC_COEFFICIENT 0.8
#define BALLTIMEOUT 3000       		// millisecs
#define LEVEL_UP_EXPERIENCE 1000
#define BALLHITPOINTS		10

// Gameplay
#define TREEAMOUNT 10
#define ROCKAMOUNT 10
#define TEAPOTS_AMOUNT 2
#define GROUND_AREA 50
#define ATTACK_DISTANCE 5
#define	COOLDOWNTIME_MS 1500
#define ATTACK_ANGLE 20
#define ENEMY_SPEED 0.2
#define LEVEL_FACTOR 2     //amount of new monster per level
#define SPRINT_SPEED 4
#define THROWPOWER 1.5

// General Use Constants
#define HIT 				true
#define NOHIT				false
#define HUD_TEXT			0
#define POP_UP				1
#define TITLE_TEXT 			2
#define PAUSED_TEXT			3
#define TEAPOT_MODEL		0
#define LOADED_MODEL		1