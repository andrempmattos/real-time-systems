/**
 * \brief Logger implementation.
 * 
 * \date 2021/08/09
 * 
 * \addtogroup logger
 * \{
 */

#include <stdio.h>

#include "../inc/logger.h"

void logger_init(void) {

    /* Create file with name report (overwrite previous). */
    //FILE *report = fopen("report/report.txt", "w");
    //fclose(report);
}

void logger_add_entry(char *entry, int entry_size) {

}

int logger_save_file(void) {

    /* Create file pointer. */
    //FILE *report = fopen("report/report.txt", "a");

    /* Check if everything is ok. */
    //if(!report) {
    //    printf("File opening failed!\n");
    //    return -1;
    //}

    /* Write the report file with the log buffer */
    //fprintf(report, "%s", log_buffer);

    //fclose(report);
    return 0;
}



/** \} End of logger group */