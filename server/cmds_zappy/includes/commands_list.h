/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# pragma once

void move_forward(struct zappy_s *, struct client_s *, const char *);
void turn_right(struct zappy_s *, struct client_s *, const char *);
void turn_left(struct zappy_s *, struct client_s *, const char *);
void display_inventory(struct zappy_s *, struct client_s *, const char *);
void display_connect_nbr(struct zappy_s *, struct client_s *, const char *);
void display_look(struct zappy_s *, struct client_s *, const char *);
void take_object(struct zappy_s *, struct client_s *, const char *);
void drop_object(struct zappy_s *, struct client_s *, const char *);
void eject_players(struct zappy_s *, struct client_s *, const char *);
void fork_player(struct zappy_s *, struct client_s *, const char *);
void increase_remaining_client(struct zappy_s *, struct client_s *,
        const char *);
void evolve_player(struct zappy_s *, struct client_s *, const char *);
void broadcast_sound(struct zappy_s *, struct client_s *, const char *);
