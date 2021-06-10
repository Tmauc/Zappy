/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# pragma once

enum ressources_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    RESSOURCES_COUNT
};

STAILQ_HEAD(llist_head_s, client_s);
STAILQ_HEAD(stack_head_s, cmds_stack_node_s);
# define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))
# define STAILQ_FOREACH_SAFE(var, head, field, tvar)			\
    for ((var) = STAILQ_FIRST((head));				\
            (var) && ((tvar) = STAILQ_NEXT((var), field), 1);		\
            (var) = (tvar))

enum direction_e {
    RIGHT,
    BOT,
    LEFT,
    TOP,
};

struct client_s
{
    STAILQ_ENTRY(client_s) next;
    int fd;
    int x;
    int y;
    int level;
    char read_buf[1024];
    char write_buf[2048];
    enum direction_e direction;
    char *team_name;
    long food_end_time;
    int inventory[RESSOURCES_COUNT];
};

struct case_s {
    struct llist_head_s players;
    int ressources[RESSOURCES_COUNT];
};

struct team_s {
    char *name;
    int allowed;
};

struct zappy_s {
    int serv_sockfd;
    int port;
    int length_x;
    int length_y;
    struct team_s *teams;
    int freq;
    struct stack_head_s cmds_stack;
    long time_counter;
    struct case_s **board;
    struct llist_head_s head;
};
