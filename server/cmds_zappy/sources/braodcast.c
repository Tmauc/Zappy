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

static int get_direction(
        bool is_straight_x,
        bool is_straight_y,
        bool from_left,
        bool from_top)
{
    if (is_straight_x && is_straight_y)
        return (0);
    if (is_straight_x)
        return (from_left ? 3 : 7);
    if (is_straight_y)
        return (from_left ? 5 : 1);
    return (from_left ? (from_top ? 2 : 4) : (from_top ? 8 : 6));
}

static int get_direction_info(
        struct zappy_s *zappy,
        struct client_s *client,
        struct client_s *iter)
{
    bool is_straight_x = client->x == iter->x;
    int diff_x_1 = abs(iter->x - client->x);
    int diff_x_2 = zappy->length_x - diff_x_1;
    bool connect_center_x = diff_x_1 <= diff_x_2;
    bool from_left = (connect_center_x && iter->x > client->x) ||
        (!connect_center_x && iter->x < client->x);
    bool is_straight_y = client->y == iter->y;
    int diff_y_1 = abs(iter->y - client->y);
    int diff_y_2 = zappy->length_y - diff_y_1;
    bool connect_center_y = diff_y_1 <= diff_y_2;
    bool from_top = (connect_center_y && iter->y > client->y) ||
        (!connect_center_y && iter->y < client->y);
    int val = get_direction(is_straight_x, is_straight_y, from_left, from_top);

    return (val + (iter->direction + 1) * 2 > 8 ?
        val + (iter->direction + 1) * 2 - 8:
        val + (iter->direction + 1) * 2);
}

void broadcast_sound(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    struct client_s *iter;
    char msg[] = "message ?, ";

    STAILQ_FOREACH(iter, &zappy->head, next) {
        if (iter == client)
            continue;
        msg[8] = get_direction_info(zappy, client, iter) + '0';
        strcat(iter->write_buf, msg);
        strcat(iter->write_buf, cmd + strlen("Broadcast "));
        strcat(iter->write_buf, "\n");
    }
    strcat(client->write_buf, "ok\n");
    fflush(stdout);
}
