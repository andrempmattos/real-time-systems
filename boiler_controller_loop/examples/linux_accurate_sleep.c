#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define NSEC_PER_SEC    (1000000000) /* The number of nsecs per sec. */

int main(int argc, char* argv[])
{
        struct timespec t;
        int interval = 50000; /* 50us*/

        clock_gettime(CLOCK_MONOTONIC ,&t);
        /* start after one second */
        t.tv_sec++;

        while(1) {
                /* wait until next shot */
                clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

                /* do the stuff */

                /* calculate next shot */
                t.tv_nsec += interval;

                while (t.tv_nsec >= NSEC_PER_SEC) {
                       t.tv_nsec -= NSEC_PER_SEC;
                        t.tv_sec++;
                }
   }
}



