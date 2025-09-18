/*
** EPITECH PROJECT, 2024
** handle_clients.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

static void handle_commands(char **args, int *client_fd, server_info_t *info)
{
    const handle_command_t CMD[] = {
        {"/help", help_command}, {"/login", login_command},
        {"/logout", logout_command}, {"/users", users_command},
        {"/user", user_command}, {"/send", send_command},
        {"/messages", messages_command},
    };

    if (count_elements_array(args) == 0) {
        return;
    }
    for (size_t i = 0; i < sizeof(CMD) / sizeof(CMD[0]); i++) {
        if (strncmp(CMD[i].command, args[0], strlen(CMD[i].command)) == 0) {
            CMD[i].cmd(args + 1, client_fd, info);
            break;
        }
    }
}

static void trim_str(char *str)
{
    int len = strlen(str);
    bool outside_quotes = true;

    for (int i = 0; i < len; i++) {
        if (outside_quotes && str[i] == ' ') {
            str[i] = '\t';
        }
        if (str[i] == '"') {
            outside_quotes = (!outside_quotes);
        }
    }
}

static void handle_client_input(int *client_fd,
    server_info_t *info)
{
    char input[MAX_COMMAND_LENGTH];
    char **args = NULL;
    int len = read(*client_fd, input, MAX_COMMAND_LENGTH);

    input[len] = '\0';
    trim_str(input);
    args = str_tok_word_array(input, "\"\t\n");
    handle_commands(args, client_fd, info);
}

static void add_to_used_fds(int new_socket, int *used_fds)
{
    for (int i = 0; i < MAX_FDS; i++) {
        if (used_fds[i] == 0) {
            used_fds[i] = new_socket;
            dprintf(used_fds[i], "%d\n", 220);
            break;
        }
    }
}

static void accept_connection(int main_socket, int *used_fds,
    struct sockaddr_in *serv_addr)
{
    int size_address = sizeof(serv_addr);
    int new_socket = accept(main_socket, (struct sockaddr *)serv_addr,
            (socklen_t *)&size_address);

    if (new_socket > 0) {
        add_to_used_fds(new_socket, used_fds);
    } else {
        printf("Error accept\n");
    }
}

void handle_clients(server_info_t *info)
{
    if (FD_ISSET(info->socket_desc, &info->rfds)) {
        accept_connection(info->socket_desc,
        info->used_fds, &info->serv_addr);
        return;
    }
    for (int i = 0; i < MAX_FDS; i += 1) {
        if (FD_ISSET(info->used_fds[i], &info->rfds) &&
        info->used_fds[i] > 0) {
            handle_client_input(&info->used_fds[i], info);
        }
    }
}
