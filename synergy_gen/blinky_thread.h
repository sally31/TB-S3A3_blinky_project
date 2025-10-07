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
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* BLINKY_THREAD_H_ */
