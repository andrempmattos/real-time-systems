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

	/* Boiler controller initialization */
	controller_init();

	/* UDP interface initialization */
	udp_init();

	/* Timer initialization */
	timer_init();

	/* Main loop (cyclic executive) */
	while(1) {
		
		/* Do stuff */
		printf("running! \t %d \n", cycle++);
		
		/* Delay until next system loop cycle (system tick) */
		timer_delay(SYS_TICK);
	}
}

/** \} End of main group */