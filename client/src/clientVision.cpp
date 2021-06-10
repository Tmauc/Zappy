/*
** EPITECH PROJECT, 2019
** clientVision.cpp
** File description:
** clientVision.cpp
*/

#include "client.hpp"

pos_t Client::upVision(int nbr)
{
    pos_t objPos = {0, 0};

    if (nbr == 0) {
        objPos.y = _posClient.y;
        objPos.x = _posClient.x;
    } else if (nbr < 4) {
        objPos.y = _posClient.y + 1;
        if (nbr == 1)
            objPos.x = _posClient.x - 1;
        else if (nbr == 2)
            objPos.x = _posClient.x;
        else if (nbr == 3)
            objPos.x = _posClient.x + 1;
    } else if (nbr > 3 && nbr < 9) {
        objPos.y = _posClient.y + 2;
        if (nbr == 4)
            objPos.x = _posClient.x - 1;
        else if (nbr == 5)
            objPos.x = _posClient.x - 2;
        else if (nbr == 6)
            objPos.x = _posClient.x;
        else if (nbr == 7)
            objPos.x = _posClient.x + 1;
        else if (nbr == 8)
            objPos.x = _posClient.x + 2;
    } else if (nbr > 8 && nbr < 16) {
        objPos.y = _posClient.y + 3;
        if (nbr == 9)
            objPos.x = _posClient.x - 1;
        else if (nbr == 10)
            objPos.x = _posClient.x - 2;
        else if (nbr == 11)
            objPos.x = _posClient.x - 3;
        else if (nbr == 12)
            objPos.x = _posClient.x;
        else if (nbr == 13)
            objPos.x = _posClient.x + 1;
        else if (nbr == 14)
            objPos.x = _posClient.x + 2;
        else if (nbr == 15)
            objPos.x = _posClient.x + 3;
    }
    return (objPos);
}

pos_t Client::downVision(int nbr)
{
    pos_t objPos = {-1, 0};

    if (nbr == 0) {
        objPos.y = _posClient.y;
        objPos.x = _posClient.x;
    } else if (nbr < 4) {
        objPos.y = _posClient.y - 1;
        if (nbr == 1)
            objPos.x = _posClient.x + 1;
        else if (nbr == 2)
            objPos.x = _posClient.x;
        else if (nbr == 3)
            objPos.x = _posClient.x - 1;
    } else if (nbr > 3 && nbr < 9) {
        objPos.y = _posClient.y - 2;
        if (nbr == 4)
            objPos.x = _posClient.x + 1;
        else if (nbr == 5)
            objPos.x = _posClient.x + 2;
        else if (nbr == 6)
            objPos.x = _posClient.x;
        else if (nbr == 7)
            objPos.x = _posClient.x - 1;
        else if (nbr == 8)
            objPos.x = _posClient.x - 2;
    } else if (nbr > 8 && nbr < 16) {
        objPos.y = _posClient.y - 3;
        if (nbr == 9)
            objPos.x = _posClient.x + 1;
        else if (nbr == 10)
            objPos.x = _posClient.x + 2;
        else if (nbr == 11)
            objPos.x = _posClient.x + 3;
        else if (nbr == 12)
            objPos.x = _posClient.x;
        else if (nbr == 13)
            objPos.x = _posClient.x - 1;
        else if (nbr == 14)
            objPos.x = _posClient.x - 2;
        else if (nbr == 15)
            objPos.x = _posClient.x - 3;
    }
    return (objPos);
}

pos_t Client::rightVision(int nbr)
{
    pos_t objPos = {0, 0};

    if (nbr == 0) {
        objPos.y = _posClient.y;
        objPos.x = _posClient.x;
    } else if (nbr < 4) {
        objPos.x = _posClient.x + 1;
        if (nbr == 1)
            objPos.y = _posClient.y + 1;
        else if (nbr == 2)
            objPos.y = _posClient.y;
        else if (nbr == 3)
            objPos.y = _posClient.y - 1;
    } else if (nbr > 3 && nbr < 9) {
        objPos.x = _posClient.x + 2;
        if (nbr == 4)
            objPos.y = _posClient.y + 1;
        else if (nbr == 5)
            objPos.y = _posClient.y + 2;
        else if (nbr == 6)
            objPos.y = _posClient.y;
        else if (nbr == 7)
            objPos.y = _posClient.y - 1;
        else if (nbr == 8)
            objPos.y = _posClient.y - 2;
    } else if (nbr > 8 && nbr < 16) {
        objPos.x = _posClient.x + 3;
        if (nbr == 9)
            objPos.y = _posClient.y + 1;
        else if (nbr == 10)
            objPos.y = _posClient.y + 2;
        else if (nbr == 11)
            objPos.y = _posClient.y + 3;
        else if (nbr == 12)
            objPos.y = _posClient.y;
        else if (nbr == 13)
            objPos.y = _posClient.y - 1;
        else if (nbr == 14)
            objPos.y = _posClient.y - 2;
        else if (nbr == 15)
            objPos.y = _posClient.y - 3;
    }
    return (objPos);
}

pos_t Client::leftVision(int nbr)
{
    pos_t objPos = {0, 0};

    if (nbr == 0) {
        objPos.y = _posClient.y;
        objPos.x = _posClient.x;
    } else if (nbr < 4) {
        objPos.x = _posClient.x - 1;
        if (nbr == 1)
            objPos.y = _posClient.y - 1;
        else if (nbr == 2)
            objPos.y = _posClient.y;
        else if (nbr == 3)
            objPos.y = _posClient.y + 1;
    } else if (nbr > 3 && nbr < 9) {
        objPos.x = _posClient.x - 2;
        if (nbr == 4)
            objPos.y = _posClient.y - 1;
        else if (nbr == 5)
            objPos.y = _posClient.y - 2;
        else if (nbr == 6)
            objPos.y = _posClient.y;
        else if (nbr == 7)
            objPos.y = _posClient.y + 1;
        else if (nbr == 8)
            objPos.y = _posClient.y + 2;
    } else if (nbr > 8 && nbr < 16) {
        objPos.x = _posClient.x - 3;
        if (nbr == 9)
            objPos.y = _posClient.y - 1;
        else if (nbr == 10)
            objPos.y = _posClient.y - 2;
        else if (nbr == 11)
            objPos.y = _posClient.y - 3;
        else if (nbr == 12)
            objPos.y = _posClient.y;
        else if (nbr == 13)
            objPos.y = _posClient.y + 1;
        else if (nbr == 14)
            objPos.y = _posClient.y + 2;
        else if (nbr == 15)
            objPos.y = _posClient.y + 3;
    }
    return (objPos);
}

void Client::renbRessourceMap(pos_t objPos)
{
    _map[objPos.y][objPos.x].setNbrFood(0);
    _map[objPos.y][objPos.x].setNbrLinemate(0);
    _map[objPos.y][objPos.x].setNbrDeraumere(0);
    _map[objPos.y][objPos.x].setNbrSibur(0);
    _map[objPos.y][objPos.x].setNbrMendiane(0);
    _map[objPos.y][objPos.x].setNbrPhiras(0);
    _map[objPos.y][objPos.x].setNbrThystame(0);
    _map[objPos.y][objPos.x].setNbrPlayer(0);
}

void Client::nbRessourceMap(pos_t objPos, std::vector<std::string> tmp)
{
    for (size_t i = 0; i != tmp.size(); i++) {
        if (tmp[i] == "food")
            _map[objPos.y][objPos.x].setNbrFood(_map[objPos.y][objPos.x].getNbrFood() + 1);
        else if (tmp[i] == "linemate")
            _map[objPos.y][objPos.x].setNbrLinemate(_map[objPos.y][objPos.x].getNbrLinemate() + 1);
        else if (tmp[i] == "deraumere")
            _map[objPos.y][objPos.x].setNbrDeraumere(_map[objPos.y][objPos.x].getNbrDeraumere() + 1);
        else if (tmp[i] == "sibur")
            _map[objPos.y][objPos.x].setNbrSibur(_map[objPos.y][objPos.x].getNbrSibur() + 1);
        else if (tmp[i] == "mendiane")
            _map[objPos.y][objPos.x].setNbrMendiane(_map[objPos.y][objPos.x].getNbrMendiane() + 1);
        else if (tmp[i] == "phiras")
            _map[objPos.y][objPos.x].setNbrPhiras(_map[objPos.y][objPos.x].getNbrPhiras() + 1);
        else if (tmp[i] == "thystame")
            _map[objPos.y][objPos.x].setNbrThystame(_map[objPos.y][objPos.x].getNbrThystame() + 1);
        else if (tmp[i] == "player")
            _map[objPos.y][objPos.x].setNbrPlayer(_map[objPos.y][objPos.x].getNbrPlayer() + 1);
    }
}

int Client::vision(std::string str, int nbr)
{
    pos_t objPos = {0, 0};
    std::vector<std::string> tmp;

    if (this->_orientation == UP)
        objPos = upVision(nbr);
    else if (this->_orientation == DOWN)
        objPos = downVision(nbr);
    else if (this->_orientation == RIGHT)
        objPos = rightVision(nbr);
    else if (this->_orientation == LEFT)
        objPos = leftVision(nbr);
    else
        return (KO);
    objPos = checkPos(objPos, _mapSize);
    if (str[0] == ' ')
        str.erase(0, 1);
    if (nbr == 0) {
        str.erase(0, 7);
    }
    tmp = my_str_to_vector(str, ' ');
    renbRessourceMap(objPos);
    nbRessourceMap(objPos, tmp);
    return (OK);
}
