#include "nosipho.h"

void handle_command(char *command, char **envp) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        char **arguments = split_arguments(command);
        if (arguments[0] != NULL) {
            if (execve(arguments[0], arguments, envp) == -1) {
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }
        free_arguments(arguments);
        exit(EXIT_SUCCESS);
    } else if (pid < 0) {
        perror("Error");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

char **split_arguments(char *line) {
    int bufsize = BUFFER_SIZE, position = 0;
    char **arguments = malloc(bufsize * sizeof(char *));
    char *argument;

    if (!arguments) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    argument = strtok(line, " \t\n\r\a");
    while (argument != NULL) {
        arguments[position] = argument;
        position++;

        if (position >= bufsize) {
            bufsize += BUFFER_SIZE;
            arguments = realloc(arguments, bufsize * sizeof(char *));
            if (!arguments) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        argument = strtok(NULL, " \t\n\r\a");
    }
    arguments[position] = NULL;
    return arguments;
}

void free_arguments(char **arguments) {
    free(arguments);
}

