/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/queue.h>
# include <unistd.h>
# include <stdio.h>
# include "tools.h"
# include "zappy.h"

static struct case_s **get_board(int x, int y)
{
    struct case_s **board = malloc(sizeof(*board) * (y + 1));

    for (int i = 0; i < y; i++)
        board[i] = calloc(x, sizeof(struct case_s));
    board[y] = NULL;
    return (board);
}

static bool add_team(struct team_s **teams, const char *new_team)
{
    int i;

    for (i = 0; (*teams)[i].name != NULL; i++);
    *teams = realloc(*teams, sizeof(struct team_s) * (i + 2));
    (*teams)[i] = (struct team_s) {strdup(new_team), 0};
    (*teams)[i + 1] = (struct team_s) {NULL};
    return (true);
}

static bool add_teams(struct zappy_s *zappy, const char *argv[])
{
    for (int i = optind - 1; argv[i] != NULL && argv[i][0] != '-'; i++)
        if (!add_team(&(zappy->teams), argv[i]))
            return (false);
    return (true);

}

static bool handle_opt_args(
        struct zappy_s *zappy,
        int c,
        const char *argv[],
        int *nbr)
{
    if (!strchr("pxycfn", c))
        return (false);
    if (c == 'p' && (zappy->port = atoi(optarg)) <= 0)
        return (false);
    if (c == 'x' && (zappy->length_x = atoi(optarg)) <= 0)
        return (false);
    if (c == 'y' && (zappy->length_y = atoi(optarg)) <= 0)
        return (false);
    if (c == 'c' && (*nbr = atoi(optarg)) <= 0)
        return (false);
    if (c == 'f' && (zappy->freq = atoi(optarg)) <= 0)
        return (false);
    if (c == 'n' && !add_teams(zappy, argv))
        return (false);
    return (true);
}

bool parse_zappy_args(struct zappy_s *zappy, const char *argv[])
{
    int c;
    int client_nbr = 0;

    *zappy = (struct zappy_s) {.freq = 10,
        .teams = malloc(sizeof(struct team_s)),
    };
    zappy->teams[0] = (struct team_s) {NULL};
    while ((c = getopt(get_word_arr_size((char **) argv),
                    (char * const *)argv, "p:x:y:n:c:f:")) != -1)
        if (!handle_opt_args(zappy, c, argv, &client_nbr))
            return (false);
    if (!zappy->port || !zappy->length_x || !zappy->length_y || client_nbr < 2)
        return (false);
    for (int i = 0; zappy->teams[i].name != NULL; i++)
        zappy->teams[i].allowed = client_nbr;
    zappy->board = get_board(zappy->length_x, zappy->length_y);
    return (true);
}
