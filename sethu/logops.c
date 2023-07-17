#include "nosipho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_logical_operators(char **commands, char **envp) {
    int i = 0;
    int command_count = 0;
    int status = 1;

    // Count the number of commands
    while (commands[i] != NULL) {
        command_count++;
        i++;
    }

    i = 0;

    while (i < command_count) {
        char *command = trim_whitespace(commands[i]);

        // Split the command into command and arguments
        char *arguments[10];
        int j = 0;
        char *token;

        token = strtok(command, " ");
        while (token != NULL) {
            arguments[j] = token;
            j++;
            token = strtok(NULL, " ");
        }
        arguments[j] = NULL;

        if (strcmp(arguments[0], "exit") == 0) {
            handle_exit(arguments);
            return;
        }

        if (strcmp(arguments[0], "cd") == 0) {
            change_directory(arguments);
            i++;
            continue;
        }

        if (access(arguments[0], X_OK) == 0) {
            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
                return;
            }

            if (pid == 0) {
                if (execve(arguments[0], arguments, envp) == -1) {
                    perror("execve");
                }
                exit(EXIT_FAILURE);
            } else {
                wait(&status);
            }
        } else {
            printf("Command not found: %s\n", arguments[0]);
        }

        if (status != 0 && strcmp(commands[i + 1], "&&") == 0) {
            // Skip the next command if the previous command failed
            i += 2;
        } else if (status == 0 && strcmp(commands[i + 1], "||") == 0) {
            // Skip the next command if the previous command succeeded
            i += 2;
        } else {
            i++;
        }
    }
}

char *trim_whitespace(char *str) {
    // Remove leading whitespace
    while (*str == ' ' || *str == '\t' || *str == '\n') {
        str++;
    }

    if (*str == '\0') {
        return str;
    }

    // Remove trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n')) {
        end--;
    }
    *(end + 1) = '\0';

    return str;
}

