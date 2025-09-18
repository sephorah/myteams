/*
** EPITECH PROJECT, 2024
** users.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

static void update_total_len(int *total_len, struct user_s *p)
{
    *total_len += (5 + strlen(p->username) + 2 + strlen(p->uuid) + 5);
}

static char *init_buffer(server_info_t *info, int *total_len)
{
    char *buffer = NULL;
    struct user_s *p = NULL;

    SLIST_FOREACH(p, &info->users, next) {
        update_total_len(total_len, p);
    }
    buffer = malloc(sizeof(char) * (*total_len + 1));
    if (!buffer) {
        return NULL;
    }
    buffer[0] = '\0';
    return buffer;
}

static void fill_buffer(struct user_s *p, char *buffer)
{
    int line_len = (strlen(p->username) + 1 + strlen(p->uuid) + 4);
    char *tmp = malloc(sizeof(char) * line_len);

    if (!tmp)
        return;
    sprintf(tmp, "%s %s %d\t", p->username,
    p->uuid, p->connected);
    strcat(buffer, tmp);
    free(tmp);
}

bool users_command(UNUSED char **args, int *client_fd,
    server_info_t *info)
{
    struct user_s *p;
    int total_len = 0;
    char *buffer = init_buffer(info, &total_len);

    if (!buffer) {
        dprintf(*client_fd, "%d\n", INTERNAL_ERROR);
        return false;
    }
    SLIST_FOREACH(p, &info->users, next) {
        fill_buffer(p, buffer);
    }
    buffer[total_len] = '\0';
    dprintf(*client_fd, "%d\t%s\n", LIST_USERS, buffer);
    free(buffer);
    return true;
}
