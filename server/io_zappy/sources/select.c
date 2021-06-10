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
# include "tools.h"
# include "zappy.h"

# ifndef USING_SELECT_FOR_TIME_HANDLING
double get_elapsed_time(void)
{
    static struct timeval t1;
    struct timeval t2;

    if (t1.tv_usec == 0)
        gettimeofday(&t1, NULL);
    gettimeofday(&t2, NULL);
    return ((t2.tv_sec * 1000000 + t2.tv_usec)
            - (t1.tv_sec * 1000000 + t1.tv_usec));
}
# endif

int setup_read_fd_array(struct zappy_s *zappy, fd_set *read_fds)
{
    int hightest_fd = zappy->serv_sockfd;
    struct client_s *iter;

    FD_ZERO(read_fds);
    FD_SET(zappy->serv_sockfd, read_fds);
    STAILQ_FOREACH(iter, &zappy->head, next) {
        FD_SET(iter->fd, read_fds);
        hightest_fd = max(hightest_fd, iter->fd);
    }
    return (hightest_fd + 1);
}

fd_set setup_write_fds(struct zappy_s *zappy, bool *to_write)
{
    struct client_s *iter;
    fd_set write_fds;

    FD_ZERO(&write_fds);
    STAILQ_FOREACH(iter, &zappy->head, next)
        if (*iter->write_buf) {
            *to_write = true;
            FD_SET(iter->fd, &write_fds);
        }
    return (write_fds);
}
