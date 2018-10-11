#include "navswitch.h"
#include "system.h"
#include "pacer.h"
#include "ir_serial.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


/* Start game at the same time. */
void start_game(void)
{
    navswitch_init ();
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (10);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    int opponent_ready = 0;
    int player_ready = 0;
    int checked = 0;

    while (checked == 0)
    {
        tinygl_text("Ready?");
        navswitch_pushed = 0;

        while (navswitch_pushed == 0) {
            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                navswitch_pushed = 1;
            pacer_wait ();
            tinygl_update ();
        }

        player_ready = 1;

        while (opponent_ready == 0) {

            if (ir_uart_write_ready_p ()) {
                ir_uart_putc ('R');
                }
            if (ir_uart_read_ready_p ()) {
                char check_opponent;
                check_opponent = ir_uart_getc ();
                if (check_opponent == 'R') {
                    opponent_ready = 1;
                }
            }
        }
        //tinygle_text("Go!");
        //while
    }
}



