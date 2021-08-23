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

	/* Timer initialization */
	timer_init();

	/* User interface initialization */
	user_interface_init();

	/* Threads initialization */
	threads_init();

	/* Mutex initialization */
	mutex_init();

	/* Wait until user thread terminate */
	pthread_join(thread_user_input_handler, NULL);
}

void main(void) {
	
	/* System initialization */
	system_init();

	/* Only achieve here if user explicitily call a system termination procedure */
    exit(0);
}

/** \} End of main group */