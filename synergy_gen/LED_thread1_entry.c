#include "LED_thread1.h"
#include "blinky_thread.h"
#include "event_define.h"
#include <stdio.h>

void check_alive_threads(int alive_num);
extern void initialise_monitor_handles(void); // for printf()

/* LED_thread1 entry function */
void LED_thread1_entry(void)
{
    initialise_monitor_handles(); // for printf()

    ssp_err_t   status;
    ULONG actual_events;
    //int timer = 0;
    //int next_event_timer = 0;

    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);

        actual_events = 0;

        status = tx_event_flags_get(&Event_Flags_Threads_LED,
                                                    Thread_FLAG_1 | watchdog_FLAG_1,
                                                    TX_OR,
                                                    &actual_events,
                                                    TX_WAIT_FOREVER);
        if(TX_SUCCESS == status)
        {
            if (actual_events & watchdog_FLAG_1)
            {
                check_alive_threads(3);
                tx_event_flags_set(&Event_Flags_Threads_LED, ~watchdog_FLAG_1, TX_AND);
            }
            if(actual_events &Thread_FLAG_1)
            {
                g_ioport.p_api->pinWrite(LED1_PIN, IOPORT_LEVEL_HIGH);

                tx_thread_sleep (100);

                g_ioport.p_api->pinWrite(LED1_PIN, IOPORT_LEVEL_LOW);

                tx_thread_sleep (30);
                tx_event_flags_set(&Event_Flags_Threads_LED, ~Thread_FLAG_1, TX_AND);
                tx_event_flags_set(&Event_Flags_Threads_LED, Thread_FLAG_2, TX_OR);

            }
        }
//        status = tx_event_flags_get(&watchdog_Event_Flags,
//                                            watchdog_FLAG,
//                                            TX_AND,
//                                            &actual_events,
//                                            //TX_WAIT_FOREVER
//                                            TX_NO_WAIT);
//
//        if (status == TX_SUCCESS)
//        {
//            check_alive_threads(3);
//        }

        tx_thread_sleep (1);


//        if(TX_SUCCESS == status)
//        {
//            //printf("LED1\n");
//
//            if ((actual_events & Thread_FLAG_1) && timer == 0)
//            {
//                //printf("LED2\n");
//                //LED点灯時間をセット（1秒）
//                timer = 100;
//
//                next_event_timer = 30;
//            }
//        }
//
//        if(timer > 0)
//        {
//
//
//            //printf("timer(%d)\n", timer);
//
//            g_ioport.p_api->pinWrite(LED1_PIN, IOPORT_LEVEL_HIGH);
//            timer--;
//        }
//        else
//        {
//
//            g_ioport.p_api->pinWrite(LED1_PIN, IOPORT_LEVEL_LOW);
//
//        }
//
//        if(next_event_timer > 0 && timer == 0)
//        {
//            //printf("next_event_timer(%d)\n", next_event_timer);
//
//
//            next_event_timer--;
//            if(next_event_timer == 0)
//            {
//                //printf("next_event_timer(%d)\n", next_event_timer);
//                tx_event_flags_set(&Event_Flags_Threads_LED, Thread_FLAG_2, TX_OR);
//            }
//        }

    }
}
