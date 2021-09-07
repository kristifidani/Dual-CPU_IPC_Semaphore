/******************************************************************************
 Description:
  Auxiliary header with constants and structures for the IPC.
*******************************************************************************/

#ifndef IPC_DEF_H
#define IPC_DEF_H

    /* Enable/Disable the usage of IPC Semaphore */
    #define ENABLE_SEMA             1u

    /* Semaphore number to be used in this example. Semaphores 0-15 are reserved
       for system use. */
    #define SEMA_NUM                16u

#endif /* IPC_DEF_H */