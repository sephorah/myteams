/*
** EPITECH PROJECT, 2024
** my_teams_server.h
** File description:
** my_teams
*/

#ifndef MY_TEAMS_SERVER_H_
    #define MY_TEAMS_SERVER_H_
    #include "my_teams.h"
    #include "../libs/myteams/logging_server.h"
    #define PATH_USERS_DB "db/users/"
    #define PATH_PRIVATE_MSGS_DB "db/users/private_msgs/"
    #include <signal.h>

typedef struct priv_msg_s {
    char receiver_uuid[UUID_STR_LEN];
    char msg[MAX_BODY_LENGTH];
    time_t timestamp;
    SLIST_ENTRY(priv_msg_s) next;
} priv_msg_t;

typedef struct user_s {
    char username[MAX_NAME_LENGTH];
    char uuid[UUID_STR_LEN + 1];
    int connected;
    char *private_msgs_filename;
    int client_fd;
    SLIST_HEAD(, priv_msg_s) private_msgs;
    SLIST_ENTRY(user_s) next;
} user_t;

typedef struct team_s {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int connected;
    char *private_msgs_filename;
    int client_fd;
    SLIST_HEAD(, priv_msg_s) private_msgs;
    SLIST_ENTRY(user_s) next;
} team_t;

typedef struct server_info_s {
    fd_set rfds;
    fd_set wfds;
    int max_fd;
    int socket_desc;
    struct sockaddr_in serv_addr;
    char *users_table_filename;
    SLIST_HEAD(slisthead, user_s) users;
    SLIST_HEAD(, team_s) teams;
    int used_fds[MAX_FDS];
    char *team_uuid;
    char *channel_uuid;
    char *thread_uuid;
} server_info_t;

typedef struct handle_commands_s {
    const char *command;
    bool (*cmd)(char **, int *, server_info_t *);
} handle_command_t;

int run_server(unsigned int port);
void handle_clients(server_info_t *info);
bool help_command(UNUSED char **args, int *client_fd,
    UNUSED server_info_t *info);
bool login_command(char **args, UNUSED int *client_fd,
    UNUSED server_info_t *info);
bool users_command(UNUSED char **args, int *client_fd,
    server_info_t *info);
bool user_command(char **args, int *client_fd,
    server_info_t *info);
bool logout_command(UNUSED char **args, int *client_fd,
    server_info_t *info);
bool send_command(char **args, int *client_fd,
    server_info_t *info);
char *get_filename_save_db(char *folder, char *filename);
void load_save_users(server_info_t *info);
void save_users(server_info_t *info);
bool init_db(server_info_t *info);
void init_save_db(server_info_t *info);
void save_private_msgs_user(struct user_s *user);
void load_priv_msgs_user(struct user_s *user);
struct user_s *get_sender(server_info_t *info, int client_fd);
bool messages_command(char **args, int *client_fd,
    server_info_t *info);

#endif /* !MY_TEAMS_SERVER_H_ */
