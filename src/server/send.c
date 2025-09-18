/*
** EPITECH PROJECT, 2024
** send.c
** File description:
** myteams
*/

#include "my_teams_server.h"

struct user_s *get_sender(server_info_t *info, int client_fd)
{
    struct user_s *p;

    SLIST_FOREACH(p, &info->users, next) {
        if (client_fd == p->client_fd) {
            return p;
        }
    }
    return NULL;
}

static struct priv_msg_s *create_node_priv_msg(char *receiver_uuid,
    char *msg)
{
    struct priv_msg_s *new_msg = malloc(sizeof(priv_msg_t));

    if (new_msg == NULL) {
        return NULL;
    }
    strcpy(new_msg->msg, msg);
    strcpy(new_msg->receiver_uuid, receiver_uuid);
    new_msg->timestamp = time(NULL);
    return new_msg;
}

static void add_msg_to_save(char *receiver_uuid,
    char *msg, struct user_s *p)
{
    priv_msg_t *new_priv_msg = create_node_priv_msg(receiver_uuid, msg);

    if (!new_priv_msg) {
        return;
    }
    SLIST_INSERT_HEAD(&p->private_msgs, new_priv_msg, next);
}

static void check_receiver(struct user_s *p, char **args,
    char *sender_uuid)
{
    if (p->client_fd > 0 && p->connected == CONNECTED) {
        dprintf(p->client_fd, "%d\t%s\t%s\n", RECEIVED_MSG, sender_uuid,
        args[1]);
    }
}

static void send_msg(char **args, struct user_s *sender, int *client_fd,
    server_info_t *info)
{
    struct user_s *p;

    SLIST_FOREACH(p, &info->users, next) {
        if (strcmp(p->uuid, args[0]) == 0) {
            check_receiver(p, args, sender->uuid);
            dprintf(*client_fd, "%d\n", SENT_MSG);
            server_event_private_message_sended(sender->uuid,
            p->uuid, args[1]);
            add_msg_to_save(p->uuid, args[1], sender);
            return;
        }
    }
    dprintf(*client_fd, "%d\t%s\n", USER_NOT_FOUND, args[0]);
}

bool send_command(char **args, int *client_fd,
    server_info_t *info)
{
    struct user_s *sender = get_sender(info, *client_fd);

    if (count_elements_array(args) != 2 ||
        strlen(args[0]) != MAX_UUID_STR_LEN) {
        dprintf(*client_fd, "%d\n", INVALID_ARGS);
        return false;
    }
    if (strlen(args[1]) >= MAX_BODY_LENGTH) {
        dprintf(*client_fd, "%d\n", TOO_LONG_BODY);
        return false;
    }
    if (!sender) {
        dprintf(*client_fd, "%d\n", INTERNAL_ERROR);
        return false;
    }
    send_msg(args, sender, client_fd, info);
    return true;
}
