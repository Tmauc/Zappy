/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# include <time.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/queue.h>
# include "zappy.h"
# include "serv_socket.h"

static const char *const ressources_names[] = {
    "food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame", NULL
};

static void send_all_line_values(
        struct zappy_s *zappy,
        struct client_s *client,
        int i,
        int y)
{
    char buffer[42];

    for (int x = 0; x < zappy->length_x; x++) {
        for (int k = 0; k < zappy->board[y][x].ressources[i]; k++) {
            sprintf(buffer, "%d|%d ", x, y);
            strcat(client->write_buf, buffer);
        }
    }
}

void update_graphical_client(struct zappy_s *zappy, struct client_s *client)
{
    struct client_s *iter;
    int fd_activity;
    fd_set read_fds;
    char buffer[42];

    for (int i = 0; i < RESSOURCES_COUNT; i++) {
        strcat(client->write_buf, ressources_names[i]);
        strcat(client->write_buf, " ");
        for (int y = 0; y < zappy->length_y; y++)
            send_all_line_values(zappy, client, i, y);
        strcat(client->write_buf, "\n");
        block_until_client_activity(zappy, &read_fds, &fd_activity);
    }
    strcat(client->write_buf, "players ");
    STAILQ_FOREACH(iter, &zappy->head, next) {
        sprintf(buffer, "%d|%d ", iter->x, iter->y);
        strcat(client->write_buf, buffer);
    }
    strcat(client->write_buf, "\n");
}
