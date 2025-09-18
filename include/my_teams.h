/*
** EPITECH PROJECT, 2024
** my_teams.h
** File description:
** my_teams
*/

#ifndef MY_TEAMS_H_
    #define MY_TEAMS_H_
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <sys/select.h>
    #include <string.h>
    #include <uuid/uuid.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <dlfcn.h>
    #include <stdbool.h>
    #include <sys/queue.h>
    #include <uuid/uuid.h>
    #include <time.h>
    #define MAX_LEN_TIMESTAMP 11
    #define MAX_FDS 20
    #define BUFFER_LEN 500
    #define SUCCESS 0
    #define ERROR 84
    #define MAX_COMMAND_LENGTH 1000
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define MAX_UUID_STR_LEN 36
    #define LOGGING_LIB_NAME "./libs/myteams/libmyteams.so"
    #define CONNECTED 1
    #define NOT_CONNECTED 0
    #define UNUSED __attribute__((unused))

enum STATUS_CODE {
    COMMAND_OKAY = 200,
    SUCCESSFUL_LOGIN = 201,
    CREATED_USER = 202,
    USER_LOGGED_IN = 203,
    RECEIVED_MSG = 211,
    SENT_MSG = 212,
    SUCCESSFUL_CONNECTION = 220,
    SUCCESSFUL_LOGOUT = 221,
    USER_LOGGED_OUT = 222,
    LIST_USERS = 230,
    DETAILS_USER = 231,
    LIST_PRIV_MSGS = 232,
    HELP_MSG = 234,
    LIST_ALL_TEAMS_OF_USER = 235,
    LIST_ALL_USERS_FROM_TEAM = 237,
    SUCCESSFUL_SUBSCRIBE_TEAM = 242,
    SUCESSFUL_UNSUBSCRIBE_TEAM = 243,
    CREATED_NEW_TEAM = 270,
    CREATED_NEW_CHANNEL = 271,
    CREATED_NEW_THREAD = 272,
    CREATED_NEW_REPLY = 273,
    LIST_ALL_TEAMS = 280,
    LIST_ALL_CHANNELS = 281,
    LIST_ALL_THREADS = 282,
    LIST_ALL_REPLIES = 283,
    CURRENT_USER_DETAILS = 284,
    SELECTED_TEAM_DETAILS = 285,
    SELECTED_CHANNEL_DETAILS = 286,
    SELECTED_THREAD_DETAILS = 287,
    SET_CONTEXT = 301,
    INVALID_ARGS = 400,
    USER_NOT_FOUND = 401,
    TEAM_NOT_FOUND = 402,
    THREAD_NOT_FOUND = 403,
    CHANNEL_NOT_FOUND = 404,
    ALREADY_EXISTS = 410,
    ALREADY_CONNECTED = 411,
    TOO_LONG_NAME = 420,
    TOO_LONG_DESCRIPTION = 421,
    TOO_LONG_BODY = 422,
    NOT_LOGGED_IN = 430,
    INTERNAL_ERROR = 500,
    UNKNOWN_COMMAND = 502,
    NONE = 0,
};

char **str_tok_word_array(char *str_not_parsed, const char *delim);
int count_elements_array(char **arr);

#endif /* !MY_TEAMS_H_ */
