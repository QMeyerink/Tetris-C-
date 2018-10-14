#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/** Constantly checking if the opponent failed while the player is still playing. */
int victory(char recieve);

/** Send a character to opponent to tell the player failed. */
void send_failed(char send);


#endif
