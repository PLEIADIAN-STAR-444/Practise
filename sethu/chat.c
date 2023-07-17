#include "nosipho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_comments(char *command) {
    // Find the first occurrence of '#' in the command
    char *comment_start = strchr(command, '#');

    if (comment_start != NULL) {
        // Replace '#' with a null character to truncate the command
        *comment_start = '\0';
    }
}

