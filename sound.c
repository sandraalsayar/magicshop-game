#include "lib.h"
#include "sound.h"

void setupSounds()
{
    REG_SOUNDCNT_X = SND_ENABLED;

	REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 | 
                     DSA_OUTPUT_RATIO_100 | 
                     DSA_OUTPUT_TO_BOTH | 
                     DSA_TIMER0 | 
                     DSA_FIFO_RESET |
                     DSB_OUTPUT_RATIO_100 | 
                     DSB_OUTPUT_TO_BOTH | 
                     DSB_TIMER1 | 
                     DSB_FIFO_RESET;

	REG_SOUNDCNT_L = 0;
}

void playSoundA( const unsigned char* sound, int length, int frequency, int loops) {
	dma[1].cnt = 0;
	
	int ticks = PROCESSOR_CYCLES_PER_SECOND/frequency;
	
	DMANow(1, sound, REG_FIFO_A, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);
	
	REG_TM0CNT = 0;
	
	REG_TM0D = -ticks;
	REG_TM0CNT = TIMER_ON;

    // TODO 2.1:  Assign all of soundA’s appropriate struct values
	soundA.data = sound;
	soundA.length = length;
	soundA.frequency = frequency;
	soundA.loops = loops;
	soundA.isPlaying = 1;
	soundA.duration = (VBLANK_FREQ * length)/frequency;
	soundA.vBlankCount = 0;
}


void playSoundB( const unsigned char* sound, int length, int frequency, int loops) {

	dma[2].cnt = 0;

	int ticks = PROCESSOR_CYCLES_PER_SECOND/frequency;

	DMANow(2, sound, REG_FIFO_B, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);

	REG_TM1CNT = 0;
	
	REG_TM1D = -ticks;
	REG_TM1CNT = TIMER_ON;
	
    // TODO 2.2:  Assign all of soundB’s appropriate struct values
	soundB.data = sound;
	soundB.length = length;
	soundB.frequency = frequency;
	soundB.loops = loops;
	soundB.isPlaying = 1;
	soundB.duration = (VBLANK_FREQ * length)/frequency;
	soundB.vBlankCount = 0;
}

void setupInterrupts()
{
	REG_IME = 0;
	
	// TODO 3.1 - Set up the interrupt handler
    REG_INTERRUPT = (unsigned int) interruptHandler;
	REG_IE |= INT_VBLANK;
	REG_DISPSTAT |= INT_VBLANK_ENABLE;
	REG_IME = 1;
}

void interruptHandler() {

	REG_IME = 0;

	if(REG_IF & INT_VBLANK) {
		if (soundA.isPlaying) {

			//TODO 3.2 - Handle soundA playing in the interruptHandler function
			soundA.vBlankCount++;
			if (soundA.vBlankCount >= soundA.duration) {
				if (soundA.loops) {
					playSoundA(soundA.data, soundA.length, soundA.frequency, soundA.loops);
				} else {
					soundA.isPlaying = 0;
					dma[1].cnt = 0;
					REG_TM0CNT = 0;
				}

			}
		}

		if (soundB.isPlaying) {

			//TODO 3.3 - Handle soundB playing in the interruptHandler function
			soundB.vBlankCount++;
			if (soundB.vBlankCount >= soundB.duration) {
				if (soundB.loops) {
					playSoundB(soundB.data, soundB.length, soundB.frequency, soundB.loops);
				} else {
					soundB.isPlaying = 0;
					dma[2].cnt = 0;
					REG_TM1CNT = 0;
				}

			}
		}
		
		REG_IF = INT_VBLANK; 
	}

	REG_IME = 1;
}

void pauseSound() {

	// TODO 4.1 - Complete the pauseSound function
		REG_TM0CNT = 0;
		soundA.isPlaying = 0;
		REG_TM1CNT = 0;
		soundB.isPlaying = 0;
}

void unpauseSound() {

	// TODO 4.2 - Complete the unpauseSound function
		REG_TM0CNT = TIMER_ON;
		soundA.isPlaying = 1;
		REG_TM1CNT = TIMER_ON;
		soundB.isPlaying = 1;

}

void stopSound() {

    // TODO 4.3 - Complete the stopSound function
		dma[1].cnt = 0;
		REG_TM0CNT = 0;
		soundA.isPlaying = 0;

		dma[2].cnt = 0;
		REG_TM1CNT = 0;
		soundB.isPlaying = 0;
}