
// ======================= THE LOVE MAZE ===================== //
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "Maze_game.h"
#include "spritesheet.h"
#include "collisionmap.h"
#include "sound.h"
#include "KeySound.h"

// Variables
PLAYER player;
MONSTER monsters[MONSTERCOUNT];
KEY key;
int hOff;
int vOff;
OBJ_ATTR shadowOAM[128];

int lives;
int winGame;

SOUND soundA;
SOUND soundB;

// States used for player.aniState
enum { PLAYERFRONT, PLAYERBACK, PLAYERRIGHT, PLAYERLEFT, PLAYERIDLE};
// States used for monsters[i].aniState
enum { MONSTERFRONT, MONSTERBACK, MONSTERRIGHT, MONSTERLEFT, MONSTERIDLE};


// =============================== INITIALIZE GAME ============================
// Initialize the game
void initMazeGame1() {
    hOff = 0;
	vOff = 512 - SCREENHEIGHT;

	lives = 1;
	winGame = 0;

	initPlayer1();
	initMonsters1();
	initKey1();

}

// =============================== DRAW GAME ================================
// Draws the game each frame
void drawMazeGame1() {
	drawPlayer1();
	drawMonsters1();
	drawKey1();

	REG_BG0HOFF = hOff;
    REG_BG0VOFF = vOff;
}

// =============================== UPDATE GAME ================================
// Updates the game each frame
void updateMazeGame1() {
	updatePlayer1();  

	for (int i = 0; i < MONSTERCOUNT; i++) {
		updateMonsters1(&monsters[i]);
	}
	updateKey1();
}


// =========================== PLAYER FUNCTIONS ==========================
// Initialize the player
void initPlayer1() {
    player.width = 16;
    player.height = 16;
    player.rdel = 1;
    player.cdel = 1;
    player.worldRow = 450;
    player.worldCol = 36;

    player.aniCounter = 0;
    player.curFrame = 0;
    player.numFrames = 3;
    player.aniState = PLAYERFRONT;
    player.hide = 0;
    
}

// Draw the player
void drawPlayer1() {
	if (player.hide) {
        shadowOAM[0].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[0].attr0 = (ROWMASK & player.screenRow) | ATTR0_SQUARE | ATTR0_REGULAR | ATTR0_4BPP;
        shadowOAM[0].attr1 = (COLMASK & player.screenCol) | ATTR1_SMALL;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(player.curFrame * 2, player.aniState * 2);
    }
}

// Handles the player walking & bumping into the exit door
void updatePlayer1() {
	// Update to include complex camera movement & to include collision map
    if(BUTTON_HELD(BUTTON_UP)) {
    	// Make sure player doesn't go off the map here, check collision map
        if ((player.worldRow > 0)
        	&& (collisionmapBitmap[OFFSET(player.worldRow, player.worldCol, MAPWIDTH)])
        		&& (collisionmapBitmap[OFFSET(player.worldRow - 1, player.worldCol + player.width - 1, MAPWIDTH)])) {

        	player.worldRow -= player.cdel;

			// Makes sure the background offset doesn't show past the edge, and only update the offset variables if player is in the right spot*/
            if (vOff > 0 && ((player.screenRow + player.height / 2) < SCREENHEIGHT / 2)) {
				vOff--;
            }
        }
    }
    if(BUTTON_HELD(BUTTON_DOWN)) {
        if (((player.worldRow + player.width) < 512)
        	&& (collisionmapBitmap[OFFSET(player.worldRow + player.height, player.worldCol, MAPWIDTH)])
        		&& (collisionmapBitmap[OFFSET(player.worldRow + player.height - 1, player.worldCol + player.width - 1, MAPWIDTH)])) {

			player.worldRow += player.cdel;

            if (vOff < 512 - SCREENHEIGHT && ((player.screenRow + player.height / 2) < SCREENHEIGHT / 2)) {
                vOff++;
            }
        }
    }
    if(BUTTON_HELD(BUTTON_LEFT)) {
        if ((player.worldCol > 0)
        	&& (collisionmapBitmap[OFFSET(player.worldRow, player.worldCol, MAPWIDTH)])
        		&& (collisionmapBitmap[OFFSET(player.worldRow + player.height - 1, player.worldCol - 1, MAPWIDTH)])) {

   			player.worldCol -= player.rdel;
			
            if (hOff > 0 && ((player.screenCol + player.width / 2) < SCREENWIDTH / 2)) {
                hOff--;
            }
        }
    }

    if(BUTTON_HELD(BUTTON_RIGHT)) {
        if (((player.worldCol + player.height) < 513)
        	&& (collisionmapBitmap[OFFSET(player.worldRow, player.worldCol + player.width, MAPWIDTH)])
        		&& (collisionmapBitmap[OFFSET(player.worldRow + player.height - 1, player.worldCol + player.width - 1, MAPWIDTH)])) {

   			player.worldCol += player.rdel;

            if (hOff < 512 - SCREENWIDTH && ((player.screenCol + player.width / 2) < SCREENWIDTH / 2)) {
                hOff++;
            }
        }
    }

    // Update screen row and screen col
    player.screenRow = player.worldRow - vOff;
    player.screenCol = player.worldCol - hOff;

    animatePlayer1();

    // Win condition
    if (player.worldRow == 16  && key.hide) {
    	winGame = 1;
    }
}

// Handle player animation states
void animatePlayer1() {

    // Set previous state to current state
    player.prevAniState = player.aniState;
    player.aniState = PLAYERIDLE;

    // Change the animation frame every 20 frames of gameplay
    if(player.aniCounter % 10 == 0) {
        player.curFrame = (player.curFrame + 1) % player.numFrames;
    }
    // Control movement and change animation state
    if(BUTTON_HELD(BUTTON_UP))
        player.aniState = PLAYERBACK;
    if(BUTTON_HELD(BUTTON_DOWN))
        player.aniState = PLAYERFRONT;
    if(BUTTON_HELD(BUTTON_LEFT))
        player.aniState = PLAYERLEFT;
    if(BUTTON_HELD(BUTTON_RIGHT))
        player.aniState = PLAYERRIGHT;

    // If the player aniState is idle, frame is player standing
    if (player.aniState == PLAYERIDLE) {
        player.curFrame = 0;
        player.aniCounter = 0;
        player.aniState = player.prevAniState;
    } else {
        player.aniCounter++;
    }
}


// ================================== MONSTERS FUNCTIONS =================================

//Initialize monsters
void initMonsters1() {
	for (int i = 0; i < MONSTERCOUNT; i++) {
		monsters[i].width = 16;
		monsters[i].height = 16;
		monsters[i].rdel = 1;
		monsters[i].cdel = 1;
		monsters[i].aniCounter = 0;
		monsters[i].curFrame = 0;
		monsters[i].numFrames = 3;
		monsters[i].aniState = MONSTERFRONT;
		monsters[i].hide = 0;
		monsters[i].stepCount = 0;
	}

    // The start position of the monsters
	monsters[0].worldRow = 272;
	monsters[0].worldCol = 24; 
	monsters[1].worldRow = 264;
	monsters[1].worldCol = 136;
	monsters[2].worldRow = 48;
	monsters[2].worldCol = 136;
	monsters[3].worldRow = 120;
	monsters[3].worldCol = 216;
	monsters[4].worldRow = 312;
	monsters[4].worldCol = 280;
	monsters[5].worldRow = 376;
	monsters[5].worldCol = 280;
	monsters[6].worldRow = 424;
	monsters[6].worldCol = 136;
	monsters[7].worldRow = 392;
	monsters[7].worldCol = 456;
	monsters[8].worldRow = 200;
	monsters[8].worldCol = 328;
	monsters[9].worldRow = 40;
	monsters[9].worldCol = 440;

	// How nany steps each monster will take
	monsters[0].steps = 56;
	monsters[1].steps = 40;
	monsters[2].steps = 80;
	monsters[3].steps = 56;
	monsters[4].steps = 96;
	monsters[5].steps = 88;
	monsters[6].steps = 56;
	monsters[7].steps = 41;
	monsters[8].steps = 60;
	monsters[9].steps = 40;

    // Initializes the direction the monster will first take. (1 means up, 2 means right, 3 means down, 4 means up)
	monsters[0].direction = 2;
	monsters[1].direction = 2;
	monsters[2].direction = 3;
	monsters[3].direction = 2;
	monsters[4].direction = 2;
	monsters[5].direction = 2;
	monsters[6].direction = 3;
	monsters[7].direction = 3;
	monsters[8].direction = 2;
	monsters[9].direction = 2;
}

// This takes care of the monsters walking
void drawMonsters1() {
	for (int i = 0; i < MONSTERCOUNT; i++) {
		if (monsters[i].hide || monsters[i].screenRow >= 160 || monsters[i].screenCol >= 240 || monsters[i].screenCol <= 0 || monsters[i].screenRow <= 0) {
			shadowOAM[i + 1].attr0 |= ATTR0_HIDE;
		} else {
			shadowOAM[i + 1].attr0 = (ROWMASK & monsters[i].screenRow) | ATTR0_SQUARE | ATTR0_REGULAR | ATTR0_4BPP;
			shadowOAM[i + 1].attr1 = (COLMASK & monsters[i].screenCol) | ATTR1_SMALL;
			shadowOAM[i + 1].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(monsters[i].curFrame * 2, 8 + monsters[i].aniState * 2);
		}
	}
}

// Updates monsters position and handles collision of a player and a monster
void updateMonsters1(MONSTER* m) {
	// Moves up
	if(m->direction == 1) {
		if (m->stepCount == m->steps) {
			m->direction = 3; // Switch direction to down
			m->stepCount = 0;
		} else {
			m->worldRow -= m->cdel;
			m->stepCount++;
		}
	}
    // Moves down
	if(m->direction == 3) {
		if (m->stepCount == m->steps) {
			m->direction = 1; // Switch direction to up
			m->stepCount = 0;
		} else {
			m->worldRow += m->cdel;
			m->stepCount++;
		}
	}
	// Moves left
	if(m->direction == 4) {
		if (m->stepCount == m->steps) {
			m->direction = 2; // Switch direction to right
			m->stepCount = 0;
		} else {
			m->worldCol -= m->rdel;
			m->stepCount++;
		}
	}
	// Moves right
	if(m->direction == 2) {
		if (m->stepCount == m->steps) {
			m->direction = 4; // Switch direction to left
			m->stepCount = 0;
		} else {
			m->worldCol += m->rdel;
			m->stepCount++;
		}
	}

	// Update screen row and screen col
    m->screenRow = m->worldRow - vOff;
    m->screenCol = m->worldCol - hOff;

	animateMonsters1(m);

	//Handles collision of a player and a monster by restarting the game
	if(collision(m->worldRow, m->worldCol, m->height, m->width, player.worldRow, player.worldCol, player.height, player.width)) {
		lives--;
	}
}

//Handle player animation states
void animateMonsters1(MONSTER* m) {
    // Set previous state to current state
	m->prevAniState = m->aniState;
	m->aniState = MONSTERIDLE;

    // Change the animation frame
	if(m->aniCounter % 10 == 0) {
		m->curFrame = (m->curFrame + 1) % m->numFrames;
	}
    // Control movement and change animation state
	if(m->direction == 1)
		m->aniState = MONSTERBACK;
	if(m->direction == 2)
		m->aniState = MONSTERRIGHT;
	if(m->direction == 3)
		m->aniState = MONSTERFRONT;
	if(m->direction == 4)
		m->aniState = MONSTERLEFT;

	// Keep increasing aniCounter since the monsters will never stop moving
	m->aniCounter++;
}

//===================================== KEY FUNCTIONS ====================================

// Initializes the key
void initKey1() {
    key.width = 16;
    key.height = 16;
    key.rdel = 1;
    key.cdel = 1;
    key.worldRow = 180;
    key.worldCol = 217;
    key.direction = 2; // Initial movement to the right
    key.steps = 64;
    key.stepCount = 0;
    key.hide = 0;
    key.active = 1;
}

// Draws the key
void drawKey1() {
    if (key.hide || key.screenRow >= 160 || key.screenCol >= 240 || key.screenRow < 0 || key.screenCol < 0 ) {
        shadowOAM[11].attr0 |= ATTR0_HIDE;
    } else if (key.active) {
        shadowOAM[11].attr0 = (ROWMASK & key.screenRow) | ATTR0_SQUARE | ATTR0_REGULAR | ATTR0_4BPP;
        shadowOAM[11].attr1 = (COLMASK & key.screenCol) |ATTR1_SMALL;
        shadowOAM[11].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 16);
    }
}

// This takes care of movement and coliision of the key with the player
void updateKey1() { 
	// Moves up
	if(key.direction == 1 && key.active) {
		if(key.stepCount == key.steps) {
			key.direction = 2; // Switch direction to right
			key.stepCount = 0;
		} else {
			key.worldRow -= key.cdel;
			key.stepCount++;
		}
	}

    // Moves down
	if(key.direction == 3 && key.active) {
		if(key.stepCount == key.steps) {
			key.direction = 4; // Switch direction to left
			key.stepCount = 0;
		} else {
			key.worldRow += key.cdel;
			key.stepCount++;
		}
	}
    // Moves left
	if(key.direction == 4 && key.active) {
		if(key.stepCount == key.steps) {
			key.direction = 1; // Switch direction to up
			key.stepCount = 0;
		} else {
			key.worldCol -= key.rdel;
			key.stepCount++;
		}
	}
    // Moves right
	if(key.direction == 2 && key.active) {
		if(key.stepCount == key.steps) {
			key.direction = 3; // Switch direction to down
			key.stepCount = 0;
		} else {
			key.worldCol += key.rdel;
			key.stepCount++;
		}
	}
	// Update screen row and screen col
	key.screenRow = key.worldRow - vOff;
	key.screenCol = key.worldCol - hOff;

	// Handles collison of player and key by hiding the key and making a sound
	if(collision(key.worldRow, key.worldCol, key.height, key.width, player.worldRow, player.worldCol, player.height, player.width)  && key.active) {
		key.active = 0;
        key.hide = 1;
        playSoundB(KeySound, KEYSOUNDLEN, KEYSOUNDFREQ, 0);
	}
}