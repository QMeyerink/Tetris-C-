// File:    Game
// Authors: Quinlan Meyerink,
//          Haruka Ichinose
// Date:    11 Oct 2018
// Descr:   Main game source

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
#include "blocks.h"
#include "ir_uart.h"
#include "movements.h"
#include "communication.h"
#include "start_game.h"

// Pre-set global arrays.
int moveArray[7][5];
int statArray[7][5];
int dispArray[7][5];


#define CLOCK_SPEED 0x05
#define MOVE_DOWN_SPEED 7000
#define WIN_LOSE_CHAR ','


void resetgame(void)
//resets all arrays to zero - (may just use other reset)
{
    int i = 0;
    int j =0;
    for(; i < 7; i++) {
        j = 0;
        for(; j < 5; j++) {
            moveArray[i][j] = 0;
            statArray[i][j] = 0;
            dispArray[i][j] = 0;
        }
    }
}

int updatedisplay(void)
// Updates display array and performs and endgame check
{
    //iterates through all vals of move and statArray's,
    //and the updates the dispArray as needed.
    int i = 0;
    int j = 0;
    for(; i < 7; i++) {
        j = 0;
        for(; j < 5; j++) {
            //Check if newly spawned block hits current statblock.
            if ((moveArray[i][j] == 1)  && (statArray[i][j] == 1)) {
                return 1;
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

void resetboard(int array[7][5])
//resets given array to zeros (used for active board and resetting game)
{
    int i = 0;
    int j = 0;
    for(; i < 7; i++) {
        j = 0;
        for(; j < 5; j++) {
            array[i][j] = 0;

        }
    }
}

int addstationary(void)
//Moves a block from active to stationary by storing it in statArray
{
    int i = 0;
    int j = 0;
    for(; i < 7; i++) {
        j = 0;
        for(; j < 5; j++) {
            if((moveArray[i][j]) == 1) {
                statArray[i][j] = 1;
            }
        }
    }
    //Active block has been set to stationary, a new active block must be made.
    resetboard(moveArray);
    spawnblock(moveArray);
    updatedisplay();
    return 0;
}

int pixelset(void)
//Toggles pixels displayed dependent on the dispArray
{
    int i = 0;
    int j = 0;
    for(; i < 7; i++) {
        j = 0;
        for(; j < 5; j++) {
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

int checkmove(void)
// Checks if the navswitch has been used, and calls apporiate functions if so.
{
    int addstat = 0;
    if(navswitch_push_event_p (NAVSWITCH_WEST)) {
        moveleft(moveArray,statArray);
    }

    if(navswitch_push_event_p (NAVSWITCH_EAST)) {
        moveright(moveArray,statArray);
    }

    if(navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        addstat = movedown(moveArray,statArray);
        if(addstat == 1) {
            addstationary();
        }
    }

    return 0;
}

int end_scroll(int won)
//Function that scrolls a win or lose message if player won or lost
{
    tinygl_clear();
    tinygl_update();
    if(won == 1) {
        tinygl_text("You Won!");
    } else {
        send_char(WIN_LOSE_CHAR);
        tinygl_text ("You lost!");
    }

    while (1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update();
        if(navswitch_push_event_p (NAVSWITCH_PUSH)) {
            break;
        }
    }
    return 0;
}

//Checks all rows to see if any have become full (and need to be deleted) deletes if so.
int checkrows(void)
{
    int rowTotal = 0;
    int rowToRemove = 0;
    int removeRow = 0;

    int i = 0;
    int j = 0;

    //Loops through nested array checking if any rows are filled.
    for(; i < 7; i++) {
        rowTotal = 0;
        j = 0;
        for(; j < 5; j++) {
            if (statArray[i][j] == 1) {
                rowTotal += 1;
            }
            if(rowTotal == 5) {
                rowToRemove = i;
                removeRow = 1;
            }
        }
    }

    //If row is filled it is deleted and every block above it is moved down.
    j = 0;
    i = rowToRemove;
    if(removeRow == 1) {
        for(; j < 5; j++) {
            statArray[rowToRemove][j] = 0;
        }
        for(; i >= 0; i--) {
            j = 0;
            for(; j < 5; j++) {
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

    TCCR1B = CLOCK_SPEED;
    spawnblock(moveArray);
    updatedisplay();
    pixelset();
    TCNT1 = 0;

    int addstat = 0;
    int lost = 0;
    int won = 0;;

    //main function loop
    while (lost == 0) {
        tinygl_update();
        navswitch_update ();
        pixelset();
        checkmove();
        checkrows();

        if(recieve_char(WIN_LOSE_CHAR) == 1) {
            PORTC |= (1 << 2);
            won = 1;
        }

        if(TCNT1 > MOVE_DOWN_SPEED) {
            addstat = movedown(moveArray,statArray);
            if(addstat == 1) {
                addstationary();
            }
            TCNT1 = 0;
        }
        checkrows();
        lost = updatedisplay();
    }

    //Calls the end_scroll function to show either won or lost.
    if(won == 1) {
        end_scroll(1);
    } else {
        end_scroll(0);
    }
    return 0;
}

int main (void)
{
    while(1) {

        resetgame();

        start_game();

        playgame();

    }
    return 0;

}

