#include "irq_thread.h"
#include "blinky_thread.h"
#include "event_define.h"
#include <stdio.h>
extern  ssp_err_t send_serial_msg(char *msg);
extern  ssp_err_t send_serial_num(ULONG num);
void check_alive_threads(int alive_num);
//extern void initialise_monitor_handles(void); // for printf()

int     count = 0;
char tx_buf[64];
void irq_handler_0(external_irq_callback_args_t *p_args)
{

    tx_event_flags_set(&irq_Event_Flags, irq_FLAG, TX_OR);

}


/* irq_thread entry function */
void irq_thread_entry(void)
{
    //initialise_monitor_handles(); // for printf()
    int     err_count = 0;
    ssp_err_t   status;
    ULONG actual_events;
    ULONG first_time = 0;
    int first = 1;

    status = Irq_handler_0.p_api->open(Irq_handler_0.p_ctrl, Irq_handler_0.p_cfg);
    if (SSP_SUCCESS != status) err_count++;
    status = Irq_handler_0.p_api->enable(Irq_handler_0.p_ctrl);
    if (SSP_SUCCESS != status) err_count++;

    //printf("1\n");


    /* TODO: add your own code here */
    while (1)
    {
        //printf("%i\n", count);
        //printf("2\n");
        actual_events = 0;

//        sprintf(tx_buf, "[%lu] Messages", tx_time_get());
//        send_serial_msg(tx_buf);
//        tx_thread_sleep (1);
        status = tx_event_flags_get(&irq_Event_Flags,
                                        irq_FLAG | watchdog_FLAG_irq_13,
                                        TX_OR,
                                        &actual_events,
                                        TX_WAIT_FOREVER);
        //printf("3\n");
        ULONG   current_time = tx_time_get();

        if(TX_SUCCESS == status)
        {
            if (actual_events & watchdog_FLAG_irq_13)
            {
                check_alive_threads(2);
                tx_event_flags_set(&irq_Event_Flags, ~watchdog_FLAG_irq_13, TX_AND);
            }

            if (actual_events & irq_FLAG)
            {
                if(first)
                {
                    first_time = current_time;
                    first = 0;
                }
                else
                {
                    ULONG num = current_time -  first_time;
                    //ULONG sec = num / TX_TIMER_TICKS_PER_SECOND;
                    //ULONG msec = (num % TX_TIMER_TICKS_PER_SECOND) * 1000 / TX_TIMER_TICKS_PER_SECOND;

                    //char msg_buf[64];
                    //snprintf(msg_buf, sizeof(msg_buf), "Time: %lu.%03lu \r\n", sec, msec);
                    send_serial_num(num);
                    first_time = current_time;
                }


                send_serial_msg("test_irq\r\n");
                tx_event_flags_set(&irq_Event_Flags, ~irq_FLAG, TX_AND);
            }
        }
        if (TX_SUCCESS != status)
        {
            send_serial_msg("Error-irq !!\r\n");
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
//            check_alive_threads(2);
//        }

        tx_thread_sleep (1);

    }
}
