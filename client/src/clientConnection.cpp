/*
** EPITECH PROJECT, 2019
** clientConnection.cpp
** File description:
** clientConnection.cpp
*/

#include "client.hpp"

#define MAX 1000000

void Client::SaveNumIfSameLevel(std::string msg)
{
    std::string nbrTmp = "";
    int dirPlayer = 0;

    msg.erase(0, 8);
    nbrTmp = msg[0];
    try {
        dirPlayer = std::stoi(nbrTmp);
    } catch (std::exception &e) {
        _dirPlayer = _dirPlayer;
    }
    if ((msg.find("level")) != std::string::npos) {
        msg.erase(0, 9);
        nbrTmp = msg[0];
        try {
            if (std::stoi(nbrTmp) == _level && _map[_posClient.y][_posClient.x].getNbrPlayer() == 0) {
                _dirPlayer = dirPlayer;
                _canLUp = false;
            }
        } catch (std::exception &e) {
            _dirPlayer = _dirPlayer;
        }
    }
    if ((msg.find("Stop")) != std::string::npos) {
        _dirPlayer = 0;
    }
}

bool Client::checkRes(std::string msg)
{
    if ((msg.find("eject")) != std::string::npos) {
        return false;
    } else if ((msg.find("message")) != std::string::npos) {
        SaveNumIfSameLevel(msg);
        return false;
    } else if ((msg.find("Current level")) != std::string::npos) {
        _stun = false;
        _canLUp = false;
        _imFirst = false;
        _dirPlayer = 0;
        _level = std::stoi(msg.erase(0, 15));
        removeRes(_posClient, _lastnbForLevelUP);
        return true;
    } else if (msg == "Elevation underway\n") {
        _stun = true;
        std::cout << "I'M STUN!" << std::endl;
        return false;
    }
    return true;
}

std::string Client::recevFrom()
{
    char buff[MAX];
    std::string msg;

    bzero(buff, sizeof(buff));
    read(_sockfd, buff, sizeof(buff));
    msg = buff;
    while (checkRes(msg) != true) {
        bzero(buff, sizeof(buff));
        read(_sockfd, buff, sizeof(buff));
        msg = buff;
    }
    return (msg);
}

int Client::sendTo(std::string msg)
{
    char cstr[msg.size() + 2];

    msg += '\n';
    strcpy(cstr, msg.c_str());
    write(_sockfd, cstr, strlen(cstr));
    return (0);
}

int Client::connection()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&_servaddr, sizeof(_servaddr));
    _servaddr.sin_family = AF_INET;
    _servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _servaddr.sin_port = htons(_port);
    if (connect(_sockfd, (SA*)&_servaddr, sizeof(_servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
    return (0);
}
