/*
** EPITECH PROJECT, 2024
** my_teams_client.h
** File description:
** my_teams
*/

#ifndef MY_TEAMS_CLIENT_H_
    #define MY_TEAMS_CLIENT_H_
    #include "my_teams.h"
    #include "../libs/myteams/logging_client.h"

typedef struct client_info_s {
    fd_set rfds;
    fd_set wfds;
    int max_fd;
    int socket_desc;
    struct sockaddr_in server_addr;
    char username[MAX_NAME_LENGTH];
    char uuid[UUID_STR_LEN];
    int status;
    bool logged_in;
} client_info_t;

int run_client(char *ip_address, int port);
bool is_command(char *input);
void help(UNUSED client_info_t *info, UNUSED char **args);
void login(client_info_t *info, char **args);
void logout(client_info_t *info, UNUSED char **args);
void already_connected(UNUSED client_info_t *info,
    UNUSED char **args);
void users(UNUSED client_info_t *info, char **args);
void user(UNUSED client_info_t *info, char **args);
void user_not_found(UNUSED client_info_t *info, char **args);
void receive_msg(UNUSED client_info_t *info, char **args);
void messages(UNUSED client_info_t *info, char **args);
void user_logged_in(UNUSED client_info_t *info, char **args);
void user_logged_out(UNUSED client_info_t *info, char **args);

typedef struct handle_reply_s {
    int status_code;
    void (*handle)(client_info_t *, char **args);
} handle_reply_t;

#endif /* !MY_TEAMS_CLIENT_H_ */
