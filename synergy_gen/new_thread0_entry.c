#include "blinky_thread.h"
#include "new_thread0.h"
#include "event_define.h"
#include <stdio.h>
void check_alive_threads(int alive_num);
extern void initialise_monitor_handles(void); // for printf()
extern  ssp_err_t send_serial_msg(char *msg);

/* New Thread entry function */
void new_thread0_entry(void)
{
    initialise_monitor_handles(); // for printf()
    ssp_err_t   status;
    ULONG actual_events;
    //int  msg_len = 0;
    //char msg[50];
    int     err_count = 0;


    while (1)
    {

        //char tx_buf[] = "abcd";
        //char    rx_buf[4];
        //UINT    err_g_queue_0;

        actual_events = 0;

        status = tx_event_flags_get(&g_new_event_flags0,
                                            EVENT_FLAG_1 | watchdog_FLAG_threads0_14,
                                            TX_OR,
                                            &actual_events,
                                            TX_WAIT_FOREVER);



        if(TX_SUCCESS == status)
        {
            if (actual_events & watchdog_FLAG_threads0_14)
            {
                check_alive_threads(13);
                tx_event_flags_set(&g_new_event_flags0, ~watchdog_FLAG_threads0_14, TX_AND);
            }

            if (actual_events & EVENT_FLAG_1)
            {
                status = tx_mutex_get(&g_new_mutex0, 100);
                //g_ioport.p_api->pinWrite(leds.p_leds[0], IOPORT_LEVEL_LOW);
                //msg_len = snprintf(msg, sizeof(msg), "%s\r\n", rx_buf);
                //status = g_uart0.p_api->write(g_uart0.p_ctrl, (uint8_t*)"abcd\r\n", (uint32_t)6);
                send_serial_msg("abcd\r\n");

                if (TX_SUCCESS != status)
                {
                    send_serial_msg("Error-thread0 !!\r\n");
                }
                tx_event_flags_set(&g_new_event_flags0, ~EVENT_FLAG_1, TX_AND);
                tx_thread_sleep(1);
            }
        }



        status = tx_mutex_put(&g_new_mutex0);
        if (TX_SUCCESS != status) err_count++;
//        status = tx_event_flags_get(&watchdog_Event_Flags,
//                                            watchdog_FLAG,
//                                            TX_AND,
//                                            &actual_events,
//                                            //TX_WAIT_FOREVER
//                                            TX_NO_WAIT);
//
//        if (status == TX_SUCCESS)
//        {
//            check_alive_threads(13);
//        }
        tx_thread_sleep (1);

    }

//    /* TODO: add your own code here */
//    while (1)
//    {
//        /* LED type structure */
//       bsp_leds_t leds;
//       /* LED state variable */
//       ioport_level_t level = IOPORT_LEVEL_HIGH;
//
//       /* Get LED information for this board */
//       R_BSP_LedsGet(&leds);
//
//       /* If this board has no leds then trap here */
//       if (0 == leds.led_count)
//       {
//           while(1);   // There are no leds on this board
//       }
//
//       while (1)
//       {
//           /* Determine the next state of the LEDs */
//           if(IOPORT_LEVEL_LOW == level)
//           {
//               level = IOPORT_LEVEL_HIGH;
//           }
//           else
//           {
//               level = IOPORT_LEVEL_LOW;
//           }
//
//           /* Update all board LEDs */
//           for(uint32_t i = 0; i < leds.led_count; i++)
//           {
//               g_ioport.p_api->pinWrite(leds.p_leds[i], level);
//           }
//           tx_thread_sleep (50);
//       }


}

