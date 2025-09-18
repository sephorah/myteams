/*
** EPITECH PROJECT, 2024
** load_save.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

static struct user_s *create_node_user(char *user_name, char *uuid,
    char *private_msgs_filename)
{
    struct user_s *new_user = malloc(sizeof(struct user_s));

    if (new_user == NULL) {
        return NULL;
    }
    strcpy(new_user->username, user_name);
    strcpy(new_user->uuid, uuid);
    new_user->connected = NOT_CONNECTED;
    new_user->client_fd = 0;
    new_user->private_msgs_filename = private_msgs_filename;
    return new_user;
}

static void get_user_from_save(char *line, server_info_t *info)
{
    char **user_info = str_tok_word_array(line, " \n");
    user_t *new_user = NULL;

    if (count_elements_array(user_info) != 3) {
        return;
    }
    new_user = create_node_user(user_info[0], user_info[1], user_info[2]);
    if (!new_user) {
        return;
    }
    SLIST_INIT(&new_user->private_msgs);
    load_priv_msgs_user(new_user);
    SLIST_INSERT_HEAD(&info->users, new_user, next);
    server_event_user_loaded(new_user->uuid, new_user->username);
    return;
}

void load_save_users(server_info_t *info)
{
    FILE *fptr = fopen(info->users_table_filename, "r");
    char *line = NULL;
    size_t len = 0;

    if (fptr == NULL) {
        return;
    }
    while (getline(&line, &len, fptr) != -1) {
        get_user_from_save(line, info);
    }
    fclose(fptr);
    free(line);
}

void save_users(server_info_t *info)
{
    FILE *fptr = fopen(info->users_table_filename, "w");
    struct user_s *p;

    if (fptr == NULL)
        return;
    SLIST_FOREACH(p, &info->users, next) {
        fprintf(fptr, "%s %s %s\n", p->username, p->uuid,
        p->private_msgs_filename);
        save_private_msgs_user(p);
    }
    fclose(fptr);
}
