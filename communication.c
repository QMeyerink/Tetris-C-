// File:    Game
// Authors: Quinlan Meyerink,
//          Haruka Ichinose
// Date:    11 Oct 2018
// Descr:   Communications module

#include "ir_uart.h"

/* Check if the board has recieved specified char from other board */
int victory(char recieve)
{

    ir_uart_init();
    int recieved = 0;
    char recieved_char = 0;

    if(ir_uart_read_ready_p ()) {
        recieved_char = ir_uart_getc ();
        if(recieved_char == recieve) {
            recieved = 1;

        }
    }
    return recieved;
}


/* Send a specified char to opponent  */
void send_failed(char send)
{

    if (ir_uart_write_ready_p ()) {
        ir_uart_putc(send);
    }

}
