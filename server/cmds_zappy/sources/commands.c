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
# include "input_handling.h"

static const command_t CMDS[] = {
    { "Forward", move_forward, 7, false},
    { "Right", turn_right, 7, false},
    { "Left", turn_left, 7, false},
    { "Inventory", display_inventory, 1, false},
    { "Connect_nbr", display_connect_nbr, 1, false},
    { "Take ", take_object, 7, true},
    { "Set ", drop_object, 7, true},
    { "Look", display_look, 7, false},
    { "Eject", eject_players, 7, false},
    { "Fork", fork_player, 42, false},
    { "Incantation", evolve_player, 1, false},
    { "Broadcast", broadcast_sound, 7, true},
};

void display_connect_nbr(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    char *remain;

    (void) cmd;
    asprintf(&remain, "%d\n", get_remaining_clients(zappy, client->team_name));
    strcat(client->write_buf, remain);
    free(remain);
}

long get_last_cmd_start(struct zappy_s *zappy, int fd)
{
    int last_cmd_start_time = zappy->time_counter;
    struct cmds_stack_node_s *iter;

    STAILQ_FOREACH(iter, &zappy->cmds_stack, next)
        if (iter->client && iter->client->fd == fd &&
                last_cmd_start_time < iter->cmd.exec_time)
            last_cmd_start_time = iter->cmd.exec_time;
    return (last_cmd_start_time);
}

void add_command_node(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *buffer,
        int i)
{
    long exec_time = CMDS[i].exec_time * 1000000 / zappy->freq +
        get_last_cmd_start(zappy, client->fd);
    struct cmds_stack_node_s *node = malloc(sizeof(*node));

    *node = (struct cmds_stack_node_s) {.client = client,
        .cmd = {strdup(buffer), CMDS[i].func, exec_time},
    };
    if (!STAILQ_EMPTY(&zappy->cmds_stack))
        STAILQ_INSERT_TAIL(&zappy->cmds_stack, node, next);
    else
        STAILQ_INSERT_HEAD(&zappy->cmds_stack, node, next);
}

void process_client_command(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *buffer)
{
    if (!*buffer || !strcmp(buffer, client->team_name))
        return;
    printf("Recv: %s\n", buffer);
    for (size_t i = 0; i < ARRAY_SIZE(CMDS); i++) {
        if ((!CMDS[i].take_option && !strcmp(buffer, CMDS[i].command)) ||
                (CMDS[i].take_option && !strncmp(buffer, CMDS[i].command,
                                                 strlen(CMDS[i].command)))) {
            add_command_node(zappy, client, buffer, i);
            return;
        }
    }
    strcat(client->write_buf, "ko\n");
}
