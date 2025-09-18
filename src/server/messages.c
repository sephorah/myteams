/*
** EPITECH PROJECT, 2024
** messages.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

static void update_total_len(int *total_len, struct priv_msg_s *p)
{
    *total_len += (strlen(p->receiver_uuid) + 2 + strlen(p->msg) + 2
    + MAX_LEN_TIMESTAMP + 2);
}

static char *init_buffer(struct user_s *user, char *receiver_uuid,
    int *total_len)
{
    char *buffer = NULL;
    struct priv_msg_s *p = NULL;

    SLIST_FOREACH(p, &user->private_msgs, next) {
        if (strcmp(p->receiver_uuid, receiver_uuid) == 0) {
            update_total_len(total_len, p);
        }
    }
    buffer = malloc(sizeof(char) * (*total_len + 1));
    if (!buffer) {
        return NULL;
    }
    buffer[0] = '\0';
    return buffer;
}

static void fill_buffer(struct priv_msg_s *p, char *buffer)
{
    int line_len = (strlen(p->receiver_uuid) + 2 + strlen(p->msg) + 2
    + MAX_LEN_TIMESTAMP + 2);
    char *tmp = malloc(sizeof(char) * line_len);

    if (!tmp)
        return;
    sprintf(tmp, "%s \"%s\" %ld\t", p->receiver_uuid, p->msg, p->timestamp);
    strcat(buffer, tmp);
    free(tmp);
}

static bool check_receiver_uuid(char *uuid, server_info_t *info)
{
    struct user_s *p;

    SLIST_FOREACH(p, &info->users, next) {
        if (strcmp(p->uuid, uuid) == 0) {
            return true;
        }
    }
    return false;
}

static bool get_messages_user(struct user_s *sender,
    char *receiver_uuid, int *client_fd)
{
    struct priv_msg_s *p = NULL;
    int total_len = 0;
    char *buffer = init_buffer(sender, receiver_uuid, &total_len);

    if (!buffer) {
        dprintf(*client_fd, "%d\n", INTERNAL_ERROR);
        return false;
    }
    SLIST_FOREACH(p, &sender->private_msgs, next) {
        if (strcmp(p->receiver_uuid, receiver_uuid) == 0) {
            fill_buffer(p, buffer);
        }
    }
    buffer[total_len] = '\0';
    dprintf(*client_fd, "%d\t%s\n", LIST_PRIV_MSGS, buffer);
    free(buffer);
    return true;
}

bool messages_command(char **args, int *client_fd,
    server_info_t *info)
{
    struct user_s *sender = get_sender(info, *client_fd);

    if (count_elements_array(args) != 1 ||
        strlen(args[0]) != MAX_UUID_STR_LEN) {
        dprintf(*client_fd, "%d\n", INVALID_ARGS);
        return false;
    }
    if (!sender) {
        dprintf(*client_fd, "%d\n", INTERNAL_ERROR);
        return false;
    }
    if (!check_receiver_uuid(args[0], info)) {
        dprintf(*client_fd, "%d\t%s\n", USER_NOT_FOUND, args[0]);
        return false;
    }
    return get_messages_user(sender, args[0], client_fd);
}
