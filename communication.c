#include "ir_uart.h"

/* Check if the opponent is already failed and player won. */
int victory(void)
{
    ir_uart_init ();
    int player_victory = 0;

    while (1)
    {
        if(ir_uart_read_ready_p ())
        {
            char opponent_fail = 0;
            opponent_fail = ir_uart_getc ();
            if(opponent_fail = 'W')
            {
                player_victory = 1;
                break;
            }
        }
    }
    return player_victory;
}


/* Send to opponent what the player failed. */
void send_failed(void)
{
    ir_uart_init ();

    if (ir_uart_write_ready_p ())
    {
        char player_failed = 'W';
        ir_uart_putc(player_failed);
    }

}

