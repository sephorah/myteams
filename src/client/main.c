/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** my_teams
*/

#include "my_teams_client.h"

int main(int ac, char **av)
{
    if (ac != 3 || (ac == 2 && strcmp("-help", av[2]) == 0)) {
        printf("USAGE:\n\t./myteams_cli ip port\n\n\tip is the server ip "
        "address on which the server socket listens\n\tport is the port "
        "number on which the server socket listens\n");
        return ERROR;
    }
    run_client(av[1], atoi(av[2]));
}
