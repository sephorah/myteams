/*
** EPITECH PROJECT, 2024
** help
** File description:
** my_teams
*/

#include "my_teams_client.h"

void login(client_info_t *info, char **args)
{
    if (count_elements_array(args) != 2) {
        return;
    }
    strcpy(info->uuid, args[0]);
    info->logged_in = true;
    strcpy(info->username, args[1]);
    client_event_logged_in(info->uuid, info->username);
}

void logout(client_info_t *info, UNUSED char **args)
{
    client_event_logged_out(info->uuid, info->username);
    info->status = SUCCESSFUL_LOGOUT;
}

void already_connected(UNUSED client_info_t *info,
    UNUSED char **args)
{
    printf("This user is already connected.\n");
}

void user_logged_in(UNUSED client_info_t *info, char **args)
{
    if (count_elements_array(args) != 2) {
        return;
    }
    client_event_logged_in(args[0], args[1]);
}

void user_logged_out(UNUSED client_info_t *info, char **args)
{
    if (count_elements_array(args) != 2) {
        return;
    }
    client_event_logged_out(args[0], args[1]);
}
