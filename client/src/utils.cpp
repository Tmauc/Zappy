/*
** EPITECH PROJECT, 2019
** utils.cpp
** File description:
** utils.cpp
*/

#include "client.hpp"
#include "commands.hpp"

Box newBox()
{
    Box tmp_box;

    tmp_box.setNbrPlayer(0);
    return (tmp_box);
}

int is_num(std::string str)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (NO);
    }
    return (YES);
}

int is_param(std::string str)
{
    if (str[0] == '-')
        return (NO);
    else
        return (YES);
}

int get_nbrFunc(std::string cmd)
{
    int nb;

    if ((cmd.find("Take")) != std::string::npos)
        return 9;
    else if ((cmd.find("Set")) != std::string::npos)
        return 10;
    else if ((cmd.find("Broadcast")) != std::string::npos)
        return 5;
    for (nb = 0; nb != 13; nb++) {
        if (my_commands[nb].name == cmd)
            break;
    }
    return (nb);
}

pos_t checkPos(pos_t pos, pos_t sizeMap)
{
    if (pos.x < 0)
        pos.x = sizeMap.x + (pos.x);
    else if (pos.x >= sizeMap.x) {
        pos.x = 0 + (pos.x - sizeMap.x);
    }
    if (pos.y < 0)
        pos.y = sizeMap.y + (pos.y);
    else if (pos.y >= sizeMap.y)
        pos.y = 0 + (pos.y - sizeMap.y);
    return (pos);
}

std::vector<std::string> cast_av(char **av)
{
    std::vector<std::string> tmp;

    for (int i = 0; av[i] != NULL; i++) {
        tmp.push_back(av[i]);
    }
    return (tmp);
}

std::vector<std::string> my_str_to_vector(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string number;

    while(std::getline(ss, number, delim)) {
        elems.push_back(number);
    }
    return elems;
}
