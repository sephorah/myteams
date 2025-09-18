/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** my_teams
*/

#include "my_teams_server.h"

int main(int ac, char **av)
{
    if ((ac != 2) || (strcmp(av[1], "-h") == 0)) {
        printf("USAGE: ./myteams_server port\n\n\t"
        "port is the port number on which the server socket listens.\n");
        return ERROR;
    }
    return run_server(atoi(av[1]));
}
