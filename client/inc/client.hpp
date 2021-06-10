/*
** EPITECH PROJECT, 2019
** client.hpp
** File description:
** client.hpp
*/

#pragma once

#include "box.hpp"

class Client
{
private:
    std::string _itineraire;
    int _level = 1;
    int _timeUnit = 0;
    int _dirPlayer = 0;
    int _port;
    int _myCounter = 0;
    int _orientation;
    int _sockfd;
    int _nbrConnect = 0;
    int _nbrFoodNeed = 3;
    bool _koInc = false;
    bool _stun = false;
    bool _canLUp = false;
    bool _imFirst = false;
    s_pos _mapSize;
    s_pos _posClient;
    std::string _teamName;
    std::string _machineName;
    std::vector<int> _inventory;
    std::vector<int> _lastnbForLevelUP;
    std::vector<std::vector<Box>> _map;
    std::vector<std::string> _cmd;
    struct sockaddr_in _servaddr;

public:
    Client(int ac, char **av);
    ~Client(){};

    int command(int nb_func, std::string res, std::string msg);
    int Forward(void);
    int Right(void);
    int Left(void);
    int Look(std::string res);
    int Inventory(std::string res);
    int Broadcast_text(std::string msg);
    int Connect_nbr(std::string res);
    int Fork(void);
    int Eject(void);
    void removeObj(std::string msg);
    void addObj(std::string msg);
    int Take_object(std::string res, std::string msg);
    int Set_object(std::string res, std::string msg);
    int Incantation(std::string res);

    int getPort(void){return(this->_port);}
    int getSocket(void){return(this->_sockfd);}
    void get_arguments(size_t ac, std::vector<std::string> av);
    std::string getNextCmd();
    std::string getTeamName(void){return(this->_teamName);}
    std::string getMachineName(void){return(this->_machineName);}
    std::vector<int> getInventory(void){return(this->_inventory);}
    void setInventory(std::vector<int> my_inventory){this->_inventory = my_inventory;}
    std::string getItineraireValue(void) {return (_itineraire);}

    int connection();
    int sendTo(std::string msg);
    bool checkRes(std::string msg);
    std::string recevFrom();

    void initialiseMap(std::string msg);
    void draw_map();

    int vision(std::string str, int nbr);
    pos_t upVision(int nbr);
    pos_t downVision(int nbr);
    pos_t rightVision(int nbr);
    pos_t leftVision(int nbr);

    void nbRessourceMap(pos_t objPos, std::vector<std::string> tmp);
    void renbRessourceMap(pos_t objPos);

    bool checkFood(void);
    void checkNbrPlayer(void);
    int checkNbrResCase(s_pos pos, std::vector<int> nbForLevelUP);
    void removeRes(s_pos pos, std::vector<int> nbForLevelUP);
    void takeItemsIA(s_pos pos, std::vector<int> nbForLevelUP);
    void groupClient(void);
    void getItineraire(void);
    int check_1_2(void);
    int check_2_3(void);
    int check_3_4(void);
    int check_4_5(void);
    int check_5_6(void);
    int check_6_7(void);
    int check_7_8(void);
    s_pos FindLinemate();
    s_pos FindDeraumere();
    s_pos FindSibur();
    s_pos FindMendiane();
    s_pos FindPhiras();
    s_pos FindThystame();
    int MoveClient(s_pos);
    void SaveNumIfSameLevel(std::string msg);
    int updateFoodQuantity(std::string cmd);

};
