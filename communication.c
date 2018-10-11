// File:    Game
// Authors: Quinlan Meyerink,
//          Haruka Ichinose
// Date:    11 Oct 2018
// Descr:   Communications module

#include "ir_uart.h"

/* Check if the opponent is already failed and player won. */
int victory(void)
{
    ir_uart_init ();
    int player_victory = 0;

    if(ir_uart_read_ready_p ()) {
        char opponent_fail = 0;
        opponent_fail = ir_uart_getc ();
        if(opponent_fail = 'W') {
            player_victory = 1;

        }
    }
    return player_victory;
}


/* Send to opponent what the player failed. */
void send_failed(void)
{
    ir_uart_init ();

    if (ir_uart_write_ready_p ()) {
        char player_failed = 'W';
        ir_uart_putc(player_failed);
    }

}

int check_ready(void) {

    ir_uart_init ();
    int player_ready = 0;

    if(ir_uart_read_ready_p ()) {
        char opponent_ready = 0;
        opponent_ready = ir_uart_getc ();
        if(opponent_ready = 'R') {
            player_ready = 1;

        }
    }
    return player_ready;
}

void send_ready(void)
{
    ir_uart_init ();

    if (ir_uart_write_ready_p ()) {
        char player_ready = 'R';
        ir_uart_putc(player_ready);
    }

}
