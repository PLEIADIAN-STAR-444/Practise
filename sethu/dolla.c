#include "nosipho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void replace_variables(char **arguments, int status) {
    int i = 0;

    while (arguments[i] != NULL) {
        if (strcmp(arguments[i], "$?") == 0) {
            char status_str[10];
            sprintf(status_str, "%d", status);
            arguments[i] = strdup(status_str);
        } else if (strcmp(arguments[i], "$$") == 0) {
            char pid_str[10];
            sprintf(pid_str, "%d", getpid());
            arguments[i] = strdup(pid_str);
        }

        i++;
    }
}

