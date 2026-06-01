#include "new_thread1.h"

/* New Thread entry function */
void new_thread1_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
