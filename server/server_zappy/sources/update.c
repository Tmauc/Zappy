/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# include "common.h"
# include <time.h>
# include <netdb.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <sys/queue.h>
# include "zappy.h"
# include "update_graphical.h"
# include "commands.h"

static void add_ressources(struct zappy_s *zappy)
{
    static int tics;
    int rand_x;
    int rand_y;
    int count = 0;

    if (zappy->time_counter - tics < 100)
        return;
    rand_x = rand() % zappy->length_x;
    rand_y = rand() % zappy->length_y;
    tics = zappy->time_counter;
    for (int i = 0; i < RESSOURCES_COUNT; i++)
        count += zappy->board[rand_y][rand_x].ressources[i];
    if (!count) {
        zappy->board[rand_y][rand_x].ressources[rand() % RESSOURCES_COUNT] += 1;
        zappy->board[rand_y][rand_x].ressources[FOOD] += 1;
    }
}

void remove_client_from_cmds_stack(struct zappy_s *zappy, int fd)
{
    struct cmds_stack_node_s *iter;
    struct cmds_stack_node_s *tmp;

    STAILQ_FOREACH_SAFE(iter, &zappy->cmds_stack, next, tmp) {
        if (iter->client && iter->client->fd == fd) {
            STAILQ_REMOVE(&zappy->cmds_stack, iter, cmds_stack_node_s, next);
            free((void *) iter->cmd.command);
            free(iter);
        }
    }
}

static void check_for_dead_clients(struct zappy_s *zappy)
{
    struct client_s *iter;
    struct client_s *tmp;

    STAILQ_FOREACH_SAFE(iter, &zappy->head, next, tmp) {
        if (!iter->team_name)
            continue;
        if (iter->food_end_time < zappy->time_counter) {
            iter->inventory[FOOD] -= 1;
            iter->food_end_time = zappy->time_counter + 126
                * 1000000 / zappy->freq;
        }
        if (iter->inventory[FOOD] < 0) {
            write(iter->fd, "dead\n", 5);
            remove_client_from_cmds_stack(zappy, iter->fd);
            STAILQ_REMOVE(&zappy->head, iter, client_s, next);
            close(iter->fd);
            free(iter->team_name);
            free(iter);
        }
    }
}

void update_clients_given_elapsed_time(struct zappy_s *zappy)
{
    struct cmds_stack_node_s *iter;
    struct cmds_stack_node_s *tmp;
    struct client_s *client;
    bool update_graphical = false;

    check_for_dead_clients(zappy);
    add_ressources(zappy);
    STAILQ_FOREACH_SAFE(iter, &zappy->cmds_stack, next, tmp) {
        if (iter->cmd.exec_time < zappy->time_counter) {
            update_graphical = true;
            iter->cmd.func(zappy, iter->client, iter->cmd.command);
            STAILQ_REMOVE(&zappy->cmds_stack, iter, cmds_stack_node_s, next);
            free((void *) iter->cmd.command);
            free(iter);
        }
    }
    STAILQ_FOREACH(client, &zappy->head, next)
        if (update_graphical && client &&
                client->team_name && !strcmp(client->team_name, "GRAPHIC"))
            update_graphical_client(zappy, client);
}
