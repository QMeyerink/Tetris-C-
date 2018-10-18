#ifndef MOVEMENTS_H
#define MOVEMENTS_H

//Moves active block left if it is safe to do so.
int moveleft(int moveArray[7][5], int statArray[7][5]);

//Moves block right if it is safe to do so
int moveright(int moveArray[7][5], int statArray[7][5]);

//Moves block down if it is safe to do so, also return 1 if block is to become stationary. 
extern int movedown(int moveArray[7][5], int statArray[7][5]);


#endif /* MOVEMENTS_H  */
