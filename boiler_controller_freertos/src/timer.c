/**
 * \brief Timing abstraction implementation.
 * 
 * \date 2021/08/07
 * 
 * \addtogroup timer
 * \{
 */

#include "../inc/timer.h"

struct timespec sys_time;

void timer_init(void) {

	/* Get the current system time */
    clock_gettime(CLOCK_MONOTONIC, &sys_time);
    
    /* Set an application initial start point 1 second ahead */
    sys_time.tv_sec+=2;

    /* Call for sleep function */
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &sys_time, NULL);
}

//void timer_get_time(void) {
//
//    /* Get the current system time */
//    clock_gettime(CLOCK_MONOTONIC, &sys_time);
//}


void timer_delay(long delay_ns) {

    struct timespec time; 
    clock_gettime(CLOCK_MONOTONIC, &time); 

    /* Calculate wake up time */
    time.tv_nsec += delay_ns;

    /* Convert wake up time to the system time structure */
    while(time.tv_nsec >= NSEC_PER_SEC) {
		time.tv_nsec -= NSEC_PER_SEC;
		time.tv_sec++;
    }
	
	/* Call for sleep function */
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time, NULL);
}

/** \} End of timer group */