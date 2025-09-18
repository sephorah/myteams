/*
** EPITECH PROJECT, 2024
** check_command.c
** File description:
** my_teams
*/

#include "my_teams_client.h"

static bool check_line_break_in_command(char *input)
{
    char *line_break = strchr(input, '\n');
    size_t size = (line_break + 1) - input;

    if (line_break == NULL) {
        printf("ERROR: A valid command MUST contain a line break (\\n).\n");
        return false;
    }
    if (strchr(line_break + 1, '\n') != NULL) {
        printf("ERROR: A valid command MUST contain only "
        "one line break (\\n).\n");
        return false;
    }
    if (input[size + 1] != '\0') {
        printf("ERROR: A valid command MUST not contain any data after "
                "the line break(\\n).\n");
        return false;
    }
    return true;
}

bool is_command(char *input)
{
    if (strlen(input) == 1) {
        printf("A valid command MUST not be empty.\n");
        return false;
    }
    if (!check_line_break_in_command(input)) {
        return false;
    }
    return true;
}
