/*
** EPITECH PROJECT, 2024
** handle_replies_msgs.c
** File description:
** myteams
*/

#include "my_teams_client.h"

void help(UNUSED client_info_t *info, UNUSED char **args)
{
    printf("Please check the RFC provided with "
    "this program for more information.\n");
}

void receive_msg(UNUSED client_info_t *info, char **args)
{
    if (count_elements_array(args) != 2) {
        return;
    }
    client_event_private_message_received(args[0], args[1]);
}

void messages(UNUSED client_info_t *info, char **args)
{
    char **args_line = NULL;

    if (count_elements_array(args) < 1) {
        return;
    }
    for (int i = 0; args[i] != NULL; i++) {
        args_line = str_tok_word_array(args[i], "\"");
        if (count_elements_array(args_line) != 3) {
            continue;
        }
        client_private_message_print_messages(args_line[0],
        atol(args_line[2]), args_line[1]);
    }
}
