// Copyright © 2019 SandraAlsayar

// ================================= FULL GAME ==================================
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "Maze_game.h"
#include "Tear_game.h"
#include "sound.h"

// Screens
#include "menu.h"
#include "pause.h"
#include "Instr1.h"
#include "Instr2.h"
#include "Instr3.h"
#include "Instr4.h"
#include "SceneA1.h"
#include "SceneA2.h"
#include "SceneA3.h"
#include "SceneA4.h"
#include "SceneA5.h"
#include "SceneA6.h"
#include "SceneA7.h"
#include "SceneA8.h"
#include "SceneA9.h"
#include "TearGameInstr.h"
#include "face.h"
#include "OpenEye1.h"
#include "OpenEye2.h"
#include "OpenEye3.h"
#include "OpenEye4.h"
#include "TearLose1.h"
#include "TearLose2.h"
#include "TearWin.h"
#include "MazeGameInstr.h"
#include "maze.h"
#include "water.h"
#include "MazeLose1.h"
#include "MazeLose2.h"

#include "blank.h"
#include "Final1.h"
#include "Final2.h"
#include "Final3.h"
#include "credits.h"
#include "creditsroll.h"

// Spritesheet
#include "spritesheet.h"

// Sound
#include "INeedU.h"
#include "Sea.h"
#include "HouseOfCards.h"
#include "Run.h"
#include "DoorSound.h"
#include "KeySound.h"
#include "TearSound.h"


// ================================= PROTOTYPES ==================================
void initialize();

// State Prototypes
void goToMenu();
void menu();

void goToInstruct1();
void instruct1();
void goToInstruct2();
void instruct2();
void goToInstruct3();
void instruct3();
void goToInstruct4();
void instruct4();

void goToSceneA1();
void sceneA1();
void goToSceneA2();
void sceneA2();
void goToSceneA3();
void sceneA3();
void goToSceneA4();
void sceneA4();
void goToSceneA5();
void sceneA5();
void goToSceneA6();
void sceneA6();
void goToSceneA7();
void sceneA7();
void goToSceneA8();
void sceneA8();
void goToSceneA9();
void sceneA9();

void goToTearInstruct();
void tearInstruct();
void goToTearGame1();
void tearGame1();
void goToTearGame2();
void tearGame2();
void goToTearWin();
void tearWin();
void goToTearLose1();
void tearLose1();
void goToTearLose2();
void tearLose2();
void goToPauseTear1();
void pauseTear1();
void goToPauseTear2();
void pauseTear2();

void goToMazeInstruct();
void mazeInstruct();
void goToMazeGame1();
void mazeGame1();
void goToMazeGame2();
void mazeGame2();
void goToMazeLose1();
void mazeLose1();
void goToMazeLose2();
void mazeLose2();
void goToPauseMaze1();
void pauseMaze1();
void goToPauseMaze2();
void pauseMaze2();
void goToMazeWin();
void mazeWin();

void goToFinal1();
void final1();
void goToFinal2();
void final2();
void goToFinal3();
void final3();
void goToCredits();
void credits();

// States
enum {MENU, INS1, INS2, INS3, INS4, SA1, SA2, SA3, SA4, SA5, SA6, SA7, SA8, SA9, INSTEAR, TEARGAME1, TEARGAME2, PAUSETEAR1, PAUSETEAR2, PAUSEMAZE1, PAUSEMAZE2, TEARWIN, TEARLOSE1, TEARLOSE2, INSMAZE, MAZEGAME1, MAZEGAME2, MAZELOSE1, MAZELOSE2, MAZEWIN, FINAL1, FINAL2, FINAL3, CREDITS};
int state;

// ================================= VARIABLES ==================================
// Button Variables
unsigned short buttons;
unsigned short oldButtons;
unsigned int vOffWater;
unsigned int vOffCredit;

// Seed variable for randomization of tears
int seed;
int fadeCounter;
// Sound Variables
SOUND soundA;
SOUND soundB;

// ================================= MAIN ==================================
int main() {
    setupInterrupts();
    setupSounds();
    playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
    initialize();

    while(1) {

        // Update button variables
        oldButtons = buttons;
        buttons = BUTTONS;
                
        // State Machine
        switch(state) {
            case MENU:
                menu();
                break;
            case INS1:
                instruct1();
                break;
            case INS2:
                instruct2();
                break;
            case INS3:
                instruct3();
                break;
            case INS4:
                instruct4();
                break;
            case SA1:
                sceneA1();
                break;
            case SA2:
                sceneA2();
                break;
            case SA3:
                sceneA3();
                break;
            case SA4:
                sceneA4();
                break;
            case SA5:
                sceneA5();
                break;
            case SA6:
                sceneA6();
                break;
            case SA7:
                sceneA7();
                break;
            case SA8:
                sceneA8();
                break;
            case SA9:
                sceneA9();
                break;
            case INSTEAR:
                tearInstruct();
                break;
            case TEARGAME1:
                tearGame1();
                break;
            case TEARGAME2:
                tearGame2();
                break;
            case TEARWIN:
                tearWin();
                break;
            case TEARLOSE1:
                tearLose1(); 
                break;
            case TEARLOSE2:
                tearLose2();
                break;
            case PAUSETEAR1:
                pauseTear1();
                break;
            case PAUSETEAR2:
                pauseTear2();
                break;
            case INSMAZE:
                mazeInstruct();
                break;
            case MAZEGAME1:
                mazeGame1();
                break;
            case MAZEGAME2:
                mazeGame2();
                break;
            case MAZELOSE1:
                mazeLose1();
                break;
            case MAZELOSE2:
                mazeLose2();
                break;
            case PAUSEMAZE1:
                pauseMaze1();
                break;
            case PAUSEMAZE2:
                pauseMaze2();
                break;
            case MAZEWIN:
                mazeWin();
                break;
            case FINAL1:
                final1();
                break; 
            case FINAL2:
                final2();
                break; 
            case FINAL3:
                final3();
                break;  
            case CREDITS:
                credits();
                break;
        }      
    }
}

// ================================= INITIALIZE ==================================
// Sets up GBA
void initialize() {
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;

    vOffWater = 0;
    vOffCredit = 0;
    seed = 0;
    fadeCounter = 0;

    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    DMANow(3, &spritesheetTiles, &CHARBLOCK[4], (spritesheetTilesLen / 2));
    
    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4) | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT);

    REG_BG0CNT = BG_SIZE_TALL | BG_4BPP | BG_CHARBLOCK(0) | BG_SCREENBLOCK(31);

    // Set up the first state
    goToMenu();
}

// ============================== STATE FUNCTION ===============================
void menu() {
    // Start the first scene
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        playSoundA(Run, RUNLEN, RUNFREQ, 1);
        goToSceneA1();
    }
    // Show general game instructions
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToInstruct1();
    }
}

// ============================== GENERAL GAME INSTRUCTIONS ===============================
void instruct1() {
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        goToInstruct2();
    }
}
void instruct2() {
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        goToInstruct3();
    } else if (BUTTON_PRESSED(BUTTON_LEFT)) {
        goToInstruct1();
    }
}
void instruct3() {
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        goToInstruct4();
    } else if (BUTTON_PRESSED(BUTTON_LEFT)) {
        goToInstruct2();
    }
}
void instruct4() {
    // Start the first scene
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        playSoundA(Run, RUNLEN, RUNFREQ, 1);
        goToSceneA1();
    } else if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToMenu();
    } else if (BUTTON_PRESSED(BUTTON_LEFT)) {
        goToInstruct3();
    }
}

// ============================== OPENNING SCENE ============================== //
void sceneA1() {
    if (BUTTON_PRESSED(BUTTON_RIGHT))
        goToSceneA2();
}
void sceneA2() {
	waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_RIGHT))
        goToSceneA3();
}
void sceneA3() {
	waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_RIGHT))
        goToSceneA4();
}
void sceneA4() {
	waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_RIGHT))
        goToSceneA5();
}
void sceneA5() {
	waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_RIGHT))
        goToSceneA6();
}
void sceneA6() {
	waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_RIGHT))
        goToSceneA7();
}
void sceneA7() {
	waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_RIGHT))
        goToSceneA8();
}
void sceneA8() {
	waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_RIGHT))
        goToSceneA9();
}

// ================================== TEAR GAME =============================== //
// Gives instructions to the tear game
void sceneA9() {
	waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        goToTearInstruct();
    }
}

// Starts the tear game, normal mode
void tearInstruct() {
	waitForVBlank();
    seed++;
    if (BUTTON_PRESSED(BUTTON_START)) {
        while (fadeCounter < 17) {
            REG_BLDY = BLD_TOP(fadeCounter);
            fadeCounter++;
        }
        srand(seed);
        goToTearGame1();
        initTearGame1();
    }
}

// Tear Game, normal mode
void tearGame1() {
    while (fadeCounter >= 0) {
        for (int i = 0; i < 5; i++) {
            waitForVBlank();
        }
        REG_BLDY = BLD_TOP(fadeCounter);
        fadeCounter--;
    }
    updateTearGame1();
    drawTearGame1();
    waitForVBlank();

    DMANow(3, &shadowOAM, OAM, (128 * 4) | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT);

    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPauseTear1();
    }

    // Check if the player lost or won
    if (myScore == 7) {
        goToTearWin();
        while (fadeCounter < 17) {
            REG_BLDY = BLD_TOP(fadeCounter);
            fadeCounter++;
        }
    }
    if (livesRemaining == 0) {
        goToTearLose1();
    }
}

// Tear Game, cheat mode
void tearGame2(){
    while (fadeCounter >= 0) {
        for (int i = 0; i < 5; i++) {
            waitForVBlank();
        }
        REG_BLDY = BLD_TOP(fadeCounter);
        fadeCounter--;
    }
    updateTearGame2();
    drawTearGame2();
    waitForVBlank();

    DMANow(3, &shadowOAM, OAM, (128 * 4) | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT);

    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPauseTear2();
    }

    // Check if the player lost or won
    if (myScore == 7) {
        goToTearWin();
        while (fadeCounter < 17) {
            REG_BLDY = BLD_TOP(fadeCounter);
            fadeCounter++;
        }
    }
}

// Losing Tear Game, normal mode
void tearLose1() {
    // Start tear game again
    seed++;
    if (BUTTON_PRESSED(BUTTON_START)) {
        while (fadeCounter < 17) {
            REG_BLDY = BLD_TOP(fadeCounter);
            fadeCounter++;
        }
        srand(seed);
        goToTearGame1();
        initTearGame1();
    }
    // Activate the cheat in Tear Game
    if (BUTTON_PRESSED(BUTTON_A)) {
        while (fadeCounter < 17) {
            REG_BLDY = BLD_TOP(fadeCounter);
            fadeCounter++;
        }
        srand(seed);
        goToTearGame2();
        initTearGame2();
    }
    // Main menu
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

// Losing Tear Game, cheat mode
void tearLose2() {
    // Start tear game again, cheat mode
    if (BUTTON_PRESSED(BUTTON_START)) {
        while (fadeCounter < 17) {
            REG_BLDY = BLD_TOP(fadeCounter);
            fadeCounter++;
        }
        srand(seed);
        goToTearGame2();
        initTearGame2();
    }
    // Main menu
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

void pauseTear1() {
    // Go back to Tear Game, normal mode
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToTearGame1();
    // Main menu
    } else if (BUTTON_PRESSED(BUTTON_SELECT)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

void pauseTear2() {
    waitForVBlank();
    // Go back to Tear Game, cheat mode
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToTearGame2();
    // Go to main menu
    } else if (BUTTON_PRESSED(BUTTON_SELECT)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

// ============================= THE LOVE MAZE =========================== //

// Tear win takes you to Maze Game instruction page
void tearWin() {
    while (fadeCounter >= 0) {
        for (int i = 0; i < 5; i++) {
            waitForVBlank();
        }
        REG_BLDY = BLD_TOP(fadeCounter);
        fadeCounter--;
    }
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        goToMazeInstruct();
    }
}

// Instructions page takes you to the Maze Game
void mazeInstruct() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        playSoundA(HouseOfCards, HOUSEOFCARDSLEN, HOUSEOFCARDSFREQ, 1);
        goToMazeGame1();
        initMazeGame1();
    }
}

// Start the Maze Game, normal mode
void mazeGame1() {
    updateMazeGame1();
    drawMazeGame1();
    waitForVBlank();
    REG_BG0VOFF = vOff;
    REG_BG0HOFF = hOff;
    REG_BG1VOFF = (vOffWater / 2);
    REG_BG1HOFF = 0;

    DMANow(3, &shadowOAM, OAM, (128 * 4) | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT);

    // Pause game
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPauseMaze1();
    }

    // Check if the player lost or won
    if (lives == 0) {
        goToMazeLose1();
    } else if (winGame) {
        stopSound();
        playSoundB(DoorSound, DOORSOUNDLEN, DOORSOUNDFREQ, 0);
        goToMazeWin();
    }

    vOffWater++;
}

// Starts the Maze Game, cheat mode
void mazeGame2() {
    updateMazeGame2();
    drawMazeGame2();
    waitForVBlank();
    REG_BG0VOFF = vOff;
    REG_BG0HOFF = hOff;
    REG_BG1VOFF = (vOffWater / 2);
    REG_BG1HOFF = 0;

    DMANow(3, &shadowOAM, OAM, (128 * 4) | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT);

    // Pause game
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPauseMaze2();
    }

    // Check if the player lost or won
    if (lives == 0) {
        goToMazeLose2();
    } else if (winGame) {
        stopSound();
        playSoundB(DoorSound, DOORSOUNDLEN, DOORSOUNDFREQ, 0);
        goToMazeWin();
    }

    vOffWater++;
}

// Pausing Maze Game, normal mode
void pauseMaze1() {
    waitForVBlank();
    // Go back to Maze Game, normal mode
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToMazeGame1();
    // Main menu
    } else if (BUTTON_PRESSED(BUTTON_SELECT)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

// Pausing the Maze Game, cheat mode
void pauseMaze2() {
    waitForVBlank();
    // Go back to Maze Game, cheat mode
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToMazeGame2();
    // Main menu
    } else if (BUTTON_PRESSED(BUTTON_SELECT)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

// Loosing the Maze Game, normal mode
void mazeLose1() {
    waitForVBlank();

    // Start maze game again
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        playSoundA(HouseOfCards, HOUSEOFCARDSLEN, HOUSEOFCARDSFREQ, 1);
        initMazeGame1();
        goToMazeGame1();

    }
    // Activate the easy maze game
    if (BUTTON_PRESSED(BUTTON_A)) {
        goToMazeGame2();
        initMazeGame2();
    }
    // Main menu
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

// Loosing the Maze Game, cheat mode
void mazeLose2() {
    waitForVBlank();

    // Start maze game again
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        playSoundA(HouseOfCards, HOUSEOFCARDSLEN, HOUSEOFCARDSFREQ, 1);
        initMazeGame2();
        goToMazeGame2();
    }
    // Main menu
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

// Win state takes you to a black page
void mazeWin() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        playSoundA(Sea, SEALEN, SEAFREQ, 1);

        while (fadeCounter < 17) {
            REG_BLDY = BLD_TOP(fadeCounter);
            fadeCounter++;
        }

        goToFinal1();
    }
}

// ============================= THE ENDING SCENE =========================== //
void final1() {
    while (fadeCounter >= 0) {
        for (int i = 0; i < 30; i++) {
            waitForVBlank();
        }
        REG_BLDY = BLD_TOP(fadeCounter);
        fadeCounter--;
    }

    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        goToFinal2();
    }
}

void final2() {
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        while (fadeCounter < 17) {
            REG_BLDY = BLD_TOP(fadeCounter);
            fadeCounter++;
        }
        goToFinal3();
    }
}
void final3() {
    while (fadeCounter >= 0) {
        for (int i = 0; i < 30; i++) {
            waitForVBlank();
        }
        REG_BLDY = BLD_TOP(fadeCounter);
        fadeCounter--;
    }
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        goToCredits();
    }
}

// Roll the credits
void credits() {
    waitForVBlank();
    // Update the offset registers with the actual offsets
    REG_BG0VOFF = (vOffCredit / 6); //The credits roll
    REG_BG1VOFF = (vOffCredit / 4); // The credits

    // Makes the credits stop once it reaches the buttom of names page
    if (vOffCredit < 2100) {
        vOffCredit++;
    }

    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        playSoundA(INeedU, INEEDULEN, INEEDUFREQ, 1);
        goToMenu();
    }
}

// ===================================================================================================
// ========================================= GOTO FUNCTIONS ==========================================
// ===================================================================================================

// Sets up the Main Menu state
void goToMenu() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, menuPal, PALETTE, 256);
	DMANow(3, &menuTiles, &CHARBLOCK[0], (menuTilesLen / 2));
	DMANow(3, &menuMap, &SCREENBLOCK[31], (menuMapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = MENU;
}

// ======================== GENERAL GAME INSTRUCTIONS SETUP ========================
// Sets up the General Instructions 1 state
void goToInstruct1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, Instr1Pal, PALETTE, 256);
    DMANow(3, &Instr1Tiles, &CHARBLOCK[0], (Instr1TilesLen / 2));
    DMANow(3, &Instr1Map, &SCREENBLOCK[31], (Instr1MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = INS1;
}

// Sets up the General Instructions 2 state
void goToInstruct2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, Instr2Pal, PALETTE, 256);
    DMANow(3, &Instr2Tiles, &CHARBLOCK[0], (Instr2TilesLen / 2));
    DMANow(3, &Instr2Map, &SCREENBLOCK[31], (Instr2MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = INS2;
}

// Sets up the General Instructions 3 state
void goToInstruct3() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, Instr3Pal, PALETTE, 256);
    DMANow(3, &Instr3Tiles, &CHARBLOCK[0], (Instr3TilesLen / 2));
    DMANow(3, &Instr3Map, &SCREENBLOCK[31], (Instr3MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = INS3;
}

// Sets up the General Instructions 4 state
void goToInstruct4() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, Instr4Pal, PALETTE, 256);
    DMANow(3, &Instr4Tiles, &CHARBLOCK[0], (Instr4TilesLen / 2));
    DMANow(3, &Instr4Map, &SCREENBLOCK[31], (Instr4MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = INS4;
}

// ============================== OPENNING SCENE SETUP ===============================
// Sets up the SceneA1 state
void goToSceneA1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA1Pal, PALETTE, 256);
    DMANow(3, &SceneA1Tiles, &CHARBLOCK[0], (SceneA1TilesLen / 2));
    DMANow(3, &SceneA1Map, &SCREENBLOCK[31], (SceneA1MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA1;
}

// Sets up the SceneA2 state
void goToSceneA2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA2Pal, PALETTE, 256);
    DMANow(3, &SceneA2Tiles, &CHARBLOCK[0], (SceneA2TilesLen / 2));
    DMANow(3, &SceneA2Map, &SCREENBLOCK[31], (SceneA2MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA2;
}

// Sets up the SceneA3 state
void goToSceneA3() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA3Pal, PALETTE, 256);
    DMANow(3, &SceneA3Tiles, &CHARBLOCK[0], (SceneA3TilesLen / 2));
    DMANow(3, &SceneA3Map, &SCREENBLOCK[31], (SceneA3MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA3;
}

// Sets up the SceneA4 state
void goToSceneA4() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA4Pal, PALETTE, 256);
    DMANow(3, &SceneA4Tiles, &CHARBLOCK[0], (SceneA4TilesLen / 2));
    DMANow(3, &SceneA4Map, &SCREENBLOCK[31], (SceneA4MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA4;
}

// Sets up the SceneA5 state
void goToSceneA5() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA5Pal, PALETTE, 256);
    DMANow(3, &SceneA5Tiles, &CHARBLOCK[0], (SceneA5TilesLen / 2));
    DMANow(3, &SceneA5Map, &SCREENBLOCK[31], (SceneA5MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA5;
}

// Sets up the SceneA6 state
void goToSceneA6() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA6Pal, PALETTE, 256);
    DMANow(3, &SceneA6Tiles, &CHARBLOCK[0], (SceneA6TilesLen / 2));
    DMANow(3, &SceneA6Map, &SCREENBLOCK[31], (SceneA6MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA6;
}

// Sets up the SceneA7 state
void goToSceneA7() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA7Pal, PALETTE, 256);
    DMANow(3, &SceneA7Tiles, &CHARBLOCK[0], (SceneA7TilesLen / 2));
    DMANow(3, &SceneA7Map, &SCREENBLOCK[31], (SceneA7MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA7;
}

// Sets up the SceneA8 state
void goToSceneA8() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA8Pal, PALETTE, 256);
    DMANow(3, &SceneA8Tiles, &CHARBLOCK[0], (SceneA8TilesLen / 2));
    DMANow(3, &SceneA8Map, &SCREENBLOCK[31], (SceneA8MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA8;
}

// Sets up the SceneA9 state
void goToSceneA9() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, SceneA9Pal, PALETTE, 256);
    DMANow(3, &SceneA9Tiles, &CHARBLOCK[0], (SceneA9TilesLen / 2));
    DMANow(3, &SceneA9Map, &SCREENBLOCK[31], (SceneA9MapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = SA9;
}

// ============================== TEAR GAME SETUP ===============================
// Sets up the Tear Game Instructions state
void goToTearInstruct() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, TearGameInstrPal, PALETTE, 256);
    DMANow(3, &TearGameInstrTiles, &CHARBLOCK[0], (TearGameInstrTilesLen / 2));
    DMANow(3, &TearGameInstrMap, &SCREENBLOCK[31], (TearGameInstrMapLen / 2));

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = INSTEAR;
}

// Sets up the Tear Game, normal mode state
void goToTearGame1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, facePal, PALETTE, 256);
    DMANow(3, faceTiles, &CHARBLOCK[0], faceTilesLen / 2);
    DMANow(3, faceMap, &SCREENBLOCK[31], faceMapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = TEARGAME1;
}

// Sets up the Tear Game, cheat mode state
void goToTearGame2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, facePal, PALETTE, 256);
    DMANow(3, faceTiles, &CHARBLOCK[0], faceTilesLen / 2);
    DMANow(3, faceMap, &SCREENBLOCK[31], faceMapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = TEARGAME2;
}

// Sets up the Tear Game, any mode, win state
void goToTearWin() {
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4) | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT);

    // Load the Win screen's Palette and the Tiles/Map which shows the character openning her eyes
    DMANow(3, OpenEye1Pal, PALETTE, 256);
    DMANow(3, &OpenEye1Tiles, &CHARBLOCK[0], OpenEye1TilesLen / 2);
    DMANow(3, &OpenEye1Map, &SCREENBLOCK[31], OpenEye1MapLen / 2);
    // This extends the eyes openning scene
    for (int i = 0; i < 90; i++) {
        waitForVBlank();
    }
    DMANow(3, OpenEye2Pal, PALETTE, 256);
    DMANow(3, &OpenEye2Tiles, &CHARBLOCK[0], OpenEye2TilesLen / 2);
    DMANow(3, &OpenEye2Map, &SCREENBLOCK[31], OpenEye2MapLen / 2);
    // This extends the eyes openning scene
    for (int i = 0; i < 90; i++) {
        waitForVBlank();
    }
    DMANow(3, OpenEye3Pal, PALETTE, 256);
    DMANow(3, &OpenEye3Tiles, &CHARBLOCK[0], OpenEye3TilesLen / 2);
    DMANow(3, &OpenEye3Map, &SCREENBLOCK[31], OpenEye3MapLen / 2);
    // This extends the eyes openning scene
    for (int i = 0; i < 90; i++) {
        waitForVBlank();
    }
    DMANow(3, OpenEye4Pal, PALETTE, 256);
    DMANow(3, &OpenEye4Tiles, &CHARBLOCK[0], OpenEye4TilesLen / 2);
    DMANow(3, &OpenEye4Map, &SCREENBLOCK[31], OpenEye4MapLen / 2);
    // This extends the eyes openning scene
    for (int i = 0; i < 400; i++) {
        waitForVBlank();
    }
    DMANow(3, TearWinPal, PALETTE, 256 );
    DMANow(3, &TearWinTiles, &CHARBLOCK[0], TearWinTilesLen / 2);
    DMANow(3, &TearWinMap, &SCREENBLOCK[31], TearWinMapLen / 2);

    state = TEARWIN;
}

// Sets up the Tear Game, normal mode, lose state
void goToTearLose1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, TearLose1Pal, PALETTE, 256);
    DMANow(3, TearLose1Tiles, &CHARBLOCK[0], TearLose1TilesLen / 2);
    DMANow(3, TearLose1Map, &SCREENBLOCK[31], TearLose1MapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = TEARLOSE1;
}

// Sets up the Tear Game, cheat mode, lose state
void goToTearLose2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, TearLose2Pal, PALETTE, 256);
    DMANow(3, TearLose2Tiles, &CHARBLOCK[0], TearLose2TilesLen / 2);
    DMANow(3, TearLose2Map, &SCREENBLOCK[31], TearLose2MapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = TEARLOSE2;
}

// Sets up the Tear Game, normal mode, pause state
void goToPauseTear1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, pausePal, PALETTE, 256);
    DMANow(3, pauseTiles, &CHARBLOCK[0], pauseTilesLen / 2);
    DMANow(3, pauseMap, &SCREENBLOCK[31], pauseMapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = PAUSETEAR1;
}

// Sets up the Tear Game, cheat mode, pause state
void goToPauseTear2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, pausePal, PALETTE, 256);
    DMANow(3, pauseTiles, &CHARBLOCK[0], pauseTilesLen / 2);
    DMANow(3, pauseMap, &SCREENBLOCK[31], pauseMapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = PAUSETEAR2;
}

// ============================ MAZE GAME SETUP ==============================
// Sets up the Maze Game Instructions state
void goToMazeInstruct() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a | BLD_BG1a;

    DMANow(3, MazeGameInstrPal, PALETTE, 256);
    DMANow(3, MazeGameInstrTiles, &CHARBLOCK[0], MazeGameInstrTilesLen / 2);
    DMANow(3, MazeGameInstrMap, &SCREENBLOCK[31], MazeGameInstrMapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = INSMAZE;
}

// Sets up the Maze Game, normal mode state
void goToMazeGame1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a | BLD_BG1a;

    DMANow(3, waterPal, PALETTE, 256);
    DMANow(3, waterTiles, &CHARBLOCK[0], waterTilesLen / 2);
    DMANow(3, waterMap, &SCREENBLOCK[30], waterMapLen / 2);
    REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(30)| BG_SIZE_SMALL;

    DMANow(3, mazeTiles, &CHARBLOCK[1], mazeTilesLen / 2);
    DMANow(3, mazeMap, &SCREENBLOCK[26], mazeMapLen / 2);
    REG_BG0CNT = BG_CHARBLOCK(1) | BG_SCREENBLOCK(26)| BG_SIZE_LARGE;

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, spritesheetPalLen/2);

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    state = MAZEGAME1;
}

// Sets up the Maze Game, cheat mode state
void goToMazeGame2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a | BLD_BG1a;

    DMANow(3, waterPal, PALETTE, 256);
    DMANow(3, waterTiles, &CHARBLOCK[0], waterTilesLen / 2);
    DMANow(3, waterMap, &SCREENBLOCK[30], waterMapLen / 2);
    REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(30)| BG_SIZE_SMALL;

    DMANow(3, mazeTiles, &CHARBLOCK[1], mazeTilesLen / 2);
    DMANow(3, mazeMap, &SCREENBLOCK[26], mazeMapLen / 2);
    REG_BG0CNT = BG_CHARBLOCK(1) | BG_SCREENBLOCK(26)| BG_SIZE_LARGE;

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, spritesheetPalLen/2);

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    state = MAZEGAME2;
}

// Sets up the Maze Game, normal mode, lose state
void goToMazeLose1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, MazeLose1Pal, PALETTE, 256);
    DMANow(3, MazeLose1Tiles, &CHARBLOCK[0], MazeLose1TilesLen / 2);
    DMANow(3, MazeLose1Map, &SCREENBLOCK[31], MazeLose1MapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = MAZELOSE1;
}

// Sets up the Maze Game, cheat mode state
void goToMazeLose2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, MazeLose2Pal, PALETTE, 256);
    DMANow(3, MazeLose2Tiles, &CHARBLOCK[0], MazeLose2TilesLen / 2);
    DMANow(3, MazeLose2Map, &SCREENBLOCK[31], MazeLose2MapLen / 2);
    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;
    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));
    waitForVBlank();
    state = MAZELOSE2;
}

// Sets up the Maze Game, normal mode, pause state
void goToPauseMaze1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, pausePal, PALETTE, 256);
    DMANow(3, pauseTiles, &CHARBLOCK[0], pauseTilesLen / 2);
    DMANow(3, pauseMap, &SCREENBLOCK[31], pauseMapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = PAUSEMAZE1;
}

// Sets up the Maze Game, cheat mode, pause state
void goToPauseMaze2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, pausePal, PALETTE, 256);
    DMANow(3, pauseTiles, &CHARBLOCK[0], pauseTilesLen / 2);
    DMANow(3, pauseMap, &SCREENBLOCK[31], pauseMapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = PAUSEMAZE2;
}

// Sets up the Maze Game, any mode, win state
void goToMazeWin() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a | BLD_BG1a;

    DMANow(3, blankPal, PALETTE, 256);
    DMANow(3, blankTiles, &CHARBLOCK[0], pauseTilesLen / 2);
    DMANow(3, blankMap, &SCREENBLOCK[31], pauseMapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = MAZEWIN;
}

// ============================= FINAL SCENES SETUP ==========================
// Sets up the Final Scene 1
void goToFinal1() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, Final1Pal, PALETTE, 256);
    DMANow(3, Final1Tiles, &CHARBLOCK[0], Final1TilesLen / 2);
    DMANow(3, Final1Map, &SCREENBLOCK[31], Final1MapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = FINAL1;
}

// Sets up the Final Scene 2
void goToFinal2() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;

    DMANow(3, Final2Pal, PALETTE, 256);
    DMANow(3, Final2Tiles, &CHARBLOCK[0], Final2TilesLen / 2);
    DMANow(3, Final2Map, &SCREENBLOCK[31], Final2MapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = FINAL2;
}

// Sets up the Final Scene 3
void goToFinal3() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    REG_BLDCNT = BLD_WHITE | BLD_BG0a;

    DMANow(3, Final3Pal, PALETTE, 256);
    DMANow(3, Final3Tiles, &CHARBLOCK[0], Final3TilesLen / 2);
    DMANow(3, Final3Map, &SCREENBLOCK[31], Final3MapLen / 2);

    REG_BG0VOFF = 0;
    REG_BG0HOFF = 0;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    waitForVBlank();
    state = FINAL3;
}

// Sets up the Credits
void goToCredits() {
    REG_DISPCTL = MODE0 | BG1_ENABLE | BG0_ENABLE;

    DMANow(3, creditsPal, PALETTE, 256 | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT);

    REG_BG1CNT = BG_SIZE_TALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(30);
    DMANow(3, &creditsTiles, &CHARBLOCK[0], creditsTilesLen / 2);
    DMANow(3, &creditsMap, &SCREENBLOCK[30], creditsMapLen / 2);

    REG_BG0CNT = BG_SIZE_TALL | BG_CHARBLOCK(2) | BG_SCREENBLOCK(28);
    DMANow(3, &creditsrollTiles, &CHARBLOCK[2], creditsrollTilesLen / 2);
    DMANow(3, &creditsrollMap, &SCREENBLOCK[28], creditsrollMapLen / 2);

    hideSprites();
    DMANow(3, &shadowOAM, OAM, (128 * 4));

    state = CREDITS;
}