/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

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
# include <assert.h>
# include <sys/queue.h>
# include "common.h"
# include "zappy.h"
# include "commands.h"
# include "update.h"
# include "serv_socket.h"
# include "input_handling.h"
# include "parse_argv.h"

void process_clients(struct zappy_s *zappy, fd_set *read_fds)
{
    struct client_s *iter;
    struct client_s *tmp;

    STAILQ_FOREACH_SAFE(iter, &zappy->head, next, tmp) {
        if (process_client_until_eof(zappy, read_fds, iter)) {
            STAILQ_REMOVE(&zappy->head, iter, client_s, next);
            remove_client_from_cmds_stack(zappy, iter->fd);
            close(iter->fd);
            free(iter->team_name);
            free(iter);
        }
    }
}

bool create_ressources(struct zappy_s *zappy)
{
    const int map_size = zappy->length_y * zappy->length_x;
    int x;
    int y;

    for (int i = 0; i < map_size / 3; i++) {
        y = rand() % zappy->length_x;
        x = rand() % zappy->length_x;
        zappy->board[y][x].ressources[rand() % RESSOURCES_COUNT] += 1;
    }
    return (true);
}

int main(__attribute__((unused)) int ac, const char *av[])
{
    struct zappy_s zappy;
    fd_set read_fds;
    int fd_activity;

    srand(time(NULL));
    if (!parse_zappy_args(&zappy, av) || !create_ressources(&zappy))
        return (84);
    if (!init_serv_socket(&zappy.serv_sockfd, zappy.port))
        return (84);
    while ("Server is running...") {
        if (!block_until_client_activity(&zappy, &read_fds, &fd_activity))
            return (84);
        update_clients_given_elapsed_time(&zappy);
        if (!fd_activity)
            continue;
        if (FD_ISSET(zappy.serv_sockfd, &read_fds))
            accept_and_create_new_client(&zappy, zappy.serv_sockfd);
        process_clients(&zappy, &read_fds);
    }
    close(zappy.serv_sockfd);
}
