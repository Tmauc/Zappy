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

static const char *const ressources_names[] = {
    "food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame", NULL
};

void display_inventory(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    char *inventory;

    (void) zappy;
    (void) cmd;
    asprintf(&inventory, "[food %d, linemate %d, deraumere %d, sibur %d, "
            "mendiane %d, phiras %d, thystame %d]\n",
            client->inventory[FOOD], client->inventory[LINEMATE],
            client->inventory[DERAUMERE], client->inventory[SIBUR],
            client->inventory[MENDIANE], client->inventory[PHIRAS],
            client->inventory[THYSTAME]);
    strcat(client->write_buf, inventory);
    free(inventory);
}

void take_object(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    assert(!strncmp(cmd, "Take ", 5));
    for (int i = 0; ressources_names[i]; i++) {
        if (!strcmp(ressources_names[i], cmd + 5)
                && zappy->board[client->y][client->x].ressources[i]) {
            client->inventory[i] += 1;
            zappy->board[client->y][client->x].ressources[i] -= 1;
            strcat(client->write_buf, "ok\n");
            return;
        }
    }
    strcat(client->write_buf, "ko\n");
}

void drop_object(
        struct zappy_s *zappy,
        struct client_s *client,
        const char *cmd)
{
    assert(!strncmp(cmd, "Set ", 4));
    for (int i = 0; ressources_names[i]; i++) {
        if (!strcmp(ressources_names[i], cmd + 4)
                && client->inventory[i]) {
            client->inventory[i] -= 1;
            zappy->board[client->y][client->x].ressources[i] += 1;
            strcat(client->write_buf, "ok\n");
            return;
        }
    }
    strcat(client->write_buf, "ko\n");
}
