#include "SerialOutput_thread.h"
#include "blinky_thread.h"
#include <stdio.h>
void check_alive_threads(int alive_num);

//static char tx_buf[64] = {0,};
int err = 0;
ssp_err_t send_serial_msg(char *msg)
{
    char tx_buf[64] = {0,};
    ssp_err_t   status;
    int max_len = 64;
    int msg_len = 64;

    tx_mutex_get(&g_new_mutex0, TX_WAIT_FOREVER);

    sprintf(tx_buf, "%.*s", sizeof(tx_buf) - 1, msg);
   //メッセージ内の文字列のサイズを調べる
   for (int i = 0; i < max_len; i++)
   {
       if(tx_buf[i] == '\0')
       {
           msg_len = i;
           break;
       }
   }
    status = g_uart0.p_api->write(g_uart0.p_ctrl, (uint8_t*)tx_buf, msg_len);
    //wait until uart transmission is complete
    status = tx_semaphore_get(&g_new_semaphore0, TX_WAIT_FOREVER);

    //status = tx_semaphore_put(&g_new_semaphore0);
    //tx_thread_sleep (1);
    if (TX_SUCCESS != status)
    {
        err++;
    }
    //tx_thread_sleep(1);
    tx_mutex_put(&g_new_mutex0);
    return status;
}

ssp_err_t send_serial_num(ULONG num)
{
    ssp_err_t   status;
    char temp_buf[64];
    int max_len = 64;
    int msg_len = 64;

    tx_mutex_get(&g_new_mutex0, TX_WAIT_FOREVER);

    ULONG sec = num / TX_TIMER_TICKS_PER_SECOND;
    ULONG msec = (num % TX_TIMER_TICKS_PER_SECOND) * 1000 / TX_TIMER_TICKS_PER_SECOND;


    snprintf(temp_buf, sizeof(temp_buf), "%lu.%03lu \r\n", sec, msec);
    //メッセージ内の文字列のサイズを調べる
   for (int i = 0; i < max_len; i++)
   {
       if(temp_buf[i] == '\0')
       {
           msg_len = i;
           break;
       }
   }
    status = g_uart0.p_api->write(g_uart0.p_ctrl, (uint8_t*)temp_buf, msg_len);
    status = tx_semaphore_get(&g_new_semaphore0, TX_WAIT_FOREVER);

    if (TX_SUCCESS != status)
    {
        err++;
    }
    tx_mutex_put(&g_new_mutex0);
    //tx_thread_sleep(1);

    return status;
}

//ssp_err_t send_serial_msg(char *msg)
//{
//    char tx_buf[64] = {0,};
//    UINT    err_g_queue_0;
//    sprintf(tx_buf, "%.*s", sizeof(tx_buf) - 1, msg);
//    err_g_queue_0 = tx_queue_send(&SerialOutput, tx_buf, TX_NO_WAIT);
//    return err_g_queue_0;
//}

//ssp_err_t send_serial_num(ULONG num)
//{
//    UINT err_g_queue_num;
//
//    char temp_buf[64];
//    ULONG sec = num / TX_TIMER_TICKS_PER_SECOND;
//    ULONG msec = (num % TX_TIMER_TICKS_PER_SECOND) * 1000 / TX_TIMER_TICKS_PER_SECOND;
//
//    snprintf(temp_buf, sizeof(temp_buf), "%lu.%03lu \r\n", sec, msec);
//
//
//    err_g_queue_num = tx_queue_send(&SerialOutput, temp_buf, TX_NO_WAIT);
//    return err_g_queue_num;
//}
void uart_callback_function (uart_callback_args_t * p_args);



void uart_callback_function (uart_callback_args_t * p_args)

{

    static bool error = false;



    if (UART_EVENT_TX_COMPLETE == p_args->event)

    {

        tx_semaphore_ceiling_put(&g_new_semaphore0, 1);

    }

    else if (UART_EVENT_RX_COMPLETE == p_args->event)

    {

        /* The receive can only complete when the transmit has completed */

        error = true;

    }

    else if(UART_EVENT_TX_DATA_EMPTY == p_args->event)

    {



    }

    else if(UART_EVENT_RX_CHAR == p_args->event)

    {

    }

    else

    {

        error = true;

    }

}



/* SerialOutput_thread entry function */
void SerialOutput_thread_entry(void)
{
    /* TODO: add your own code here */

    while (1)
    {
        tx_thread_sleep(1);
    }

//    while (1)
//    {
//        //tx_thread_sleep (1);
//
//       ssp_err_t   status;
//
//       UINT    err_g_queue_0;
//       char    rx_buf[64];
//       int max_len = 64;
//       int msg_len = 64;
//       int err_count = 0;
//
//
//
//       // キューからメッセージを受け取る
//       err_g_queue_0 = tx_queue_receive (&SerialOutput, rx_buf, TX_NO_WAIT);
//       if (TX_SUCCESS == err_g_queue_0)
//       {
//           //メッセージ内の文字列のサイズを調べる
//           for (int i = 0; i < max_len; i++)
//           {
//               if(rx_buf[i] == '\0')
//               {
//                   msg_len = i;
//                   break;
//               }
//           }
//
//           //調べたサイズの文字列をシリアルI/Fで送信する
//           //msg_len = snprintf(msg, sizeof(msg), "%s\r\n", rx_buf);
//           status = g_uart0.p_api->write(g_uart0.p_ctrl, (uint8_t*)rx_buf, msg_len);
//
//           tx_thread_sleep (1);
//           if (TX_SUCCESS != status) err_count++;
//       }
//       check_alive_threads(14);
//       tx_thread_sleep (1);
//    }
}
