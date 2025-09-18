/*
** EPITECH PROJECT, 2024
** save_private_msgs.c
** File description:
** myteams
*/

#include "my_teams_server.h"

static struct priv_msg_s *create_node_priv_msg(char *receiver_uuid,
    char *msg, char *timestamp)
{
    struct priv_msg_s *new_msg = malloc(sizeof(priv_msg_t));

    if (new_msg == NULL) {
        return NULL;
    }
    strcpy(new_msg->msg, msg);
    strcpy(new_msg->receiver_uuid, receiver_uuid);
    new_msg->timestamp = atol(timestamp);
    return new_msg;
}

static void get_priv_msg_from_user(char *line, user_t *user)
{
    char **msg_info = str_tok_word_array(line, "\t\"\n");
    struct priv_msg_s *new_msg = NULL;

    if (count_elements_array(msg_info) != 3) {
        return;
    }
    new_msg = create_node_priv_msg(msg_info[0], msg_info[1], msg_info[2]);
    if (!new_msg) {
        return;
    }
    SLIST_INSERT_HEAD(&user->private_msgs, new_msg, next);
    return;
}

void load_priv_msgs_user(struct user_s *user)
{
    FILE *fptr = fopen(user->private_msgs_filename, "r");
    char *line = NULL;
    size_t len = 0;

    if (fptr == NULL) {
        return;
    }
    while (getline(&line, &len, fptr) != -1) {
        get_priv_msg_from_user(line, user);
    }
    fclose(fptr);
    free(line);
}

void save_private_msgs_user(struct user_s *user)
{
    FILE *fptr = fopen(user->private_msgs_filename, "w");
    struct priv_msg_s *p;

    if (fptr == NULL || user == NULL)
        return;
    SLIST_FOREACH(p, &user->private_msgs, next) {
        fprintf(fptr, "%s\t\"%s\"\t%ld\n", p->receiver_uuid, p->msg,
        p->timestamp);
    }
    fclose(fptr);
}
