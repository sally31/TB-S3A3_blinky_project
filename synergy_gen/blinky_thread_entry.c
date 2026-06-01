/***********************************************************************************************************************
* File Name    : blinky_thread_entry.c
* Description  : This is a very simple example application that blinks all the LEDs on a board.
***********************************************************************************************************************/
#include <stdio.h>
#include "blinky_thread.h"
#include "event_define.h"

void check_alive_threads(int alive_num);
extern void initialise_monitor_handles(void); // for printf()
void event_setter_thread_entry(void);
extern  ssp_err_t send_serial_msg(char *msg);

TX_EVENT_FLAGS_GROUP my_event_flags_group;

ssp_err_t   status;
//int  msg_len = 0;
//char msg[50];


/*******************************************************************************************************************//**
 * @brief  Blinky example application
 *
 * Blinks all leds at a rate of 1 second using the the threadx sleep function.
 * Only references two other modules including the BSP, IOPORT.
 *
 **********************************************************************************************************************/
void blinky_thread_entry(void)
{
    initialise_monitor_handles(); // for printf()

    /* Define the units to be used with the threadx sleep function */
	const uint32_t threadx_tick_rate_Hz = 100;
    /* Set the blink frequency (must be <= threadx_tick_rate_Hz */
    const uint32_t freq_in_hz = 10;
    /* Calculate the delay in terms of the threadx tick rate */
    const uint32_t delay = threadx_tick_rate_Hz/freq_in_hz;
    /* LED type structure */
    bsp_leds_t leds;
    /* LED state variable */
    ioport_level_t level = IOPORT_LEVEL_HIGH;

    /* Get LED information for this board */
    R_BSP_LedsGet(&leds);

    //tx_event_flags_create(&my_event_flags_group, "MY EVENT FLAGS");
    /* If this board has no leds then trap here */
    if (0 == leds.led_count)
    {
        while(1);   // There are no leds on this board
    }


    status = g_uart0.p_api->open(g_uart0.p_ctrl, g_uart0.p_cfg);
    if (status != SSP_SUCCESS)
    {
        __BKPT(0);  // Halt for debugging if UART init fails
    }

    ULONG actual_events;

    send_serial_msg("SerialTest-1\r\n");

    if (TX_SUCCESS != status)
    {
        send_serial_msg("Error-2 !!\r\n");
    }

    //int count_time = 0;

    while (1)
    {
//        UINT    err_g_queue_0;
//        UINT    err_g_queue_2;
//        char    rx_buf[4];

        tx_thread_sleep(300);
        event_setter_thread_entry();
        status = tx_event_flags_get(&watchdog_Event_Flags,
                                    watchdog_FLAG_blinky_11,
                                            TX_AND,
                                            &actual_events,
                                            TX_NO_WAIT);

        if (status == TX_SUCCESS)
        {
            check_alive_threads(0);
            tx_event_flags_set(&watchdog_Event_Flags, ~watchdog_FLAG_blinky_11, TX_AND);
        }

        tx_thread_sleep(1);


    }
}

void event_setter_thread_entry(void)
{
    tx_event_flags_set(&g_new_event_flags0, EVENT_FLAG_1, TX_OR);

    //tx_event_flags_set(&g_new_event_flags0, EVENT_FLAG_2, TX_OR);

    //tx_event_flags_set(&Event_Flags_Threads_LED, Thread_FLAG_1, TX_OR);


}




