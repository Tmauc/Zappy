/*
** EPITECH PROJECT, 2019
** box.hpp
** File description:
** box.hpp
*/

#pragma once

#include "zappy_ai.hpp"

class Box
{
    private:
        int _nbrPlayers = 0;
        int _nbrFood = 0;
        int _nbrLinemate = 0;
        int _nbrDeraumere = 0;
        int _nbrSibur = 0;
        int _nbrMendiane = 0;
        int _nbrPhiras = 0;
        int _nbrThystame = 0;
    public:
        Box(){};
        ~Box(){};
        int getNbrPlayer(void){return(this->_nbrPlayers);}
        int getNbrFood(void){return(this->_nbrFood);}
        int getNbrLinemate(void){return(this->_nbrLinemate);}
        int getNbrDeraumere(void){return(this->_nbrDeraumere);}
        int getNbrSibur(void){return(this->_nbrSibur);}
        int getNbrMendiane(void){return(this->_nbrMendiane);}
        int getNbrPhiras(void){return(this->_nbrPhiras);}
        int getNbrThystame(void){return(this->_nbrThystame);}
        void setNbrPlayer(int tmp){this->_nbrPlayers = tmp;}
        void setNbrFood(int tmp){this->_nbrFood = tmp;}
        void setNbrLinemate(int tmp){this->_nbrLinemate = tmp;}
        void setNbrDeraumere(int tmp){this->_nbrDeraumere = tmp;}
        void setNbrSibur(int tmp){this->_nbrSibur = tmp;}
        void setNbrMendiane(int tmp){this->_nbrMendiane = tmp;}
        void setNbrPhiras(int tmp){this->_nbrPhiras = tmp;}
        void setNbrThystame(int tmp){this->_nbrThystame = tmp;}
};

Box newBox();