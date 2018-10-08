#include <stdlib.h>
#include <stdio.h>

// Moves active block right when player uses navswitch
int moveleft(int moveArray[7][5],int statArray[7][5])
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

int moveright(int moveArray[7][5],int statArray[7][5])
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

int movedown(int moveArray[7][5],int statArray[7][5])
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
