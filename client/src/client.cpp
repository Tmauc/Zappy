/*
** EPITECH PROJECT, 2019
** client.cpp
** File description:
** client.cpp
*/

#include "client.hpp"

Client::Client(int ac, char **av)
{
    _itineraire = "";
    _posClient = {9,4};
    _orientation = UP;
    std::vector<std::string> sav = cast_av(av);
    _machineName = "localhost";
    get_arguments(ac, sav);
    _inventory.push_back(10);
    for (int i = 1; i != 7; i++)
        _inventory.push_back(0);
}

void Client::get_arguments(size_t ac, std::vector<std::string> av)
{
    for (size_t i = 0; i != av.size(); i++) {
        if ((av[i].find("-p")) != std::string::npos && (i+1 <= ac)) {
            if (is_num(av[i + 1]) == YES)
                _port = std::stoi(av[i + 1]);
            else
                exit_error("port is supose to be a number");
            i++;
        } else if ((av[i].find("-n")) != std::string::npos && (i+1 <= ac)) {
            if (is_param(av[i + 1]) == YES)
                _teamName = av[i + 1];
            else
                exit_error("Please enter a team name");
            i++;
        } else if ((av[i].find("-h")) != std::string::npos && (i+1 <= ac)) {
            if (is_param(av[i + 1]) == YES)
                _machineName = av[i + 1];
            else
                exit_error("Please enter a machine name");
            i++;
        }
    }
}

int Client::MoveClient(s_pos pos)
{
    if (_posClient.y != pos.y && (_orientation == UP || _orientation == DOWN)) {
        _itineraire = "Forward";
        return (NO);
    } else if (_posClient.y != pos.y && (_orientation == LEFT || _orientation == RIGHT)) {
        _itineraire = "Right";
        return (NO);
    } else if (_posClient.x != pos.x && (_orientation == UP || _orientation == DOWN)) {
        _itineraire = "Right";
        return (NO);
    } else if (_posClient.x != pos.x && (_orientation == LEFT || _orientation == RIGHT)) {
        _itineraire = "Forward";
            return (NO);
    } else if ((_posClient.y == pos.y) && (_posClient.x == pos.x))
        return (YES);
    return (NO);
}

void Client::removeRes(s_pos pos, std::vector<int> nbForLevelUP)
{
    _map[pos.y][pos.x].setNbrLinemate(_map[pos.y][pos.x].getNbrLinemate() - nbForLevelUP[0]);
    _map[pos.y][pos.x].setNbrDeraumere(_map[pos.y][pos.x].getNbrDeraumere() - nbForLevelUP[1]);
    _map[pos.y][pos.x].setNbrSibur(_map[pos.y][pos.x].getNbrSibur() - nbForLevelUP[2]);
    _map[pos.y][pos.x].setNbrMendiane(_map[pos.y][pos.x].getNbrMendiane() - nbForLevelUP[3]);
    _map[pos.y][pos.x].setNbrPhiras(_map[pos.y][pos.x].getNbrPhiras() - nbForLevelUP[4]);
    _map[pos.y][pos.x].setNbrThystame(_map[pos.y][pos.x].getNbrThystame() - nbForLevelUP[5]);
}

int Client::checkNbrResCase(s_pos pos, std::vector<int> nbForLevelUP)
{
    if (_map[pos.y][pos.x].getNbrLinemate() < nbForLevelUP[0]) {
        if (_inventory[1] > 0)
            _itineraire = "Set linemate";
        else
            _canLUp = false;
        return (KO);
    } else if (_map[pos.y][pos.x].getNbrDeraumere() < nbForLevelUP[1]) {
        if (_inventory[2] > 0)
            _itineraire = "Set deraumere";
        else
            _canLUp = false;
        return (KO);
    } else if (_map[pos.y][pos.x].getNbrSibur() < nbForLevelUP[2]) {
        if (_inventory[3] > 0)
            _itineraire = "Set sibur";
        else
            _canLUp = false;
        return (KO);
    } else if (_map[pos.y][pos.x].getNbrMendiane() < nbForLevelUP[3]) {
        if (_inventory[4] > 0)
            _itineraire = "Set mendiane";
        else
            _canLUp = false;
        return (KO);
    } else if (_map[pos.y][pos.x].getNbrPhiras() < nbForLevelUP[4]) {
        if (_inventory[5] > 0)
            _itineraire = "Set phiras";
        else
            _canLUp = false;
        return (KO);
    } else if (_map[pos.y][pos.x].getNbrThystame() < nbForLevelUP[5]) {
        if (_inventory[6] > 0)
            _itineraire = "Set thystame";
        else
            _canLUp = false;
        return (KO);
    }
    if (_imFirst ==  false && _map[pos.y][pos.x].getNbrPlayer() == 0)
        _imFirst = true;
    if (_map[pos.y][pos.x].getNbrPlayer() != nbForLevelUP[6]) {
        _myCounter += 1;
        if (_myCounter % 2 == 0)
            _itineraire = "Look";
        else if (_imFirst == true)
            _itineraire = "Broadcast level " + std::to_string(_level);
        else
            _itineraire = "Broadcast I Wait" ;
        if (_map[pos.y][pos.x].getNbrPlayer() > nbForLevelUP[6] && _myCounter % 2 != 0)
            _itineraire = "Forward";
        return (KO);
    }
    return (OK);
}

void Client::takeItemsIA(s_pos pos, std::vector<int> nbForLevelUP)
{
    if (_map[pos.y][pos.x].getNbrFood() > 0) {
        _itineraire = "Take food";
        return;
    } else if (_map[pos.y][pos.x].getNbrLinemate() > nbForLevelUP[0]) {
        _itineraire = "Take linemate";
        return;
    } else if (_map[pos.y][pos.x].getNbrDeraumere() > nbForLevelUP[1]) {
        _itineraire = "Take deraumere";
        return;
    } else if (_map[pos.y][pos.x].getNbrSibur() > nbForLevelUP[2]) {
        _itineraire = "Take sibur";
        return;
    } else if (_map[pos.y][pos.x].getNbrMendiane() > nbForLevelUP[3]) {
        _itineraire = "Take mendiane";
        return;
    } else if (_map[pos.y][pos.x].getNbrPhiras() > nbForLevelUP[4]) {
        _itineraire = "Take phiras";
        return;
    } else if (_map[pos.y][pos.x].getNbrThystame() > nbForLevelUP[5]) {
        _itineraire = "Take thystame";
        return;
    }
    if (checkNbrResCase(pos, nbForLevelUP) == OK) {
        if (_koInc == true) {
            _itineraire = "Look";
            _koInc = false;
            return;
        } else {
            if (_imFirst == true)
                _itineraire = "Incantation";
            _lastnbForLevelUP = nbForLevelUP;
        }
    }
}

void Client::getItineraire()
{
    s_pos pos;

    if (_level == 1) {
        if (this->_inventory[1] < 1){
            pos = FindLinemate();
            if (pos.x == -1 && pos.y == -1) {
                _itineraire = "";
            } else if (MoveClient(pos) == YES) {
                takeItemsIA(pos, {1, 0, 0, 0, 0, 0, 0});
            }
        } else
            takeItemsIA(_posClient, {1, 0, 0, 0, 0, 0, 0});
    } else if (_level == 2) {
        if (_canLUp == true) {
            takeItemsIA(_posClient, {1, 1, 1, 0, 0, 0, 1});
            return;
        }
        if (this->_inventory[1] < 1) {
            std::cout << "Search linemate " << std::endl;
            pos = FindLinemate();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES) {
                    _itineraire = "Take linemate";
            }
        } else if (this->_inventory[2] < 1) {
            std::cout << "Search deraumere" << std::endl;
            pos = FindDeraumere();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES) {
                    _itineraire = "Take deraumere";
            }
        } else if (this->_inventory[3] < 1) {
            std::cout << "Search sibur" << std::endl;
            pos = FindSibur();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES) {
                    _itineraire = "Take sibur";
            }
        }
        if (this->_inventory[1] >= 1 && this->_inventory[2] >= 1 && this->_inventory[3] >= 1)
            _canLUp = true;
    } else if (_level == 3) {
        if (_canLUp == true) {
            takeItemsIA(_posClient, {2, 0, 1, 0, 2, 0, 1});
            return;
        }
        if (this->_inventory[1] < 2) {
            std::cout << "Search linemate " << std::endl;
            pos = FindLinemate();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take linemate";
        } else if (this->_inventory[3] < 1) {
            std::cout << "Search sibur " << std::endl;
            pos = FindSibur();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take sibur";
        } else if (this->_inventory[5] < 2) {
            std::cout << "Search phiras " << std::endl;
            pos = FindPhiras();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take phiras";
        }
        if (this->_inventory[1] >= 2 && this->_inventory[3] >= 1 && this->_inventory[5] >= 2)
            _canLUp = true;
    } else if (_level == 4) {
        if (_canLUp == true) {
            takeItemsIA(_posClient, {1, 1, 2, 0, 1, 0, 3});
            return;
        }
        if (this->_inventory[1] < 1){
            std::cout << "Search linemate " << std::endl;
            pos = FindLinemate();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take linemate";
        } else if (this->_inventory[2] < 1){
            std::cout << "Search deraumere " << std::endl;
            pos = FindDeraumere();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take deraumere";
        } else if (this->_inventory[3] < 2){
            std::cout << "Search sibur " << std::endl;
            pos = FindSibur();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take sibur";
        } else if (this->_inventory[5] < 1){
            std::cout << "Search phiras" << std::endl;
            pos = FindPhiras();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take phiras";
        }
        if (this->_inventory[1] >= 1 && this->_inventory[2] >= 1
            && this->_inventory[3] >= 2 && this->_inventory[5] >= 1)
            _canLUp = true;
    } else if (_level == 5) {
        if (_canLUp == true) {
            takeItemsIA(_posClient, {1, 2, 1, 3, 0, 0, 3});
            return;
        }
        if (this->_inventory[1] < 1) {
            std::cout << "Search linemate" << std::endl;
            pos = FindLinemate();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take linemate";
        } else if (this->_inventory[2] < 2){
            std::cout << "Search deraumere" << std::endl;
            pos = FindDeraumere();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take deraumere";
        } else if (this->_inventory[3] < 1){
            std::cout << "Search sibur" << std::endl;
            pos = FindSibur();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take sibur";
        } else if (this->_inventory[4] < 3){
            std::cout << "Search mendiane" << std::endl;
            pos = FindMendiane();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take mendiane";
        }
        if (this->_inventory[1] >= 1 && this->_inventory[2] >= 2
            && this->_inventory[3] >= 1 && this->_inventory[4] >= 3)
            _canLUp = true;
    } else if (_level == 6) {
        if (_canLUp == true) {
            takeItemsIA(_posClient, {1, 2, 3, 0, 1, 0, 5});
            return;
        }
        if (this->_inventory[1] < 1){
            pos = FindLinemate();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take linemate";
        } else if (this->_inventory[2] < 2){
            pos = FindDeraumere();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take deraumere";
        } else if (this->_inventory[3] < 3){
            pos = FindSibur();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take sibur";
        } else if (this->_inventory[5] < 1){
            pos = FindPhiras();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take phiras";
        }
        if (this->_inventory[1] >= 1 && this->_inventory[2] >= 2
            && this->_inventory[3] >= 3 && this->_inventory[5] >= 1)
            _canLUp = true;
    } else if (_level == 7) {
        if (_canLUp == true) {
            takeItemsIA(_posClient, {2, 2, 2, 2, 2, 1, 5});
            return;
        }
        if (this->_inventory[1] < 2){
            pos = FindLinemate();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take linemate";
        } else if (this->_inventory[2] < 2){
            pos = FindDeraumere();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take deraumere";
        } else if (this->_inventory[3] < 2){
            pos = FindSibur();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take sibur";
        } else if (this->_inventory[4] < 2){
            pos = FindMendiane();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take mendiane";
        } else if (this->_inventory[5] < 2){
            pos = FindPhiras();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take phiras";
        } else if (this->_inventory[6] < 1){
            pos = FindThystame();
            if (pos.x == -1 && pos.y == -1)
                _itineraire = "";
            else if (MoveClient(pos) == YES)
                _itineraire = "Take thystame";
        }
        if (this->_inventory[1] >= 2 && this->_inventory[2] >= 2
            && this->_inventory[3] >= 2 && this->_inventory[4] >= 2
            && this->_inventory[5] >= 2 && this->_inventory[6] >= 1)
            _canLUp = true;
    }
}

bool Client::checkFood(void)
{
    if (_inventory[0] < _nbrFoodNeed) {
        if (_canLUp == true) {
            _canLUp = false;
            _itineraire = "Broadcast Stop";
            return (KO);
        }
        if (_nbrFoodNeed == 3)
            _nbrFoodNeed += 4 + _level;
        _myCounter += 1;
        if (_myCounter % 2 == 0) {
            _itineraire = "Take food";
            return (KO);
        } else {
            int i = rand() % 2;
            (i == 0) ? _itineraire = "Forward" : _itineraire = "Left";
            return (KO);
        }
    }
    _nbrFoodNeed = 3;
    return (OK);
}

void Client::checkNbrPlayer(void)
{
    if (_level == 2 && _map[_posClient.y][_posClient.x].getNbrPlayer() >= 1)
        _itineraire = "Broadcast Stop";
    if (_level == 3 && _map[_posClient.y][_posClient.x].getNbrPlayer() >= 1)
        _itineraire = "Broadcast Stop";
    if (_level == 4 && _map[_posClient.y][_posClient.x].getNbrPlayer() >= 3)
        _itineraire = "Broadcast Stop";
    if (_level == 5 && _map[_posClient.y][_posClient.x].getNbrPlayer() >= 3)
        _itineraire = "Broadcast Stop";
    if (_level == 6 && _map[_posClient.y][_posClient.x].getNbrPlayer() >= 5)
        _itineraire = "Broadcast Stop";
    if (_level == 7 && _map[_posClient.y][_posClient.x].getNbrPlayer() >= 5)
        _itineraire = "Broadcast Stop";
}

void Client::groupClient(void)
{
    if (checkFood() == KO)
        return;
    if (_dirPlayer == 1 && _map[_posClient.y][_posClient.x].getNbrPlayer() >= 1) {
        _canLUp = true;
        _dirPlayer = 0;
        checkNbrPlayer();
        return;
    }
    if (_dirPlayer == 1 || _dirPlayer == 2 || _dirPlayer == 4 || _dirPlayer == 5 || _dirPlayer == 6 || _dirPlayer == 8)
        _itineraire = "Forward";
    else if (_dirPlayer == 3) {
        _itineraire = "Left";
    } else if ( _dirPlayer == 7) {
        _itineraire = "Right";
    }
    _myCounter += 1;
    if (_myCounter % 3 != 0)
        _itineraire = "Look";
}

std::string Client::getNextCmd(void)
{
    if (checkFood() == KO)
        return (_itineraire);
    if (_dirPlayer == 0)
        getItineraire();
    else
        groupClient();
    if (_itineraire == "") {
        _myCounter += 1;
        if (_myCounter % 2 == 0)
            return ("Forward");
        else
            return ("Look");
    } else {
        if (_koInc == true) {
            _koInc = false;
            return ("Look");
        } else
            return(_itineraire);
    }
}

void Client::initialiseMap(std::string msg)
{
    int i = 0;
    std::string nbr = "";
    std::string x = "";
    std::string y = "";

    for (; msg[i] != '\n' && msg[i] != '\0'; i++)
        nbr += msg[i];
    for(i++; msg[i] != ' ' && msg[i] != '\0'; i++)
        x += msg[i];
    for(i++; msg[i] != '\0'; i++)
        y += msg[i];
    _nbrConnect = std::stoi(nbr);
    _mapSize.x = std::stoi(x);
    _mapSize.y = std::stoi(y);
    for (int height = 0; height != _mapSize.y; height++) {
        std::vector<Box> tmp;
        _map.push_back(tmp);
        for (int width = 0; width != _mapSize.x; width++) {
            _map[height].push_back(newBox());
        }
    }
}

void Client::draw_map()
{
    std::cout << "INV= ";
    for (size_t i = 0; i != _inventory.size(); i++)
        std::cout << i << "= "<< _inventory[i] << " ";
    std::cout << std::endl;
    std::cout << "LEVEL= " << _level << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
}
/*
for (int y = 0; y != _mapSize.y; y++) {
    for (int x = 0; x != _mapSize.x; x++) {
        if (y == _posClient.y && x == _posClient.x) {
            std::cout << "|X" << _map[y][x].getNbrFood()
            << " " << _map[y][x].getNbrLinemate()
            << " " << _map[y][x].getNbrDeraumere()
            << " " << _map[y][x].getNbrSibur()
            << " " << _map[y][x].getNbrMendiane()
            << " " << _map[y][x].getNbrPhiras()
            << " " << _map[y][x].getNbrThystame()
            << " " << _map[y][x].getNbrPlayer()
             << "|";
        } else {
            std::cout << "|" << _map[y][x].getNbrFood()
            << " " << _map[y][x].getNbrLinemate()
            << " " << _map[y][x].getNbrDeraumere()
            << " " << _map[y][x].getNbrSibur()
            << " " << _map[y][x].getNbrMendiane()
            << " " << _map[y][x].getNbrPhiras()
            << " " << _map[y][x].getNbrThystame()
            << " " << _map[y][x].getNbrPlayer()
             << "|";
        }
    }
    std::cout << std::endl;
}
*/
