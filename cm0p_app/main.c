/******************************************************************************
Description: This is the source code for CM0+ in the the Dual CPU Empty
              Application for ModusToolbox.
*******************************************************************************/

#include "cy_pdl.h"
#include "ipc_def.h"

#include <stdlib.h> 

#if defined (TARGET_CYSBSYSKIT_DEV_01)
#define UART_RES        SCB10
#else
#define UART_RES        SCB5
#endif
#define BTN_RES_PORT    GPIO_PRT0
#define BTN_RES_PIN     4

int main(void)
{
    /* Enable global interrupts */
    __enable_irq();

    /* Lock the sempahore to wait for CM4 to be init */
    Cy_IPC_Sema_Set(SEMA_NUM, false);

    /* Enable CM4. CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);

    /* Wait till CM4 unlocks the semaphore */
    do
    {
        __WFE();
    } 
    while (Cy_IPC_Sema_Status(SEMA_NUM) == CY_IPC_SEMA_STATUS_LOCKED);
    
    /* Update clock settings */
    SystemCoreClockUpdate();

    for (;;)
    {
        /* Check if the button is pressed */
        if (Cy_GPIO_Read(BTN_RES_PORT, BTN_RES_PIN) == 0)
        {        
        #if ENABLE_SEMA
            if (Cy_IPC_Sema_Set(SEMA_NUM, false) == CY_IPC_SEMA_SUCCESS)
        #endif        
            {
                /* Print a message to the console */
                Cy_SCB_UART_PutString(UART_RES, "Message sent from CM0+\r\n");

            #if ENABLE_SEMA    
                while (CY_IPC_SEMA_SUCCESS != Cy_IPC_Sema_Clear(SEMA_NUM, false));
            #endif
            }
        }    
    }
}
