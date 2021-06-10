/*
** EPITECH PROJECT, 2019
** zappy_ai.hpp
** File description:
** zappy_ai.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <algorithm>

# define SA struct sockaddr

# define FALSE 0
# define NO 0
# define TRUE 1
# define YES 1
# define OK 0
# define KO 1

# define LEFT 10
# define UP 11
# define RIGHT 12
# define DOWN 13

# define FOOD 0
# define LINEMATE 1
# define DERAUMERE 2
# define SIBUR 3
# define MENDIANE 4
# define PHIRAS 5
# define THYSTAME 6

typedef struct pos_t
{
    int x;
    int y;
} s_pos;

int is_num(std::string str);
int is_param(std::string str);
void exit_error(std::string str);
int get_nbrFunc(std::string cmd);
int command(int nb_func, std::string msg);
pos_t checkPos(pos_t pos, pos_t sizeMap);
std::vector<std::string> cast_av(char **av);
std::vector<std::string> my_str_to_vector(const std::string &s, char delim);

