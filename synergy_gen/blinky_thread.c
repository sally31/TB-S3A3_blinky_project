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
TX_QUEUE g_new_queue2;
static uint8_t queue_memory_g_new_queue2[20];
TX_MUTEX g_new_mutex0;
TX_EVENT_FLAGS_GROUP g_new_event_flags0;
TX_EVENT_FLAGS_GROUP Event_Flags_Threads_LED;
TX_EVENT_FLAGS_GROUP irq_Event_Flags;
TX_SEMAPHORE g_new_semaphore0;
TX_EVENT_FLAGS_GROUP watchdog_Event_Flags;
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
    UINT err_g_new_queue2;
    err_g_new_queue2 = tx_queue_create (&g_new_queue2, (CHAR*) "New Queue", 1, &queue_memory_g_new_queue2,
                                        sizeof(queue_memory_g_new_queue2));
    if (TX_SUCCESS != err_g_new_queue2)
    {
        tx_startup_err_callback (&g_new_queue2, 0);
    }
    UINT err_g_new_mutex0;
    err_g_new_mutex0 = tx_mutex_create (&g_new_mutex0, (CHAR*) "New Mutex", TX_NO_INHERIT);
    if (TX_SUCCESS != err_g_new_mutex0)
    {
        tx_startup_err_callback (&g_new_mutex0, 0);
    }
    UINT err_g_new_event_flags0;
    err_g_new_event_flags0 = tx_event_flags_create (&g_new_event_flags0, (CHAR*) "New Event Flags");
    if (TX_SUCCESS != err_g_new_event_flags0)
    {
        tx_startup_err_callback (&g_new_event_flags0, 0);
    }
    UINT err_Event_Flags_Threads_LED;
    err_Event_Flags_Threads_LED = tx_event_flags_create (&Event_Flags_Threads_LED, (CHAR*) "Event_Flags_Threads_LED");
    if (TX_SUCCESS != err_Event_Flags_Threads_LED)
    {
        tx_startup_err_callback (&Event_Flags_Threads_LED, 0);
    }
    UINT err_irq_Event_Flags;
    err_irq_Event_Flags = tx_event_flags_create (&irq_Event_Flags, (CHAR*) "irq_Event_Flags");
    if (TX_SUCCESS != err_irq_Event_Flags)
    {
        tx_startup_err_callback (&irq_Event_Flags, 0);
    }
    UINT err_g_new_semaphore0;
    err_g_new_semaphore0 = tx_semaphore_create (&g_new_semaphore0, (CHAR*) "New Semaphore", 0);
    if (TX_SUCCESS != err_g_new_semaphore0)
    {
        tx_startup_err_callback (&g_new_semaphore0, 0);
    }
    UINT err_watchdog_Event_Flags;
    err_watchdog_Event_Flags = tx_event_flags_create (&watchdog_Event_Flags, (CHAR*) "watchdog_Event_Flags");
    if (TX_SUCCESS != err_watchdog_Event_Flags)
    {
        tx_startup_err_callback (&watchdog_Event_Flags, 0);
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
