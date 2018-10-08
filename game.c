#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "string.h"
#include <avr/io.h>
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "button.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "blocks.h"

// Pre-set global arrays.
int moveArray[7][5];
int statArray[7][5];
int dispArray[7][5];
int lost;

void resetgame(void)
//resets all arrays to zero - (may just use other reset)
{
    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
            moveArray[i][j] = 0;
            statArray[i][j] = 0;
            dispArray[i][j] = 0;
            lost = 0;
        }
    }
}
int updatedisplay(void) 
// Updates display array and performs and endgame check
{
	//iterates through all vals of move and statArray's,
	//and the updates the dispArray as needed.
    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
			//Check if newly spawned block hits current statblock.
            if ((moveArray[i][j] == 1)	&& (statArray[i][j] == 1)) {
                lost = 1;
                return 0;
            } else {
                if((moveArray[i][j] == 1) || (statArray[i][j] == 1)) {
                    dispArray[i][j] = 1;
                } else {
                    dispArray[i][j] =0;
                }
            }
        }
    }
    return 0;
}

void spawnblock(void)
//Spawns next random block at top of screen
{
	int block = 0;
	block  = (rand() % 3) + 1;
	
	if(block == 1) {
		block1(moveArray);
	}
	if( block == 2) {
		block2(moveArray);
	}
	if(block == 3) {
		block3(moveArray);
	}
	if(block == 4) {
		block4(moveArray);
	}
	
	updatedisplay();
}

void resetboard(int array[7][5])
//resets given array to zeros (used for active board and resetting game)
{

    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
            array[i][j] = 0;

        }
    }
}

int addstationary(void)
//Moves a block from active to stationary by storing it in statArray
{
    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
            if((moveArray[i][j]) == 1) {
                statArray[i][j] = 1;
            }
        }
    }
    //Active block has been set to stationary, a new active block must be made.
    resetboard(moveArray);
    spawnblock();
    return 0;
}

int pixelset(void)
//Toggles pixels displayed dependent on the dispArray
{

    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
			//Checks dispArray and toggles corrosponding pixel as required.
            if(dispArray[i][j] == 1) {
                tinygl_pixel_set(tinygl_point (j, i), 1);
            } else {
                tinygl_pixel_set(tinygl_point (j, i), 0);
            }

        }
    }
    return 0;
}

int moveleft(void)
// Moves active block right when player uses navswitch
{
	//First checks that any movement wont go off board, or if
	//a static block currently exists where block will move to.
    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
            if(moveArray[i][j] == 1) {
                if(j == 0) {
                    return 0;
                } else if(statArray[i][j] == 1) {
                    return 0;
                }
            }
        }
    }
	//If it is safe to move, every active pixel is moved left one.
    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
            if(moveArray[i][j] == 1) {
                moveArray[i][j-1] = 1;
                moveArray[i][j] = 0;
            }
        }
    }
    return 0;
}

int moveright(void)
//Moves the active block right when player moves nawswitch.
{
	//First checks that any movement wont go off board, or if
	//a static block currently exists where block will move to.
    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
            if(moveArray[i][j] == 1) {
                if((j == 4) || (statArray[i][j] == 1))  {
                    return 0;

                }
            }
        }
    }
    //If it is safe to move, every active pixel is moved right one.
    int i = 0;
    int j = 0;
    for(i = 6; i >= 0; i--) {
        for(j = 4; j >= 0; j--) {
            if(moveArray[i][j] == 1) {
                moveArray[i][j+1] = 1;
                moveArray[i][j] = 0;
            }
        }
    }
    return 0;
}

int movedown(void)
//Is the move block down function. Does checks for if block collision or bottom is met.
{
	//First checks that any movement wont go off board, or if
	//a static block currently exists where block will move to.
    for(int i = 0; i < 7; i++) {
        for( int j = 0; j < 5; j++) {
            if(moveArray[i][j] == 1) {
                if((i == 6) || (statArray[i+1][j] == 1)) {
                    addstationary();
                    return 0;
                }
            }
        }
    }
    //If it is safe to move, every active pixel is moved right one.
    int i = 0;
    int j = 0;
    for(i = 6; i >= 0; i--) {
        for(j = 4; j >= 0; j--) {
            if(moveArray[i][j] == 1) {
                moveArray[i+1][j] = 1;
                moveArray[i][j] = 0;
            }
        }
    }
    return 0;
}

int checkmove(void)
//Todo - Rotation calls in North and south directions (replacing current down)
// Checks if the navswitch has been used, and calls apporiate functions if so.
{
    if(navswitch_push_event_p (NAVSWITCH_WEST)) {
        moveleft();
    }

    if(navswitch_push_event_p (NAVSWITCH_EAST)) {
        moveright();
    }

    if(navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        movedown();
    }

    return 0;
}

int lost_scroll(void)
//ToDo
//Function that scrools.You lost! when player loses
{

    pacer_init (1000);
    tinygl_init (1000);

    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (10);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text ("You lost!");
    

    while (1) {
        pacer_wait ();
        tinygl_update ();
    }
    return 0;
}
int checkrows(void)
{
	int rowTotal = 0;
	int rowToRemove = 0;
	int removeRow = 0;
	
	 for(int i = 0; i < 7; i++) {
		 rowTotal = 0;
        for( int j = 0; j < 5; j++) {
			if (statArray[i][j] == 1) {
				rowTotal += 1;
			}
			if(rowTotal == 5) {
				rowToRemove = i;
				removeRow = 1;
			}
		}
	}
	if(removeRow == 1) {
		for(int j = 0; j < 5; j++) {
			statArray[rowToRemove][j] = 0;
		}
		for(int i = rowToRemove; i >= 0; i--) {
			for( int j = 0; j < 5; j++) {
				if(statArray[i][j] == 1) {
					statArray[i+1][j] = 1;
					statArray[i][j] = 0;
				}
			}
		}
	}
	updatedisplay();
	return 0;
}
	
int playgame(void) 
{
	// reset and make first block
	TCCR1B = 0x05;
    resetgame();
    spawnblock();
    pixelset();
    TCNT1 = 0;

	//main function loop
    while (lost == 0) {
        tinygl_update();
        navswitch_update ();
        pixelset();
        checkmove();
        checkrows();
        if(TCNT1 > 7000) {
			movedown();
			TCNT1 = 0;
		}
        updatedisplay();


    }
    lost_scroll();
    return 0;	
}	
int main (void)
{
	// initilise programs
    system_init ();
    pacer_init (1000);
    tinygl_init (1000);
    navswitch_init ();
    srand(time(NULL));
    
    playgame();
    
    return 0;
    
}

