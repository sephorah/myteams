/*
** EPITECH PROJECT, 2024
** handle_server.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

static bool set_fds(server_info_t *info)
{
    FD_ZERO(&info->rfds);
    FD_SET(info->socket_desc, &info->rfds);
    FD_ZERO(&info->wfds);
    FD_SET(STDIN_FILENO, &info->rfds);
    for (int i = 0; i < MAX_FDS; i++) {
        if (info->used_fds[i] > 0) {
            FD_SET(info->used_fds[i], &info->rfds);
        }
        if (info->used_fds[i] > info->max_fd) {
            info->max_fd = info->used_fds[i];
        }
    }
    return true;
}

static void init_addr(struct sockaddr_in *serv_addr, int port)
{
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(port);
    serv_addr->sin_addr.s_addr = INADDR_ANY;
}

static bool init_server_connection(server_info_t *info, int port)
{
    int opt = 1;

    info->socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (info->socket_desc == -1) {
        return false;
    }
    if (setsockopt(info->socket_desc,
    SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        return false;
    }
    init_addr(&info->serv_addr, port);
    if (bind(info->socket_desc, (struct sockaddr *)&info->serv_addr,
    sizeof(info->serv_addr)) == -1) {
        return false;
    }
    if (listen(info->socket_desc, MAX_FDS) == -1) {
        return false;
    }
    return true;
}

static bool init_server(server_info_t *info, int port)
{
    if (!init_server_connection(info, port)) {
        printf("%s\n", strerror(errno));
        return false;
    }
    for (int i = 0; i < MAX_FDS; i++) {
        info->used_fds[i] = 0;
    }
    info->max_fd = info->socket_desc;
    info->team_uuid = NULL;
    info->channel_uuid = NULL;
    info->thread_uuid = NULL;
    init_save_db(info);
    if (!init_db(info)) {
        return false;
    }
    load_save_users(info);
    return true;
}

static void save_info(server_info_t *info)
{
    save_users(info);
}

static void handle_signals(int sig)
{
    if (sig == SIGINT) {
    }
}

static bool catch_signals(struct sigaction *sa, sigset_t *sigset)
{
    sa->sa_handler = handle_signals;
    sigemptyset(&sa->sa_mask);
    sa->sa_flags = 0;
    if (sigaction(SIGINT, sa, NULL) == -1) {
        return false;
    }
    if (sigemptyset(sigset) == -1) {
        return false;
    }
    return true;
}

int run_server(unsigned int port)
{
    struct sigaction sa;
    sigset_t sigset;
    server_info_t info;

    if (!init_server(&info, port) || !catch_signals(&sa, &sigset))
        return ERROR;
    while (1) {
        set_fds(&info);
        if (pselect(info.max_fd + 1, &info.rfds, &info.wfds,
        NULL, NULL, &sigset) < 0) {
            save_info(&info);
            close(info.socket_desc);
            break;
        }
        handle_clients(&info);
    }
    return SUCCESS;
}
