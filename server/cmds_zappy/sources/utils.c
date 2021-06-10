/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# include "common.h"
# include <sys/queue.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "zappy.h"
# include "commands.h"

int get_idx(int pos, int limit)
{
    if (pos < 0)
        return (limit - 1);
    return (pos >= limit ? 0 : pos);
}

struct case_s *get_case(struct zappy_s *zappy, int x, int y)
{
    return (&zappy->board[get_idx(y,
                zappy->length_y)][get_idx(x, zappy->length_x)]);
}
