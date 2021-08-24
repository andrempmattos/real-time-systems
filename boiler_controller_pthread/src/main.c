/**
 * \brief Main loop implementation.
 * 
 * \date 2021/08/07
 * 
 * \addtogroup main
 * \{
 */

#include <stdio.h>
#include <pthread.h>

#include "udp_client.h"
#include "timer.h"
#include "user_interface.h"
#include "threads.h"

void system_init(void) {

	/* UDP interface initialization */
	udp_init(SERVER_ADDRESS, SERVER_PORT);

	/* User interface initialization */
	user_interface_init();

	/* Timer initialization */
	timer_init();

	/* Threads initialization */
	threads_init();

	/* Wait until user thread terminate */
	pthread_join(thread_user_input_handler, NULL);
}

void main(void) {
	
	/* Critical system initialization */
	system_init();

	printf(ANSI_COLOR_RED "\nProgram terminated due to user input (exit code 0)!\n\n" ANSI_COLOR_RESET);

	/* Only achieve here if user explicitily call a system termination procedure */
    exit(0);
}

/** \} End of main group */