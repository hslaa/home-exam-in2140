#include <stdio.h>
#include <string.h>
#include <time.h>

/*
 *
 * Heavily inspired by the logging program provided by the Plenary Sessions instructors.
 *
 * (https://github.uio.no/IN2140/PlenarySessions/blob/master/tips_and_tricks/logging/colors.c)
 */

#define CNRM "\x1b[0m"
#define CMAG "\x1b[35m"
#define CYEL "\x1b[33m"

#define LOGGER_LEVEL_DEBUG 2
#define LOGGER_LEVEL_INFO 1
#define LOGGER_LEVEL_OFF 0

#define LOGGER_DEBUG "DEBUG"
#define LOGGER_INFO "INFO"
#define LOGGER_OUT "OUT"

int logger_level = LOGGER_LEVEL_DEBUG;

void logger(char* type, char* msg) {
    if ((strcmp(type, LOGGER_DEBUG) == 0 && logger_level > 1) ||
        (strcmp(type, LOGGER_INFO) == 0 && logger_level > 0) ||
        (strcmp(type, LOGGER_OUT) == 0)) {
            
        char* color;
        if (strcmp(type, LOGGER_DEBUG) == 0) {
            color = CMAG;
        } else if (strcmp(type, LOGGER_INFO) == 0) {
            color = CYEL;
        } else {
            color = CNRM;
        }


        time_t rawtime;
        struct tm* timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        char* datetime = asctime(timeinfo);
        datetime[strlen(datetime) - 6] = 0;
        datetime = &datetime[strlen(datetime) - 8];
        printf("[%s][%s%-5s%s] %s\n", datetime, color, type, CNRM, msg);
    }
}
