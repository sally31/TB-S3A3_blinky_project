#include "buttom_thread.h"
#include "blinky_thread.h"
#include "event_define.h"
#include <stdio.h>
void check_alive_threads(int alive_num);
//extern void initialise_monitor_handles(void); // for printf
extern  ssp_err_t send_serial_msg(char *msg);

/* buttom_thread entry function */
void buttom_thread_entry(void)
{
    ULONG actual_events;
    ssp_err_t   status;
    //initialise_monitor_handles(); // for printf()
    uint32_t    active_time = 0;
    /* TODO: add your own code here */
    while (1)
    {
        actual_events = 0;
        ioport_level_t pin_value;
        g_ioport.p_api->pinRead(SWITCH_S1_PIN, &pin_value);

        // スイッチの押下時間を測定
        if(pin_value == IOPORT_LEVEL_LOW)  // Active Low
        {
            active_time++;
            //printf("%lu\n", active_time);
        }
        else
        {
            // 長押し判定
            if(active_time > 300)  // 100 * 10ms Long push
            {
                tx_event_flags_set(&g_new_event_flags0, EVENT_FLAG_2, TX_OR);
            }
            else if(active_time > 2)  // 2 * 10ms Short push
            {
                tx_event_flags_set(&Event_Flags_Threads_LED, Thread_FLAG_1, TX_OR);
            }
            active_time = 0;
        }
        status = tx_event_flags_get(&watchdog_Event_Flags,
                                    watchdog_FLAG_buttom_12,
                                            TX_AND,
                                            &actual_events,
                                            //TX_WAIT_FOREVER
                                            TX_NO_WAIT);

        if (status == TX_SUCCESS)
        {
            check_alive_threads(1);
            tx_event_flags_set(&watchdog_Event_Flags, ~watchdog_FLAG_buttom_12, TX_AND);
        }

        tx_thread_sleep (1);
    }
}
