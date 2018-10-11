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
    int ready_recieved = 0;

    while (checked == 0)
    {
        tinygl_text("Ready?");

        while (!navswitch_push_event_p (NAVSWITCH_PUSH)) {
            pacer_wait ();
            tinygl_update ();
        }

        player_ready = 1;

        while (opponent_ready == 0) {
            ir_serial_ret_t ret;

            if (ir_uart_write_ready_p) {
                ir_serial_transmit(IR_SERIAL_OK);
            }
            if (ir_uart_read_ready_p) {
                ret = ir_serial_receive (&data);
                if (ret == IR_SERIAL_OK) {
                    opponent_ready == 1;
                }
            }
        }
        //tinygle_text("Go!");
        //while
    }
}



