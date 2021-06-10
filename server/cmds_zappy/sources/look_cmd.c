/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# include "common.h"
# include <sys/queue.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <assert.h>
# include "zappy.h"
# include "utils_cmds.h"
# include "commands.h"
# include "serv_socket.h"

static const char *const ressources_names[] = {
    "food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame", NULL
};

static void to_print(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *str)
{
    fd_set read_fds;
    int activity;

    if (strlen(client->write_buf) + strlen(str) >
            ARRAY_SIZE(client->write_buf))
        block_until_client_activity(zappy, &read_fds, &activity);
    if (strlen(client->write_buf) + strlen(str) <=
            ARRAY_SIZE(client->write_buf))
        strcat(client->write_buf, str);
}

static bool func_that_print_thanks_norme(
        struct zappy_s *zappy,
        struct client_s *client,
        int i,
        bool sep)
{
    if (sep)
        to_print(zappy, client, " ");
    to_print(zappy, client, ressources_names[i]);
    return (true);
}

static void display_case(
        struct zappy_s *zappy,
        struct client_s *client,
        struct case_s *case_)
{
    struct client_s *iter;
    bool sep = !STAILQ_EMPTY(&case_->players);

    STAILQ_FOREACH(iter, &case_->players, next) {
        to_print(zappy, client, "player");
        if (STAILQ_NEXT(iter, next))
            to_print(zappy, client, " ");
    }
    for (int i = 0; ressources_names[i]; i++)
        for (int j = 0; j < case_->ressources[i]; j++)
            sep = func_that_print_thanks_norme(zappy, client, i, sep);
}

static void display_pre_infos(struct zappy_s *zappy, struct client_s *client,
        int pos[3], bool is_first_pass)
{
    int x = pos[1];
    int y = pos[2];

    for (; *pos; (*pos)--) {
        int j = is_first_pass ? *pos : -(*pos);
        to_print(zappy, client, ",");
        switch (client->direction) {
            case RIGHT:
                display_case(zappy, client, get_case(zappy, x + *pos, y - j));
                break;
            case TOP:
                display_case(zappy, client, get_case(zappy, x - j, y + *pos));
                break;
            case LEFT:
                display_case(zappy, client, get_case(zappy, x - *pos, y - j));
                break;
            case BOT:
                display_case(zappy, client, get_case(zappy, x - j, y - *pos));
        }
    }
}

void display_look(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd __attribute__((unused)))
{
    int x = client->x;
    int y = client->y;

    strcat(client->write_buf, "[");
    display_case(zappy, client, &zappy->board[y][x]);
    for (int i = 1; i < client->level + 1; i++) {
        int infos[3] = {i, x, y};
        display_pre_infos(zappy, client, infos, true);
        to_print(zappy, client, ",");
        if (client->direction == RIGHT)
            display_case(zappy, client, get_case(zappy, x + i, y));
        if (client->direction == TOP)
            display_case(zappy, client, get_case(zappy, x, y + i));
        if (client->direction == LEFT)
            display_case(zappy, client, get_case(zappy, x - i, y));
        if (client->direction == BOT)
            display_case(zappy, client, get_case(zappy, x, y - i));
        display_pre_infos(zappy, client, infos, false);
    }
    to_print(zappy, client, "]\n");
}
