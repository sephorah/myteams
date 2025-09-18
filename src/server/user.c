/*
** EPITECH PROJECT, 2024
** user.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

bool user_command(char **args, int *client_fd,
    server_info_t *info)
{
    struct user_s *p;

    if (count_elements_array(args) != 1 ||
    strlen(args[0]) != MAX_UUID_STR_LEN) {
        dprintf(*client_fd, "%d\n", INVALID_ARGS);
        return false;
    }
    SLIST_FOREACH(p, &info->users, next) {
        if (strcmp(p->uuid, args[0]) == 0) {
            dprintf(*client_fd, "%d\t%s %s %d\n", DETAILS_USER,
            p->username, p->uuid, p->connected);
            return true;
        }
    }
    dprintf(*client_fd, "%d\t%s\n", USER_NOT_FOUND, args[0]);
    return true;
}
