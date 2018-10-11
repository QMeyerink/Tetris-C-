#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/** Constantly checking if the opponent failed while the player is still playing. */
int victory(void);

/** Send a character to opponent to tell the player failed. */
void send_failed(void);

int check_ready(void);

void send_ready(void);

#endif
