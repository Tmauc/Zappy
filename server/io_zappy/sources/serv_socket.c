/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

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
# include <sys/queue.h>
# include <sys/time.h>
# include "zappy.h"
# include "select.h"

bool init_serv_socket(int *serv_sockfd, int port)
{
    struct sockaddr_in servaddr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(port),
    };

    if ((*serv_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return (false);
    }
    if ((bind(*serv_sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)))) {
        perror("bind");
        return (false);
    }
    if ((listen(*serv_sockfd, -1))) {
        perror("listen");
        return (false);
    }
    return (true);
}

void accept_and_create_new_client(struct zappy_s *zappy, int serv_sockfd)
{
    int client_sockfd = accept(serv_sockfd, NULL, NULL);
    struct client_s *elem = malloc(sizeof(*elem));

    if (client_sockfd == -1 || !elem) {
        perror("accept new client");
    } else {
        printf("Client connected\n");
        *elem = (struct client_s) {.fd = client_sockfd,
            .x = rand() % zappy->length_x,
            .y = rand() % zappy->length_y,
            .level = 1,
        };
        STAILQ_INSERT_HEAD(&zappy->board[elem->y][elem->x].players, elem, next);
        elem->inventory[FOOD] = 10;
        STAILQ_INSERT_HEAD(&zappy->head, elem, next);
        strcat(elem->write_buf, "WELCOME\n");
    }
}

void flush_clients_output(struct zappy_s *zappy, fd_set *write_fds)
{
    struct client_s *iter;
    char *last_line;
    int len;

    STAILQ_FOREACH(iter, &zappy->head, next) {
        if (!*iter->write_buf || !FD_ISSET(iter->fd, write_fds))
            continue;
        if ((last_line = strrchr(iter->write_buf, '\n'))) {
            last_line++;
            len = strlen(last_line);
            printf("Write: %.*s", (int) (last_line - iter->write_buf),
                    iter->write_buf);
            write(iter->fd, iter->write_buf, last_line - iter->write_buf);
            strcat(iter->write_buf, last_line);
            memset(iter->write_buf + len, 0, ARRAY_SIZE(iter->write_buf) - len);
        }
    }
}

// Using sec_by_freq AFTER select() is NOT portable (see man select).
bool block_until_client_activity(
        struct zappy_s *zappy,
        fd_set *read_fds,
        int *fd_activity)
{
    struct timeval sec_by_freq = {0, (1 * 1000000) / zappy->freq};
    int hightest_fd = setup_read_fd_array(zappy, read_fds);
    bool to_write = false;
    fd_set write_fds = setup_write_fds(zappy, &to_write);

    *fd_activity = select(hightest_fd, read_fds, (to_write ? &write_fds : NULL),
            NULL, &sec_by_freq);
    if (*fd_activity == -1) {
        perror("select");
        return (false);
    }
    flush_clients_output(zappy, &write_fds);
# ifdef USING_SELECT_FOR_TIME_HANDLING
    zappy->time_counter += sec_by_freq.tv_sec * 1000000 + sec_by_freq.tv_usec;
# else
    zappy->time_counter = get_elapsed_time();
# endif
    return (true);
}
