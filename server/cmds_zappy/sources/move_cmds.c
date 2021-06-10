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

void move_forward(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    int x = client->x;
    int y = client->y;

    (void) cmd;
    STAILQ_REMOVE(&zappy->board[y][x].players, client, client_s, next);
    switch (client->direction) {
        case TOP:
            client->y = y + 1 == zappy->length_y ? 0 : y + 1; break;
        case BOT:
            client->y = y == 0 ? zappy->length_y - 1 : y - 1; break;
        case RIGHT:
            client->x = x + 1 == zappy->length_x ? 0 : x + 1; break;
        case LEFT:
            client->x = x == 0 ? zappy->length_x - 1 : x - 1; break;
        default: assert(!"Break out of enum values");
    }
    STAILQ_INSERT_HEAD(&zappy->board[client->y][client->x].players,
            client, next);
    strcat(client->write_buf, "ok\n");
}

void turn_right(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    (void) zappy;
    (void) cmd;
    client->direction = client->direction + 1 == 4 ? 0 : client->direction + 1;
    strcat(client->write_buf, "ok\n");
}

void turn_left(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    (void) zappy;
    (void) cmd;
    client->direction = client->direction ? client->direction - 1 : 3;
    strcat(client->write_buf, "ok\n");
}
