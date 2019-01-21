// ======================= THE TEAR GAME ===================== //
#include <stdlib.h>
#include "lib.h"
#include "Tear_game.h"
#include "spritesheet.h"
#include "face.h"
#include "sound.h"
#include "TearSound.h"


// Variables
BOTTLE bottle;
TEARS leftTears[TEARSCOUNT/2];
TEARS rightTears[TEARSCOUNT/2];
HEARTS hearts[HEARTSCOUNT];
SCORE score[SCORECOUNT];

int livesRemaining;
int tearsRemaining;
int randEye;
int timeToNextTear;
int myScore;

OBJ_ATTR shadowOAM[128];

SOUND soundA;
SOUND soundB;


// =============================== INITIALIZE GAME ============================
// Initialize the Tear game
void initTearGame2() {

	initBottle2();
	initLeftTears2();
	initRightTears2();
	initHearts2();
	initScore2();

	livesRemaining = HEARTSCOUNT;
	tearsRemaining = TEARSCOUNT;
	timeToNextTear = 50;

	// Initialize Score
	myScore = 0;
	livesRemaining = HEARTSCOUNT;

}

// =============================== DRAW GAME ================================
// Draws the game each frame
void drawTearGame2() {
	drawBottle2();
	drawLeftTears2();
	drawRightTears2();
	drawHearts2();
	drawScore2();
}

// =============================== UPDATE GAME ================================

void updateTearGame2() {

	updateBottle2();  

	int randEye = rand()%(2);
	if(randEye == 0) {
		if (timeToNextTear <= 0) {
			dropLeftTears2();
		} else {
			timeToNextTear--;
		}
	} else {
		if (timeToNextTear <= 0) {
			dropRightTears2();
		} else {
			timeToNextTear--;
		}
	}

	for (int i = 0; i < TEARSCOUNT / 2; i++) {
		updateLeftTears2(&leftTears[i]);
	}
	for (int j = 0; j < TEARSCOUNT / 2; j++) {
		updateRightTears2(&rightTears[j]);
	}

}

// ====================================================================================
// =========================== BOTTLE FUNCTIONS =======================================
// ====================================================================================

// Initialize the bottle
void initBottle2() {
	bottle.row = 132;
    bottle.col = 120;
    bottle.oldCol = bottle.col;
    bottle.rdel = 1;
    bottle.width = 16;
    bottle.height = 16;
    bottle.hide = 0;
}

// Draw the bottle
void drawBottle2() {
	if (bottle.hide) {
        shadowOAM[0].attr0 |= ATTR0_HIDE;
    } else {
    shadowOAM[0].attr0 = bottle.row | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[0].attr1 = bottle.col | ATTR1_SMALL;
    shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 18);
    }
}

// Handles the bottle sliding across the screen
void updateBottle2() {
		// Move the bottle
	if (BUTTON_HELD(BUTTON_LEFT) && bottle.col >= bottle.rdel) {
		bottle.col = bottle.col - (2 * bottle.rdel);
	} else if (BUTTON_HELD(BUTTON_RIGHT) && bottle.col + bottle.width - 1 < SCREENWIDTH - bottle.rdel) {
		bottle.col =bottle.col + (2 * bottle.rdel);
	}
}


// ====================================================================================
// ================================== TEARS FUNCTIONS =================================
// ====================================================================================

//Initialize left eye tears
void initLeftTears2() {
	for (int i = 0; i < (TEARSCOUNT / 2); i++) {
		leftTears[i].row = leftTears[i].height;
		leftTears[i].col = 0;
		leftTears[i].height = 16;
		leftTears[i].width = 16;
		leftTears[i].active = 0;
		leftTears[i].rdel = 1;	
	}
}

//Initialize right eye tears
void initRightTears2() {
	for (int i = 0; i < (TEARSCOUNT / 2); i++) {
		rightTears[i].row = rightTears[i].height;
		rightTears[i].col = 0;
		rightTears[i].height = 16;
		rightTears[i].width = 16;
		rightTears[i].active = 0;
		rightTears[i].rdel = 1;
	}
}

// Draw left eye tears
void drawLeftTears2() {
	for (int i = 0; i < (TEARSCOUNT / 2); i++) {
		if (leftTears[i].hide) {
			shadowOAM[i + 13].attr0 |= ATTR0_HIDE;
		} else if (leftTears[i].active) {
			shadowOAM[i + 13].attr0 = (ROWMASK & leftTears[i].row) | ATTR0_SQUARE | ATTR0_REGULAR | ATTR0_4BPP;
			shadowOAM[i + 13].attr1 = (COLMASK & leftTears[i].col) | ATTR1_SMALL;
			shadowOAM[i + 13].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 20);
		}
	}
}

// Draw right eye tears
void drawRightTears2() {
	for (int i = 0; i < (TEARSCOUNT / 2); i++) {
		if (rightTears[i].hide) {
			shadowOAM[i + 18].attr0 |= ATTR0_HIDE;
		} else if (rightTears[i].active) {
			shadowOAM[i + 18].attr0 = (ROWMASK & rightTears[i].row) | ATTR0_SQUARE | ATTR0_REGULAR | ATTR0_4BPP;
			shadowOAM[i + 18].attr1 = (COLMASK & rightTears[i].col) | ATTR1_SMALL;
			shadowOAM[i + 18].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 20);
		}
	}
}

// This takes care of the left tears falling
void updateLeftTears2(TEARS* t) {
	if (t->active) {
		if (t->row + t->height-1 <= 150) {
			t->row += t->rdel;
			
		} else {
			t->active = 0;
		}
	}

	// Handles catching a tear and updating the score
	if (collision(t->row, t->col, t->height, t->width, bottle.row, bottle.col, bottle.height, bottle.width)  && t->active) {
		t->active = 0;
		t->hide = 1;
		myScore++;
		playSoundB(TearSound, TEARSOUNDLEN, TEARSOUNDFREQ, 0);
		updateScore2();
	// Handles not catching a tear by just hiding it
	} else if (t->row == 150 - t-> height  && t->active) {
		t->active = 0;
		t->hide = 1;
	}
}

// This takes care of the right tears falling
void updateRightTears2(TEARS* t) {
	if (t->active) {
		if (t->row + t->height-1 <= 150) {
			t->row += t->rdel;
			
		} else {
			t->active = 0;
		}
	}
	// Handles catching a tear and updating the score
	if (collision(t->row, t->col, t->height, t->width, bottle.row, bottle.col, bottle.height, bottle.width) && t->active) {
		t->active = 0;
		t->hide = 1;
		myScore++;
		playSoundB(TearSound, TEARSOUNDLEN, TEARSOUNDFREQ, 0);
		updateScore2();
	// Handles not catching a tear by just hiding it
	} else if (t->row == 150 - t-> height  && t->active) {
		t->active = 0;
		t->hide = 1;
	}
}

// Find and positions the next left tear
void dropLeftTears2() {
	int randomNum = rand()%(2);   // random num between 0 or 1
	timeToNextTear = rand()%40 + 90;
	// Find the first inactive tears
	for (int i = 0; i < TEARSCOUNT / 2; i++) {
		if (!leftTears[i].active) {
			leftTears[i].hide = 0;
			// Position the new tear
			leftTears[i].row = 31;
			// This choses randomly which side of the left eye the tear will fall from
			if (randomNum == 0) {
				leftTears[i].col = 44;
			} else if (randomNum == 1){
				leftTears[i].col = 64;
			}
			// Take the tear out of the pool
			leftTears[i].active = 1;

			// Break out of the loop
			break;
		}
	}
}

// Find and positions the next right tear
void dropRightTears2() {
	int randomNum = rand()%(2);   // random num between 0 or 1
	timeToNextTear = rand()%40 + 50;
	// Find the first inactive tears
	for (int i = 0; i < TEARSCOUNT / 2; i++) {
		if (!rightTears[i].active) {
			rightTears[i].hide = 0;
			rightTears[i].row = 31;
			// This choses randomly which side of the right eye the tear will fall from
			if (randomNum == 0) {
				rightTears[i].col = 168;
			} else if (randomNum == 1){
				rightTears[i].col = 184;
			}
			// Take the tear out of the pool
			rightTears[i].active = 1;

			// Break out of the loop
			break;
		}
	}
}

// ===================================================================================
// ================================= HEARTS FUNCTIONS ================================
// ===================================================================================

void initHearts2() {
	int initCol = 40;
	for (int i = 0; i < HEARTSCOUNT; i++) {
		hearts[i].width = 16;
		hearts[i].height = 16;
		hearts[i].row = 145;
		hearts[i].col = initCol;
		initCol += 16;
		hearts[i].active = 1;
	}
}

void drawHearts2() {
    for(int i = 0; i < HEARTSCOUNT; i++) {
		if (hearts[i].active) {
			shadowOAM[i + 23].attr0 = hearts[i].row | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
			shadowOAM[i + 23].attr1 = hearts[i].col | ATTR1_SMALL;
			shadowOAM[i + 23].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 22);
		} else {
			shadowOAM[i + 23].attr2 = ATTR0_HIDE;
		}
	}
}

// ===================================================================================
// ================================= SCORE FUNCTIONS ================================
// ===================================================================================

void initScore2() {
	for(int i = 0; i < SCORECOUNT; i++) {
		score[i].width = 16;
		score[i].height = 16;
		score[i].row = 145;
		score[i].col = 213;
		score[i].active = 0;
	}
}

void drawScore2() {
		if (score[myScore].active) {
			shadowOAM[26].attr0 = score[myScore].row | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
			shadowOAM[26].attr1 = score[myScore].col | ATTR1_SMALL;
			shadowOAM[26].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 16 + (myScore*2));
		} else {
			shadowOAM[26].attr2 = ATTR0_HIDE;
		}
}

// Updates the score
void updateScore2() {
	if (myScore == 0) {
		score[0].active = 1;
	}
	if (myScore == 1) {
		score[1].active = 1;
	}
	if (myScore == 2) {
		score[2].active = 1;
	}
	if (myScore == 3) {
		score[3].active = 1;
	}
	if (myScore == 4) {
		score[4].active = 1;
	}
	if (myScore == 5) {
		score[5].active = 1;
	}
	if (myScore == 6) {
		score[6].active = 1;
	}
	if (myScore == 7) {
		score[7].active = 1;
	}
}