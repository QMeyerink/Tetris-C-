#include "navswitch.h"
#include "system.h"
#include "pacer.h"
#include "ir_serial.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include <avr/io.h>
#include "communication.h"

//
void game_init(void) {

    system_init ();
    tinygl_init (2000);
    pacer_init(3000);
    navswitch_init ();
    ir_uart_init ();
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (20);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

}


/* Start game at the same time. */
void start_game(void)
{
    game_init();

    int opponent_ready = 0;
    int navswitch_pushed = 0;
    tinygl_text("Ready?");

    while (navswitch_pushed == 0) {
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            navswitch_pushed = 1;
        }
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
    }
    tinygl_clear();
    UCSR1A |= BIT (TXC1);
    UCSR1A |= BIT (RXEN1);

    while (opponent_ready == 0) {
        if(victory('/') == 1) {
            opponent_ready = 1;
        }

        send_failed('/');
        pacer_wait();
    }
    //tinygle_text("Go!");
    //while
}




