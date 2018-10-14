// File:    Game
// Authors: Quinlan Meyerink,
//          Haruka Ichinose
// Date:    11 Oct 2018
// Descr:   Communications module

#include "ir_uart.h"

/* Check if the opponent is already failed and player won. */
int victory(char recieve)
{

    ir_uart_init();
    int player_victory = 0;

    if(ir_uart_read_ready_p ()) {
        char opponent_fail = 0;
        opponent_fail = ir_uart_getc ();
        if(opponent_fail == recieve) {
            player_victory = 1;

        }
    }
    return player_victory;
}


/* Send to opponent what the player failed. */
void send_failed(char send)
{

    if (ir_uart_write_ready_p ()) {
        ir_uart_putc(send);
    }

}
