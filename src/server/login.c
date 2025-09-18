/*
** EPITECH PROJECT, 2024
** login.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

static void generate_uuid(char *uuid)
{
    uuid_t binuuid;

    uuid_generate_random(binuuid);
    uuid_unparse_lower(binuuid, uuid);
}

static void send_user_logged_in_event_to_clients(char *username,
    int *used_fds, char *uuid, int client_fd)
{
    for (int i = 0; i < MAX_FDS; i++) {
        if (used_fds[i] > 0 && used_fds[i] != client_fd) {
            dprintf(used_fds[i], "%d\t%s\t%s\n", USER_LOGGED_IN, uuid,
            username);
        }
    }
}

static struct user_s *create_node_user(char *user_name, char *uuid,
    int client_fd, char *private_msgs_filename)
{
    struct user_s *new_user = malloc(sizeof(user_t));

    if (new_user == NULL) {
        return NULL;
    }
    strcpy(new_user->username, user_name);
    strcpy(new_user->uuid, uuid);
    new_user->connected = CONNECTED;
    new_user->client_fd = client_fd;
    new_user->private_msgs_filename = private_msgs_filename;
    return new_user;
}

static bool check_already_connected(char *user_name, int client_fd,
    struct user_s *p, UNUSED int *used_fds)
{
    if (strcmp(user_name, p->username) == 0) {
        if (p->client_fd > 0) {
            dprintf(client_fd, "%d\n", ALREADY_CONNECTED);
        } else {
            dprintf(client_fd, "%d\t%s\t%s\n", SUCCESSFUL_LOGIN,
            p->uuid, user_name);
            send_user_logged_in_event_to_clients(p->username,
            used_fds, p->uuid, client_fd);
            p->client_fd = client_fd;
            p->connected = CONNECTED;
            server_event_user_logged_in(p->uuid);
        }
        return true;
    }
    return false;
}

static bool get_user_from_save(char *user_name, int client_fd,
    server_info_t *info)
{
    struct user_s *p;

    SLIST_FOREACH(p, &info->users, next) {
        if (strcmp(p->username, user_name) == 0) {
            if (p->client_fd > 0 && p->connected == CONNECTED) {
                dprintf(client_fd, "%d\n", ALREADY_CONNECTED);
                return true;
            }
        }
    }
    p = NULL;
    SLIST_FOREACH(p, &info->users, next) {
        if (check_already_connected(user_name, client_fd, p,
        info->used_fds)) {
            return true;
        }
    }
    return false;
}

char *get_filename_save_db(char *folder, char *filename)
{
    int len = strlen(folder) + strlen(filename);
    char *str = malloc(sizeof(char) * (len + 1));

    if (str == NULL) {
        return NULL;
    }
    strcpy(str, folder);
    strcat(str, filename);
    return str;
}

static bool add_new_user(char *user_name, int client_fd,
    server_info_t *info)
{
    char uuid[UUID_STR_LEN];
    char *private_msgs_filename = get_filename_save_db(
        PATH_PRIVATE_MSGS_DB, user_name);
    struct user_s *new_user = NULL;

    generate_uuid(uuid);
    dprintf(client_fd, "%d\t%s\t%s\n", SUCCESSFUL_LOGIN, uuid, user_name);
    send_user_logged_in_event_to_clients(user_name,
    info->used_fds, uuid, client_fd);
    new_user = create_node_user(user_name, uuid,
    client_fd, private_msgs_filename);
    if (!new_user)
        return false;
    SLIST_INSERT_HEAD(&info->users, new_user, next);
    server_event_user_created(new_user->uuid, new_user->username);
    server_event_user_logged_in(new_user->uuid);
    return true;
}

bool login_command(char **args, int *client_fd, server_info_t *info)
{
    if (count_elements_array(args) != 1) {
        dprintf(*client_fd, "%d\n", INVALID_ARGS);
        return false;
    }
    if (strlen(args[0]) >= MAX_NAME_LENGTH) {
        dprintf(*client_fd, "%d\n", TOO_LONG_NAME);
        return false;
    }
    if (!get_user_from_save(args[0], *client_fd, info)) {
        add_new_user(args[0], *client_fd, info);
    }
    return true;
}
