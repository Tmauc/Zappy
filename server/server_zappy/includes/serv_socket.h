/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# pragma once

void accept_and_create_new_client(struct zappy_s *zappy, int serv_sockfd);
bool init_serv_socket(int *serv_sockfd, int port);
bool block_until_client_activity(struct zappy_s *, fd_set *, int *);
