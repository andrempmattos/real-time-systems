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
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "logger.h"

char log_buffer[FILE_BUFFER_SIZE];

void logger_init(void) {

    /* Create file with name report (overwrite previous). */
    FILE *report = fopen("report/report.txt", "w");
    fclose(report);
}

void logger_add_entry(char *entry, int entry_size, bool add_spacer) {

    int size = 0;
    char buffer[100];
    struct timespec time;
    
    /* Get the current system time */
    clock_gettime(CLOCK_MONOTONIC, &time);

    size = sprintf(buffer, "[%ld:%ld]: ", time.tv_sec, time.tv_nsec);
    strcat(buffer, entry);
    strcat(buffer, "\n");
    strcat(log_buffer, buffer);

    if (add_spacer == true)
    {
        strcat(log_buffer, "\n");
    }
}

int logger_save_file(void) {

    /* Create file pointer. */
    FILE *report = fopen("report/report.txt", "a");

    /* Check if everything is ok. */
    if (!report) {
        printf("File opening failed!\n");
        return -1;
    }

    /* Write the report file with the log buffer */
    fprintf(report, "%s", log_buffer);

    /* Clear array */
    memset(log_buffer, 0, FILE_BUFFER_SIZE);

    fclose(report);
    return 0;
}



/** \} End of logger group */