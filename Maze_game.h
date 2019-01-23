// Player struct
typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int rdel;
    int cdel;
    int width;
    int height;
    int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;
    int hide;
} PLAYER;

// Monsters struct
typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int rdel;
    int cdel;
    int width;
    int height;
    int direction;
    int steps;
    int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;
    int hide;
    int stepCount;
} MONSTER;

// Key Struct
typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int rdel;
    int cdel;
	int height;
	int width;
	int direction;
    int steps;
    int stepCount;
	int hide;
    int active;
} KEY;

// Constants
#define MONSTERCOUNT 10
#define KEYCOUNT 1
#define MAPHEIGHT 512
#define MAPWIDTH 512

// Variables
extern int hOff;
extern int vOff;

extern OBJ_ATTR shadowOAM[128];
extern PLAYER player;
extern MONSTER monster[MONSTERCOUNT];
extern KEY key;
extern int lives;
extern int winGame;

// Prototypes
void initialize();
void update();
void draw();

void initMazeGame1();
void updateMazeGame1();
void drawMazeGame1();
void initMazeGame2();
void updateMazeGame2();
void drawMazeGame2();

void initPlayer1();
void drawPlayer1();
void updatePlayer1();
void animatePlayer1();
void initPlayer2();
void drawPlayer2();
void updatePlayer2();
void animatePlayer2();

void initMonsters1();
void drawMonsters1();
void updateMonsters1(MONSTER *);
void animateMonsters1(MONSTER *);
void initMonsters2();
void drawMonsters2();
void updateMonsters2(MONSTER *);
void animateMonsters2(MONSTER *);

void initKey1();
void drawKey1();
void updateKey1();
void initKey2();
void drawKey2();
void updateKey2();
