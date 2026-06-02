/* generated thread source file - do not edit */
#include "SerialOutput_thread.h"

TX_THREAD SerialOutput_thread;
void SerialOutput_thread_create(void);
static void SerialOutput_thread_func(ULONG thread_input);
static uint8_t SerialOutput_thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.SerialOutput_thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE SerialOutput;
static uint8_t queue_memory_SerialOutput[1024];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void SerialOutput_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_SerialOutput;
    err_SerialOutput = tx_queue_create (&SerialOutput, (CHAR*) "SerialOutput", 16, &queue_memory_SerialOutput,
                                        sizeof(queue_memory_SerialOutput));
    if (TX_SUCCESS != err_SerialOutput)
    {
        tx_startup_err_callback (&SerialOutput, 0);
    }

    UINT err;
    err = tx_thread_create (&SerialOutput_thread, (CHAR*) "SerialOutput_thread", SerialOutput_thread_func, (ULONG) NULL,
                            &SerialOutput_thread_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&SerialOutput_thread, 0);
    }
}

static void SerialOutput_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    SerialOutput_thread_entry ();
}
