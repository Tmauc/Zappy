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
# include "commands.h"

static char *get_eject_string(enum direction_e from, enum direction_e look_to)
{
    if (from == look_to)
        return ("eject 1\n");
    if (abs(from - look_to) == 2)
        return ("eject 5\n");
    if ((from == TOP && look_to == RIGHT) ||
            (from == RIGHT && look_to == BOT) ||
            (from == BOT && look_to == LEFT) ||
            (from == LEFT && look_to == TOP))
        return ("eject 3\n");
    return ("eject 7\n");
}

static bool eject_player(
        struct client_s *client,
        struct client_s *iter,
        struct case_s *client_case,
        struct case_s *target_case)
{
    if (iter == client)
        return (false);
    STAILQ_INSERT_HEAD(&target_case->players, iter, next);
    strcat(iter->write_buf, get_eject_string(
                (client->direction  < 2 ? client->direction + 2 :
                 client->direction - 2),
                iter->direction));
    STAILQ_REMOVE(&client_case->players, iter, client_s, next);
    return (true);
}

void eject_players(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd __attribute__((unused)))
{
    struct case_s *client_case = &zappy->board[client->y][client->x];
    int x = client->x;
    int y = client->y;
    struct case_s *target_case;
    struct client_s *iter;
    struct client_s *tmp;
    bool ejected = false;

    if (client->direction == TOP)
        y = y + 1 == zappy->length_y ? 0 : y + 1;
    if (client->direction == BOT)
        y = y ? y - 1 : zappy->length_y - 1;
    if (client->direction == RIGHT)
        x = x + 1 == zappy->length_x ? 0 : x + 1;
    if (client->direction == LEFT)
        x = x ? x - 1 : zappy->length_x - 1;
    target_case = &zappy->board[y][x];
    STAILQ_FOREACH_SAFE(iter, &client_case->players, next, tmp)
        ejected |= eject_player(client, iter, client_case, target_case);
    strcat(client->write_buf, (ejected ? "ok\n" : "ko\n"));
}
