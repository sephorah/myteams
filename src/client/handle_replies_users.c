/*
** EPITECH PROJECT, 2024
** handle_replies_users.c
** File description:
** myteams
*/

#include "my_teams_client.h"

void user(UNUSED client_info_t *info, char **args)
{
    char **args_line = NULL;

    if (count_elements_array(args) != 1) {
        return;
    }
    args_line = str_tok_word_array(args[0], " ");
    if (count_elements_array(args_line) != 3) {
        return;
    }
    client_print_user(args_line[1], args_line[0], atoi(args_line[2]));
}

void users(UNUSED client_info_t *info, char **args)
{
    char **args_line = NULL;

    if (count_elements_array(args) < 1) {
        return;
    }
    for (int i = 0; args[i] != NULL; i++) {
        args_line = str_tok_word_array(args[i], " ");
        if (count_elements_array(args_line) != 3) {
            continue;
        }
        client_print_users(args_line[1], args_line[0], atoi(args_line[2]));
    }
}

void user_not_found(UNUSED client_info_t *info, char **args)
{
    if (count_elements_array(args) < 1) {
        return;
    }
    client_error_unknown_user(args[0]);
}
