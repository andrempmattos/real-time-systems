

#include "controller.h"
#include "timer.h"
#include "udp_client.h"

#include <stdio.h>


int main(int argc, char const *argv[]) {

	controller_init();

	udp_init();

	timer_init();


	while(1) {
	printf("running!\n");
		//return 0;
	}

}