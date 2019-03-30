#include <stdio.h>

void logger(char* log_level, char* msg) {
    printf("[%s] %s\n", log_level, msg);
}
