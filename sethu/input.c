#include "nosipho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_file_input(char *filename, char **envp) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("File open failed");
        return;
    }

    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

        if (line[0] != '\0') {
            handle_command(line, envp);
        }
    }

    fclose(file);
}

