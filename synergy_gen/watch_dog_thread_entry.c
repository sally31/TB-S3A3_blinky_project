#include "watch_dog_thread.h"
#include "blinky_thread.h"
#include "event_define.h"
#include <stdio.h>
//extern void initialise_monitor_handles(void); // for printf()
extern  ssp_err_t send_serial_msg(char *msg);
extern  ssp_err_t send_serial_num(ULONG num);
#define total_threads  15

int count_threads_alive[total_threads] = {0};
int     err_count = 0;


void check_alive_threads();
void kick_watchdog();

/* watch_dog_thread entry function */
void watch_dog_thread_entry(void)
{
    //initialise_monitor_handles();

    ssp_err_t   status;
    status = g_wdt0.p_api->open(g_wdt0.p_ctrl, g_wdt0.p_cfg);
    if(status != SSP_SUCCESS) err_count++;

    /* TODO: add your own code here */
    send_serial_msg("ONE\r\n");
    while (1)
    {
        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_1 | watchdog_FLAG_2 | watchdog_FLAG_3
                            | watchdog_FLAG_4 | watchdog_FLAG_5 | watchdog_FLAG_6 | watchdog_FLAG_7
                             | watchdog_FLAG_8 | watchdog_FLAG_9 | watchdog_FLAG_10, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_2, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_3, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_4, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_5, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_6, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_7, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_8, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_9, TX_OR);
//        tx_event_flags_set(&Event_Flags_Threads_LED, watchdog_FLAG_10, TX_OR);
        tx_event_flags_set(&watchdog_Event_Flags, watchdog_FLAG_blinky_11 | watchdog_FLAG_buttom_12, TX_OR);
        //tx_event_flags_set(&watchdog_Event_Flags, watchdog_FLAG_buttom_12, TX_OR);

        tx_event_flags_set(&g_new_event_flags0, watchdog_FLAG_threads0_14 | watchdog_FLAG_threads2_15, TX_OR);
        //tx_event_flags_set(&g_new_event_flags0, watchdog_FLAG_threads2_15, TX_OR);

        tx_event_flags_set(&irq_Event_Flags, watchdog_FLAG_irq_13, TX_OR);

        //send_serial_msg("TWO\r\n");
        tx_thread_sleep (400);

        //send_serial_msg("THREE\r\n");
        kick_watchdog();
        send_serial_msg("finish-kickdog\r\n");

    }
}

void kick_watchdog(void)
{
     // for printf()
    ssp_err_t   status;
    int count = 0;
    //全部のスレッズ16個がyesっていったら
    //watch dogとhal_entry.c以外
    char buf[64];
    for(int i = 0; i < total_threads; i++)
    {
        sprintf(buf, "Thread[%d] = %d\r\n", i, count_threads_alive[i]);
        //send_serial_msg(buf);
        if (count_threads_alive[i] == 1)
        {
            count++;
        }

    }

    if(count == total_threads)
    {
        status = g_wdt0.p_api->refresh(g_wdt0.p_ctrl);
        send_serial_msg("kick-dog\r\n");
        if(status != SSP_SUCCESS) err_count++;

        for(int i = 0; i < total_threads; i++)
        {
            count_threads_alive[i] = 0;
        }
    }
    else
    {
        //リセットする
        send_serial_msg("reset\r\n");
    }


}

void check_alive_threads(int alive_num)
{
    //全員が生きてるかカウントする
    if(alive_num < total_threads)
    {
        count_threads_alive[alive_num] = 1;
    }
}
