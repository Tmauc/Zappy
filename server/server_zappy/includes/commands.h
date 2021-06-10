/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# pragma once

struct command_s {
    const char *command;
    void (*func)(zappy_t*, struct client_s*, const char *);
    long exec_time;
    bool take_option;
};

struct cmds_stack_node_s {
    struct client_s *client;
    struct command_s cmd;
    STAILQ_ENTRY(cmds_stack_node_s) next;
};

void process_client_command(zappy_t *, struct client_s *, const char *);
