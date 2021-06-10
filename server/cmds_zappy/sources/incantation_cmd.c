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
# include "commands_list.h"

static const enum ressources_e ressources_requiered[][8] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 0, 1, 0, 2, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

void evolve_players_end(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    char level[] = "Current level: ?\n";

    (void) cmd;
    (void) zappy;
    level[strlen(level) - 2] = client->level + '0';
    strcat(client->write_buf, level);
}

int get_players_nbr_on_case(struct case_s *case_)
{
    struct client_s *iter;
    int counter = 0;

    STAILQ_FOREACH(iter, &case_->players, next) {
        if (STAILQ_NEXT(iter, next) &&
                STAILQ_NEXT(iter, next)->level != iter->level)
            return (0);
        counter += 1;
    }
    return (counter);
}

static void evolve_players_on_case(
        struct zappy_s *zappy,
        struct client_s *client,
        struct case_s *case_)
{
    const size_t ressources_size = sizeof(enum ressources_e)
        * (RESSOURCES_COUNT - 1);
    struct cmds_stack_node_s *node;
    struct client_s *iter;

    memset(&case_->ressources[1], 0, ressources_size);
    STAILQ_FOREACH(iter, &zappy->board[client->y][client->x].players, next) {
        node = malloc(sizeof(*node));
        *node = (struct cmds_stack_node_s) {.client = iter,
            .cmd = {
                .func = evolve_players_end,
                .exec_time = 300 * 1000000 / zappy->freq + zappy->time_counter,
            },
        };
        STAILQ_INSERT_HEAD(&zappy->cmds_stack, node, next);
        iter->level += 1;
        strcat(client->write_buf, "Elevation underway\n");
    }
}

void evolve_player(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    struct case_s *case_ = &zappy->board[client->y][client->x];
    const enum ressources_e *requiered =
        ressources_requiered[client->level - 1];
    bool player_nbr = get_players_nbr_on_case(case_);
    const size_t ressources_size = sizeof(enum ressources_e)
        * (RESSOURCES_COUNT - 1);

    (void) cmd;
    if (client->level != 8 && player_nbr == *requiered &&
            !memcmp(&requiered[1], &case_->ressources[1],
                ressources_size - 1)) {
        evolve_players_on_case(zappy, client, case_);
    } else {
        strcat(client->write_buf, "ko\n");
    }
}
