#include "blinky_thread.h"
#include "new_thread2.h"
#include "event_define.h"
#include <stdio.h>
//void check_alive_threads(int alive_num);
extern void initialise_monitor_handles(void); // for printf
extern  ssp_err_t send_serial_msg(char *msg);


/* New Thread entry function */
void new_thread2_entry(void)
{
    initialise_monitor_handles(); // for printf()
    ssp_err_t   status;
    //int  msg_len = 0;
    //char msg[50];
    int     err_count = 0;

    ULONG actual_events;



    while (1)
    {

//        char tx_buf[] = "efgh";
//        UINT    err_g_queue_2;
//        char    rx_buf[4];
        actual_events = 0;
        status = tx_event_flags_get(&g_new_event_flags0,
                                            EVENT_FLAG_2 | watchdog_FLAG_threads2_15,
                                            TX_OR,
                                            &actual_events,
                                            TX_WAIT_FOREVER);
                                            //TX_NO_WAIT
        //printf("status2 = %d\n", status);
        //printf("actual_events2 = %lu\n", actual_events);
        //printf("thread2-1\n");
        if(TX_SUCCESS == status)
        {
            if (actual_events & watchdog_FLAG_threads2_15)
            {
                check_alive_threads(14);
                tx_event_flags_set(&g_new_event_flags0, ~watchdog_FLAG_threads2_15, TX_AND);
            }

            if (actual_events & EVENT_FLAG_2)
            {
                status = tx_mutex_get(&g_new_mutex0, 100);
                //g_ioport.p_api->pinWrite(leds.p_leds[0], IOPORT_LEVEL_LOW);
                //msg_len = snprintf(msg, sizeof(msg), "%s\r\n", rx_buf);
                //status = g_uart0.p_api->write(g_uart0.p_ctrl, (uint8_t*)"efgh\r\n", (uint32_t)6);
                send_serial_msg("efgh\r\n");
                status = tx_mutex_put(&g_new_mutex0);

                if (TX_SUCCESS != status)
                {
                    send_serial_msg("Error-thread2 !!\r\n");
                }
                tx_event_flags_set(&g_new_event_flags0, ~EVENT_FLAG_2, TX_AND);
                tx_thread_sleep(1);
            }
        }




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
//            check_alive_threads(14);
//        }

        tx_thread_sleep (1);
    }
}
