// Bottle struct
typedef struct {
    int row;
    int col;
    int oldCol;
    int rdel;
    int width;
    int height;
    int hide;
} BOTTLE;

// Tears struct
typedef struct {
    int row;
    int col;
    int rdel;
    int width;
    int height;
    int hide;
    int active;
} TEARS;

// Hearts Struct
typedef struct {
    int row;
    int col;
	int height;
	int width;
    int active;
} HEARTS;

// Score Struct
typedef struct {
    int row;
    int col;
    int height;
    int width;
    int active;
} SCORE;

// Constants
#define TEARSCOUNT 10
#define HEARTSCOUNT 3
#define SCORECOUNT 8

// Variables
extern OBJ_ATTR shadowOAM[128];

extern BOTTLE bottle;
extern TEARS leftTears[TEARSCOUNT / 2];
extern TEARS rightTears[TEARSCOUNT / 2];
extern HEARTS hearts[HEARTSCOUNT];
extern SCORE score[SCORECOUNT];

extern int livesRemaining;
extern int tearsCollected;
extern int tearsRemaining;
extern int timeToNextLeftTear;
extern int timeToNextRightTear;
extern int myScore;

// Prototypes
void initialize();
void update();
void draw();

void initTearGame1();
void initTearGame2();
void updateTearGame1();
void updateTearGame2();
void drawTearGame1();
void drawTearGame2();

void initBottle1();
void drawBottle1();
void updateBottle1();
void initBottle2();
void drawBottle2();
void updateBottle2();

void initLeftTears1();
void drawLeftTears1();
void updateLeftTears1(TEARS *);
void dropLeftTears1();
void initLeftTears2();
void drawLeftTears2();
void updateLeftTears2(TEARS *);
void dropLeftTears2();

void initRightTears1();
void drawRightTears1();
void updateRightTears1(TEARS *);
void dropRightTears1();
void initRightTears2();
void drawRightTears2();
void updateRightTears2(TEARS *);
void dropRightTears2();

void initHearts1();
void drawHearts1();
void initHearts2();
void drawHearts2();

void initScore1();
void drawScore1();
void updateScore1();
void initScore2();
void drawScore2();
void updateScore2();