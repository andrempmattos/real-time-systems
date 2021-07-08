/**
 * \brief Timing abstraction implementation.
 * 
 * \date 2021/08/07
 * 
 * \addtogroup timer
 * \{
 */

#include "timer.h"

struct timespec sys_time;

void timer_init(void) {

	/* Get the current system time */
    clock_gettime(CLOCK_MONOTONIC, &sys_time);
    
    /* Set an application initial start point 1 second ahead */
    sys_time.tv_sec++;

    /* Call for sleep function */
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &sys_time, NULL);
}


void timer_delay(long delay_ns) {	 

    /* Calculate wake up time */
    sys_time.tv_nsec += delay_ns;

    /* Convert wake up time to the system time structure */
    while(sys_time.tv_nsec >= NSEC_PER_SEC) {
		sys_time.tv_nsec -= NSEC_PER_SEC;
		sys_time.tv_sec++;
    }
	
	/* Call for sleep function */
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &sys_time, NULL);
}

/** \} End of timer group */