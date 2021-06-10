/*
** EPITECH PROJECT, 2019
** command.cpp
** File description:
** command.cpp
*/

#include "client.hpp"

int Client::Fork(void)
{
    return (0);
}

int Client::Eject(void)
{
    return (0);
}

int Client::Broadcast_text(std::string msg)
{
    msg.erase(0, 10);
    std::cout << "THE CLIENT SEND: " << msg << std::endl;
    return (0);
}

int Client::Forward(void)
{
    if(this->_orientation == UP) {
        (_posClient.y >= _mapSize.y - 1) ?
        _posClient.y = 0 : _posClient.y += 1;
    } else if (this->_orientation == DOWN) {
        (_posClient.y <= 0) ?
        _posClient.y = _mapSize.y - 1 : _posClient.y -= 1;
    } else if (this->_orientation == RIGHT) {
        (_posClient.x >= _mapSize.x - 1) ?
        _posClient.x = 0 : _posClient.x += 1;
    } else if (this->_orientation == LEFT) {
        (_posClient.x <= 0) ?
        _posClient.x = _mapSize.x - 1 : _posClient.x -= 1;
    } else
        return (KO);
    return (OK);
}

int Client::Right()
{
    if (_orientation == 13)
        _orientation = 10;
    else
        _orientation += 1;
    return (0);
}

int Client::Left()
{
    if (_orientation == 10)
        _orientation = 13;
    else
        _orientation -= 1;
    return (0);
}

int Client::Look(std::string res)
{
    std::vector<std::string> tmp;

    if (res == "ok\n" || res == "ko\n") {
        recevFrom();
        return (KO);
    }
    for (size_t i = 0; i < res.size(); i++)
        if (res[i] == '[' || res[i] == ']')
            res.erase(i, i + 1);
    res.erase(0, 1);
    tmp = my_str_to_vector(res, ',');
    for (size_t i = 0; i < tmp.size(); i++) {
        if (vision(tmp[i], i) == KO)
            return (KO);
    }
    return (OK);
}

int Client::Inventory(std::string res)
{
    std::vector<std::string> tmp;
    std::vector<std::string> tmp2;

    if (res[0] != '[')
        return (0);
    for (size_t i = 0; i < res.size(); i++)
        if (res[i] == '[' || res[i] == ']' || (i > 0 && res[i - 1] == ',' && res[i] == ' '))
            res.erase(i, 1);
    if (res[0] == ' ')
        res.erase(0, 1);
    tmp = my_str_to_vector(res, ',');
    for (size_t i = 0; i < tmp.size(); i++) {
        tmp2 = my_str_to_vector(tmp[i], ' ');
        try {
            this->_inventory[i] = std::stoi(tmp2[1]);
        } catch (std::exception &e) {
            continue;
        }
    }
    return (0);
}

int Client::Connect_nbr(std::string res)
{
    std::string tmp = "";

    for (size_t i = 0; res[i] != '\n' && res[i] != '\0'; i++)
        tmp += res[i];
    _nbrConnect = std::stoi(tmp);
    return (0);
}

void Client::removeObj(std::string msg)
{
    if (msg == "food" && _map[_posClient.y][_posClient.x].getNbrFood() > 0) {
        _inventory[0] += 1;
        _map[_posClient.y][_posClient.x].setNbrFood(_map[_posClient.y][_posClient.x].getNbrFood() - 1);
    } else if (msg == "linemate" && _map[_posClient.y][_posClient.x].getNbrLinemate() > 0) {
        _inventory[1] += 1;
        _map[_posClient.y][_posClient.x].setNbrLinemate(_map[_posClient.y][_posClient.x].getNbrLinemate() - 1);
    } else if (msg == "deraumere" && _map[_posClient.y][_posClient.x].getNbrDeraumere() > 0) {
        _inventory[2] += 1;
        _map[_posClient.y][_posClient.x].setNbrDeraumere(_map[_posClient.y][_posClient.x].getNbrDeraumere() - 1);
    } else if (msg == "sibur" && _map[_posClient.y][_posClient.x].getNbrSibur() > 0) {
        _inventory[3] += 1;
        _map[_posClient.y][_posClient.x].setNbrSibur(_map[_posClient.y][_posClient.x].getNbrSibur() - 1);
    } else if (msg == "mendiane" && _map[_posClient.y][_posClient.x].getNbrMendiane() > 0) {
        _inventory[4] += 1;
        _map[_posClient.y][_posClient.x].setNbrMendiane(_map[_posClient.y][_posClient.x].getNbrMendiane() - 1);
    } else if (msg == "phiras" && _map[_posClient.y][_posClient.x].getNbrPhiras() > 0) {
        _inventory[5] += 1;
        _map[_posClient.y][_posClient.x].setNbrPhiras(_map[_posClient.y][_posClient.x].getNbrPhiras() - 1);
    } else if (msg == "thystame" && _map[_posClient.y][_posClient.x].getNbrThystame() > 0) {
        _inventory[6] += 1;
        _map[_posClient.y][_posClient.x].setNbrThystame(_map[_posClient.y][_posClient.x].getNbrThystame() - 1);
    }
}

int Client::Take_object(std::string res, std::string msg)
{
    std::string response;

    if (res == "ok\n") {
        _itineraire = "";
        _myCounter = 0;
        msg.erase(0, 5);
        removeObj(msg);
        std::cout << "THE CLIENT TAKE: " << msg << std::endl;
    } else if (res == "ko\n") {
        _koInc = true;
    }
    return (0);
}

void Client::addObj(std::string msg)
{
    if (msg == "food") {
        _inventory[0] -= 1;
        _map[_posClient.y][_posClient.x].setNbrFood(_map[_posClient.y][_posClient.x].getNbrFood() + 1);
    } else if (msg == "linemate") {
        _inventory[1] -= 1;
        _map[_posClient.y][_posClient.x].setNbrLinemate(_map[_posClient.y][_posClient.x].getNbrLinemate() + 1);
    } else if (msg == "deraumere") {
        _inventory[2] -= 1;
        _map[_posClient.y][_posClient.x].setNbrDeraumere(_map[_posClient.y][_posClient.x].getNbrDeraumere() + 1);
    } else if (msg == "sibur") {
        _inventory[3] -= 1;
        _map[_posClient.y][_posClient.x].setNbrSibur(_map[_posClient.y][_posClient.x].getNbrSibur() + 1);
    } else if (msg == "mendiane") {
        _inventory[4] -= 1;
        _map[_posClient.y][_posClient.x].setNbrMendiane(_map[_posClient.y][_posClient.x].getNbrMendiane() + 1);
    } else if (msg == "phiras") {
        _inventory[5] -= 1;
        _map[_posClient.y][_posClient.x].setNbrPhiras(_map[_posClient.y][_posClient.x].getNbrPhiras() + 1);
    } else if (msg == "thystame") {
        _inventory[6] -= 1;
        _map[_posClient.y][_posClient.x].setNbrThystame(_map[_posClient.y][_posClient.x].getNbrThystame() + 1);
    }
}

int Client::Set_object(std::string res, std::string msg)
{
    std::string stockCmd = msg;
    std::string response;

    if (res == "ok\n") {
        msg.erase(0, 4);
        addObj(msg);
        std::cout << "THE CLIENT SET: " << msg << std::endl;
    } else if (res == "ko\n") {
        sendTo("Inventory");
        response = recevFrom();
        command(get_nbrFunc("Inventory"), response, "Inventory");
    }
    while (res[0] == '[') {
        res = recevFrom();
        if (res[0] != '[') {
            std::cout << "RES= " << res << std::endl;
            command(get_nbrFunc(stockCmd), res, stockCmd);
        }
    }
    return (0);
}

int Client::Incantation(std::string res)
{
    if (res == "ko\n") {
        _koInc = true;
    }
    return (0);
}

int Client::command(int nb_func, std::string res, std::string msg)
{
    switch (nb_func) {
    case 0:
        Forward();
        break;
    case 1:
        Right();
        break;
    case 2:
        Left();
        break;
    case 3:
        Look(res);
        break;
    case 4:
        Inventory(res);
        break;
    case 5:
        Broadcast_text(msg);
        break;
    case 6:
        Connect_nbr(res);
        break;
    case 7:
        Fork();
        break;
    case 8:
        Eject();
        break;
    case 9:
        Take_object(res, msg);
        break;
    case 10:
        Set_object(res, msg);
        break;
    case 11:
        Incantation(res);
        break;
    default:
        printf("\nMauvais numéro de fonction.\n");
        break;
    }
    return 0;
}
