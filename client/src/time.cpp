/*
** EPITECH PROJECT, 2019
** time.cpp
** File description:
** time.cpp
*/

#include "client.hpp"
#include "commands.hpp"
#include "zappy_ai.hpp"

int getTimeOfCommand(std::string cmd)
{
    size_t i = 0;

    for (i = 0; i != 13; i++) {
        if (cmd == my_commands[i].name)
        return (my_commands[i].time_limit);
    }
    return (-1);
}

int Client::updateFoodQuantity(std::string cmd)
{
    int timeCost = getTimeOfCommand(cmd);

    if (timeCost == -1)
        return (OK);
    _timeUnit += timeCost;
    if(_timeUnit >= 300) {
        _itineraire = "Inventory";
        _timeUnit -= 300;
        return (KO);
    }
    return (OK);
}
