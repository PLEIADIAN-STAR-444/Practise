#include "nosipho.h"

int main(void) {
    char line[BUFFER_SIZE];

    while (1) {
        printf("$ ");
        fgets(line, BUFFER_SIZE, stdin);

        // Remove newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0) {
            break;
        }

        handle_command(line, NULL);
    }

    return 0;
}

