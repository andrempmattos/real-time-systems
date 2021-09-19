/**
 * \brief Hooks implementation.
 * 
 * \date 2021/09/18
 * 
 * \addtogroup hooks
 * \{
 */

#include <FreeRTOS.h>
#include <task.h>

void vApplicationMallocFailedHook(void)
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient free memory available in the */
    /* FreeRTOS heap. pvPortMalloc() is called internally by FreeRTOS API functions that create tasks, queues */
    /* or semaphores */
    taskDISABLE_INTERRUPTS();

    while(1);
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void)pxTask;
    (void)pcTaskName;

    /* Run time stack overflow checking is performed if configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or */
    /* 2. This hook function is called if a stack overflow is detected */
    taskDISABLE_INTERRUPTS();

    while(1);
}

/** \} End of hooks group */