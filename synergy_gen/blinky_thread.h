/* generated thread header file - do not edit */
#ifndef BLINKY_THREAD_H_
#define BLINKY_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void blinky_thread_entry(void);
                #else
extern void blinky_thread_entry(void);
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern TX_QUEUE g_new_queue0;
extern TX_QUEUE g_new_queue2;
extern TX_MUTEX g_new_mutex0;
extern TX_EVENT_FLAGS_GROUP g_new_event_flags0;
extern TX_EVENT_FLAGS_GROUP Event_Flags_Threads_LED;
extern TX_EVENT_FLAGS_GROUP irq_Event_Flags;
extern TX_SEMAPHORE g_new_semaphore0;
extern TX_EVENT_FLAGS_GROUP watchdog_Event_Flags;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* BLINKY_THREAD_H_ */
