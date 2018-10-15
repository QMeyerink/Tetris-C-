// File:    Game
// Authors: Quinlan Meyerink,
//          Haruka Ichinose
// Date:    11 Oct 2018
// Descr:   Game start module

#include "navswitch.h"
#include "system.h"
#include "pacer.h"
#include "ir_serial.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include <avr/io.h>
#include "communication.h"

// Initialise all game dependencies.
void game_init(void) {

    system_init ();
    tinygl_init (3000);
    pacer_init(2000);
    navswitch_init ();
    ir_uart_init ();
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (20);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

}


// Start game at the same time.
void start_game(void)
{
    game_init();

    int opponent_ready = 0;

    tinygl_text("Ready?");

    // Wait for player to 'ready up' and scroll 'Ready?'.
    while (navswitch_push_event_p (NAVSWITCH_PUSH) == 0) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
    }

    // Clear display and IR income value.
    tinygl_clear();
    UCSR1A |= BIT (TXC1);
    UCSR1A |= BIT (RXEN1);

    while (opponent_ready == 0) {
        tinygl_update();
        if(victory('/') == 1) {
            opponent_ready = 1;
        }

        send_failed('/');
        pacer_wait();
    }
}




