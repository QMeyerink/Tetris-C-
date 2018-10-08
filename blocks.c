#include <stdlib.h>
#include <stdio.h>

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
