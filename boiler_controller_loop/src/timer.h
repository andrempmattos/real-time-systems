/**
 * \brief Timing abstraction definitions.
 * 
 * \date 2021/08/07
 * 
 * \defgroup timer Timer
 * \ingroup src
 * \{
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdlib.h>
#include <time.h>

#define NSEC_PER_SEC    1000000000 		   /**< The number of nanoseconds per second. */
#define SYS_TICK    	  30000000         /**< System tick time (30ms). */
#define TICKS_TO_1_SECOND       33         /**< Amount of ticks to complete a cycle of 1 second of duration. */

/**
 * \brief Timer abstraction initialization.
 */
void timer_init(void);

/**
 * \brief Timer delay/sleep function abstraction.
 *
 * \param[in] delay_ns is the time in nanoseconds to delay.
 */
void timer_delay(long delay_ns);

#endif /* TIMER_H_ */

/** \} End of timer group */