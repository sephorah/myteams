/*
** EPITECH PROJECT, 2024
** logout.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

static void send_user_logged_out_event_to_clients(char *username,
    int *used_fds, char *uuid, int client_fd)
{
    for (int i = 0; i < MAX_FDS; i++) {
        if (used_fds[i] > 0 && used_fds[i] != client_fd) {
            dprintf(used_fds[i], "%d\t%s\t%s\n", USER_LOGGED_OUT, uuid,
            username);
        }
    }
}

bool logout_command(UNUSED char **args, int *client_fd,
    server_info_t *info)
{
    user_t *p;

    SLIST_FOREACH(p, &info->users, next) {
        if (p->client_fd == *client_fd) {
            break;
        }
    }
    if (p == NULL) {
        return false;
    }
    dprintf(*client_fd, "%d\n", SUCCESSFUL_LOGOUT);
    send_user_logged_out_event_to_clients(p->username,
    info->used_fds, p->uuid, *client_fd);
    FD_CLR(*client_fd, &info->rfds);
    *client_fd = 0;
    p->client_fd = 0;
    p->connected = NOT_CONNECTED;
    server_event_user_logged_out(p->uuid);
    return true;
}
