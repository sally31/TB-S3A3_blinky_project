/* generated thread header file - do not edit */
#ifndef SERIALOUTPUT_THREAD_H_
#define SERIALOUTPUT_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void SerialOutput_thread_entry(void);
                #else
extern void SerialOutput_thread_entry(void);
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern TX_QUEUE SerialOutput;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* SERIALOUTPUT_THREAD_H_ */
