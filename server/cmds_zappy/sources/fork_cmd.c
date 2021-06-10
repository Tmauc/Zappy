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
# include "zappy.h"
# include "commands.h"
# include "commands_list.h"

void increase_remaining_client(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    (void) client;
    for (int i = 0; zappy->teams[i].name; i++) {
        if (!strcmp(zappy->teams[i].name, cmd))
            zappy->teams[i].allowed += 1;
    }
}

void fork_player(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    struct cmds_stack_node_s *node = malloc(sizeof(*node));

    (void) cmd;
    *node = (struct cmds_stack_node_s) {.next = {0},
        .cmd = {.func = increase_remaining_client,
            .exec_time = 600 * 1000000 / zappy->freq + zappy->time_counter,
            .command = strdup(client->team_name)
        },
    };
    STAILQ_INSERT_HEAD(&zappy->cmds_stack, node, next);
    strcat(client->write_buf, "ok\n");
}
