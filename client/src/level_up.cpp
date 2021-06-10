/*
** EPITECH PROJECT, 2019
** level_up.cpp
** File description:
** level_up.cpp
*/

#include "client.hpp"
#include "zappy_ai.hpp"


s_pos Client::FindLinemate()
{
    s_pos pos = {0,0};

    for (pos.y = 0; pos.y < _mapSize.y ; pos.y++) {
        for (pos.x = 0; pos.x < _mapSize.x; pos.x++) {
            if (_map[pos.y][pos.x].getNbrLinemate() >= 1)
                return(pos);
        }
    }
    pos.x = -1;
    pos.y = -1;
    return (pos);
}

s_pos Client::FindDeraumere()
{
    s_pos pos = {0,0};

    for (pos.y = 0; pos.y < _mapSize.y ; pos.y++) {
        for (pos.x = 0; pos.x < _mapSize.x; pos.x++) {
            if (_map[pos.y][pos.x].getNbrDeraumere() >= 1)
                return(pos);
        }
    }
    pos.x = -1;
    pos.y = -1;
    return (pos);
}

s_pos Client::FindSibur()
{
    s_pos pos = {0,0};

    for (pos.y = 0; pos.y < _mapSize.y ; pos.y++) {
        for (pos.x = 0; pos.x < _mapSize.x; pos.x++) {
            if (_map[pos.y][pos.x].getNbrSibur() >= 1)
                return(pos);
        }
    }
    pos.x = -1;
    pos.y = -1;
    return (pos);
}

s_pos Client::FindMendiane()
{
    s_pos pos = {0,0};

    for (pos.y = 0; pos.y < _mapSize.y ; pos.y++) {
        for (pos.x = 0; pos.x < _mapSize.x; pos.x++) {
            if (_map[pos.y][pos.x].getNbrMendiane() >= 1)
                return(pos);
        }
    }
    pos.x = -1;
    pos.y = -1;
    return (pos);
}

s_pos Client::FindPhiras()
{
    s_pos pos = {0,0};

    for (pos.y = 0; pos.y < _mapSize.y ; pos.y++) {
        for (pos.x = 0; pos.x < _mapSize.x; pos.x++) {
            if (_map[pos.y][pos.x].getNbrPhiras() >= 1)
                return(pos);
        }
    }
    pos.x = -1;
    pos.y = -1;
    return (pos);
}

s_pos Client::FindThystame()
{
    s_pos pos = {0,0};

    for (pos.y = 0; pos.y < _mapSize.y ; pos.y++) {
        for (pos.x = 0; pos.x < _mapSize.x; pos.x++) {
            if (_map[pos.y][pos.x].getNbrThystame() >= 1)
                return(pos);
        }
    }
    pos.x = -1;
    pos.y = -1;
    return (pos);
}
