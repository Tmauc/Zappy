/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# pragma once

bool process_client_until_eof(struct zappy_s *, fd_set *, struct client_s *);
int get_remaining_clients(struct zappy_s *zappy, const char *team_name);
