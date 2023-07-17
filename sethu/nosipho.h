#ifndef NOSIPHO_H
#define NOSIPHO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void handle_command(char *command, char **envp);
char **split_arguments(char *line);
void free_arguments(char **arguments);
void handle_file_input(char *filename, char **envp);
void handle_comments(char *command);
void replace_variables(char **arguments, int status);
void handle_alias_command(char **arguments);
void handle_logical_operators(char **commands, char **envp);
char *trim_whitespace(char *str);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
#endif /* NOSIPHO_H */


