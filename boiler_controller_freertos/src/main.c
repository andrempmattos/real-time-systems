/**
 * \brief Main loop implementation.
 * 
 * \date 2021/08/07
 * 
 * \addtogroup main
 * \{
 */

#include <FreeRTOS.h>
#include <task.h>

#include "../inc/udp_client.h"
#include "../inc/user_interface.h"
#include "../inc/tasks.h"
#include "../inc/console.h"

void system_init(void) {

	/* Console initialization */
	console_init();

	/* UDP interface initialization */
	udp_init(SERVER_ADDRESS, SERVER_PORT);

	/* User interface initialization */
	user_interface_init();
}

int main(void) {
	
	/* Critical system initialization */
	system_init();

	/* Create the system tasks */
	create_tasks();

	/* Start operating system scheduler */
	vTaskStartScheduler();

	/* Execution termination (it should never reach this point) */
    return 0;
}

/** \} End of main group */