/* generated thread source file - do not edit */
#include "blinky_thread.h"

TX_THREAD blinky_thread;
void blinky_thread_create(void);
static void blinky_thread_func(ULONG thread_input);
static uint8_t blinky_thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.blinky_thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE g_new_queue0;
static uint8_t queue_memory_g_new_queue0[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void blinky_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_g_new_queue0;
    err_g_new_queue0 = tx_queue_create (&g_new_queue0, (CHAR*) "New Queue", 1, &queue_memory_g_new_queue0,
                                        sizeof(queue_memory_g_new_queue0));
    if (TX_SUCCESS != err_g_new_queue0)
    {
        tx_startup_err_callback (&g_new_queue0, 0);
    }

    UINT err;
    err = tx_thread_create (&blinky_thread, (CHAR*) "Blinky Thread", blinky_thread_func, (ULONG) NULL,
                            &blinky_thread_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&blinky_thread, 0);
    }
}

static void blinky_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    blinky_thread_entry ();
}
