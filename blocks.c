// File:    Game
// Authors: Quinlan Meyerink,
//          Haruka Ichinose
// Date:    11 Oct 2018
// Descr:   Blocks module

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

void block1(int moveArray[7][5])
{
    //Preset starting location of block type 1
    moveArray[0][2] = 1;
    moveArray[1][1] = 1;
    moveArray[1][2] = 1;
    moveArray[1][3] = 1;

}

void block2(int moveArray[7][5])
//Preset starting location of block type 2
{

    moveArray[0][2] = 1;
    moveArray[1][2] = 1;
    moveArray[2][2] = 1;

}

void block3(int moveArray[7][5])
//Preset starting location of block type 3
{

    moveArray[0][1] = 1;
    moveArray[0][2] = 1;
    moveArray[1][2] = 1;
    moveArray[1][3] = 1;

}

void block4(int moveArray[7][5])
//Preset starting location of block type 4
{

    moveArray[0][2] = 1;
    moveArray[0][3] = 1;
    moveArray[1][2] = 1;
    moveArray[1][3] = 1;

}

void spawnblock(int moveArray[7][5])
//Spawns next random block at top of screen
{

    int time = 0;
    int block = 0;
    //Using the TNCT1 timer 'random' number created
    time = TCNT1;
    block = time % 4 + 1;

    //Calls to block formation depending on generated number
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
}
