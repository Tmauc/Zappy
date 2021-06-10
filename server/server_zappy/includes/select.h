/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# pragma once

# ifndef USING_SELECT_FOR_TIME_HANDLING
    double get_elapsed_time(void);
# endif
int setup_read_fd_array(struct zappy_s *zappy, fd_set *read_fds);
fd_set setup_write_fds(struct zappy_s *zappy, bool *to_write);
