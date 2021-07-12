/**
 * \brief Logger implementation.
 * 
 * \date 2021/08/09
 * 
 * \addtogroup logger
 * \{
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "logger.h"

#define NSEC_PER_SEC    1000000000         /* The number of nanoseconds per second. */

long response_time_ns[FILE_BUFFER_SIZE];
long last_cycle_s;
long last_cycle_ns;

int buffer_index = 0;

void logger_set_entry(void) {

    struct timespec time;
    
    /* Get the current system time */
    clock_gettime(CLOCK_MONOTONIC, &time);

    last_cycle_s = (long)time.tv_sec; 
    last_cycle_ns = (long)time.tv_nsec;
}

void logger_get_entry(void) {
    
    struct timespec time;
    
    /* Get the current system time */
    clock_gettime(CLOCK_MONOTONIC, &time);

    response_time_ns[buffer_index] = (((long)time.tv_sec - last_cycle_s) * NSEC_PER_SEC) + ((long)time.tv_nsec - last_cycle_ns);

    /* Update variables for the next cycle */ 
    if((++buffer_index) >= FILE_BUFFER_SIZE) {
        /* Maximum buffer size achieved */
        buffer_index = 0;
    }
}

int logger_save_file(void) {

    printf("\nStarting log file session!\n");

    /* Create file pointer. */
    FILE *report = fopen("report/report.csv", "a");

    /* Check if everything is ok. */
    if (!report) {
        printf("File opening failed!\n");
        return -1;
    }

    /* Write the report file with the log buffer */
    for (int i = 0; i < FILE_BUFFER_SIZE; i++) {
        fprintf(report, "%f\n", (float)(response_time_ns[i]));
    }
    
    printf("Log file saved!\n\n");

    fclose(report);
    return 0;
}



/** \} End of logger group */