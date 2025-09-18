/*
** EPITECH PROJECT, 2024
** init_db
** File description:
** myteams
*/

#include "my_teams_server.h"

static void init_save_users(server_info_t *info)
{
    SLIST_INIT(&info->users);
}

void init_save_db(server_info_t *info)
{
    init_save_users(info);
}

bool init_db(server_info_t *info)
{
    info->users_table_filename = get_filename_save_db(PATH_USERS_DB,
        "users");
    if (!info->users_table_filename) {
        return false;
    }
    return true;
}
