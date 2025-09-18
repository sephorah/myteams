/*
** EPITECH PROJECT, 2024
** count_element_arr.c
** File description:
** my_teams
*/

#include <stdlib.h>

int count_elements_array(char **arr)
{
    int nb_elements;

    for (nb_elements = 0; arr[nb_elements] != NULL; nb_elements++);
    return nb_elements;
}
