/*
** EPITECH PROJECT, 2024
** client.c
** File description:
** my_teams
*/

#include "my_teams_client.h"

bool init_client(client_info_t *info, char *ip_address, int port)
{
    info->socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (info->socket_desc < 0) {
        printf("Unable to create socket\n");
        return false;
    }
    info->logged_in = false;
    info->server_addr.sin_family = AF_INET;
    info->server_addr.sin_port = htons(port);
    info->server_addr.sin_addr.s_addr = inet_addr(ip_address);
    if (connect(info->socket_desc, (struct sockaddr *)&info->server_addr,
                sizeof(info->server_addr)) < 0) {
        printf("Unable to connect with the server\n");
        return false;
    }
    info->max_fd = info->socket_desc;
    info->status = SUCCESSFUL_CONNECTION;
    return true;
}

static bool set_fds(client_info_t *info)
{
    FD_ZERO(&info->rfds);
    FD_SET(info->socket_desc, &info->rfds);
    FD_ZERO(&info->wfds);
    FD_SET(STDIN_FILENO, &info->rfds);
    return true;
}

static void handle_status_code(client_info_t *info, char *buffer,
    const handle_reply_t handle[], size_t limit)
{
    char **reply_args = str_tok_word_array(buffer, "\t\n");
    int status_code = 0;

    if (count_elements_array(reply_args) == 0)
        return;
    status_code = atoi(reply_args[0]);
    for (size_t i = 0; i < limit; i++) {
        if (status_code == handle[i].status_code) {
            handle[i].handle(info, reply_args + 1);
            break;
        }
    }
}

static void check_status_code(client_info_t *info, char *buffer)
{
    const handle_reply_t handle[] = { {HELP_MSG, help},
    {SUCCESSFUL_LOGIN, login}, {USER_NOT_FOUND, user_not_found},
    {CREATED_USER, login}, {RECEIVED_MSG, receive_msg},
    {SUCCESSFUL_LOGOUT, logout}, {LIST_PRIV_MSGS, messages},
    {DETAILS_USER, user}, {USER_LOGGED_IN, user_logged_in},
    {ALREADY_CONNECTED, already_connected},
    {LIST_USERS, users}, {USER_LOGGED_OUT, user_logged_out},
    {DETAILS_USER, user},
    };
    size_t limit = sizeof(handle) / sizeof(handle[0]);

    handle_status_code(info, buffer, handle, limit);
}

static bool get_server_reply(client_info_t *info, char *buffer)
{
    int len = 0;

    if (FD_ISSET(info->socket_desc, &info->rfds)) {
        len = read(info->socket_desc, buffer, MAX_COMMAND_LENGTH);
        if (len == -1) {
            return false;
        }
        buffer[len] = '\0';
        check_status_code(info, buffer);
        return true;
    }
    return false;
}

static bool get_input_from_stdin(client_info_t *info, char *buffer)
{
    int len = 0;

    if (FD_ISSET(STDIN_FILENO, &info->rfds)) {
        len = read(STDIN_FILENO, buffer, MAX_COMMAND_LENGTH);
        if (len == -1) {
            return false;
        }
        buffer[len] = '\0';
        if (is_command(buffer) == true) {
            dprintf(info->socket_desc, buffer);
        }
        return true;
    }
    return false;
}

static bool monitor_fds(client_info_t *info, char *buffer)
{
    return (get_input_from_stdin(info, buffer) ||
    get_server_reply(info, buffer));
}

int run_client(char *ip_address, int port)
{
    client_info_t info;
    char buffer[MAX_COMMAND_LENGTH + 1] = {0};

    if (!init_client(&info, ip_address, port)) {
        return ERROR;
    }
    while (info.status != SUCCESSFUL_LOGOUT) {
        memset(buffer, 0, MAX_COMMAND_LENGTH + 1);
        set_fds(&info);
        if (select(info.max_fd + 1, &info.rfds, &info.wfds,
            NULL, NULL) < 0) {
            printf("Error select: %d\n", errno);
            return ERROR;
        }
        monitor_fds(&info, buffer);
    }
    close(info.socket_desc);
    return SUCCESS;
}
