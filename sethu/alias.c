#include "nosipho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIAS_COUNT 10

typedef struct {
    char *name;
    char *value;
} Alias;

Alias alias_list[MAX_ALIAS_COUNT];
int alias_count = 0;

void handle_alias_command(char **arguments) {
    if (arguments[1] == NULL) {
        print_all_aliases();
        return;
    }

    if (arguments[1] != NULL && arguments[2] == NULL) {
        print_alias(arguments[1]);
        return;
    }

    define_aliases(arguments);
}

void print_all_aliases() {
    for (int i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
    }
}

void print_alias(char *name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_list[i].name, name) == 0) {
            printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
            return;
        }
    }

    fprintf(stderr, "Alias not found: %s\n", name);
}

void define_aliases(char **arguments) {
    int i = 1;

    while (arguments[i] != NULL) {
        char *name = strtok(arguments[i], "=");
        char *value = strtok(NULL, "=");

        if (name == NULL || value == NULL) {
            fprintf(stderr, "Invalid alias definition: %s\n", arguments[i]);
            return;
        }

        if (alias_count == MAX_ALIAS_COUNT) {
            fprintf(stderr, "Maximum number of aliases reached\n");
            return;
        }

        for (int j = 0; j < alias_count; j++) {
            if (strcmp(alias_list[j].name, name) == 0) {
                free(alias_list[j].value);
                alias_list[j].value = strdup(value);
                break;
            }
        }

        alias_list[alias_count].name = strdup(name);
        alias_list[alias_count].value = strdup(value);
        alias_count++;

        i++;
    }
}

void free_aliases() {
    for (int i = 0; i < alias_count; i++) {
        free(alias_list[i].name);
        free(alias_list[i].value);
    }
}

