/*
** EPITECH PROJECT, 2024
** help.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

bool help_command(UNUSED char **args, int *client_fd,
    UNUSED server_info_t *info)
{
    dprintf(*client_fd, "%d\n", HELP_MSG);
    return true;
}
