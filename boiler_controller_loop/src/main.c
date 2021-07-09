/**
 * \brief Main loop implementation.
 * 
 * \date 2021/08/07
 * 
 * \addtogroup main
 * \{
 */

#include <stdio.h>

#include "controller.h"
#include "udp_client.h"
#include "timer.h"

int main(int argc, char const *argv[]) {
	
	int cycle = 0;
	char buffer[MAX_BUFFER_SIZE];
	int received_size = 0;

	/* Boiler controller initialization */
	controller_init();

	/* UDP interface initialization */
	udp_init(SERVER_ADDRESS, SERVER_PORT);

	/* Timer initialization */
	timer_init();

	/* Main loop (cyclic executive) */
	while(1) {
		
		printf("Loop cycle! \t %d \n", cycle++);

		/********* Do stuff */
		send_message("st-0");
		received_size = receive_message(buffer);
		
		if (received_size > 0) {
			buffer[received_size] = '\0';
			printf("Received message of %d bytes >>> %s\n\n", received_size, buffer);
		}
		else {
			printf("Receive message failed!\n\n");
		}
		/********* Finished stuff */

		/* Delay until next system loop cycle (system tick) */
		timer_delay(SYS_TICK);
	}
}

/** \} End of main group */