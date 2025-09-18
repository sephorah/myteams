/*
** EPITECH PROJECT, 2024
** my_str_to_word_array.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

int nbr_line(char *buffer)
{
    int count = 1;

    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
            count++;
    }
    return count;
}

char **str_tok_word_array(char *str_not_parsed, const char *delim)
{
    char *str = strdup(str_not_parsed);
    int nb_line = nbr_line(str);
    char *token = strtok(str, delim);
    char **array = malloc(sizeof(char *) * ((nb_line + 1) + 1));
    size_t i = 0;

    if (array == NULL)
        return NULL;
    while (token != NULL) {
        array[i] = strdup(token);
        token = strtok(NULL, delim);
        i++;
    }
    array[i] = NULL;
    free(str);
    free(token);
    return array;
}
