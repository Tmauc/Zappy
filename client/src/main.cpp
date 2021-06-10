/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** main.cpp
*/

#include "client.hpp"

void print_usage(void)
{
    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine\n"
    << "\tport\tis the port number\n"
    << "\tname\tis the name of the team\n"
    << "\tmachine\tis the name of the machine; localhost by default\n" << std::endl;
}

int is_error(int ac, char **av)
{
    if (ac < 5) {
        print_usage();
        return (YES);
    }
    (void)av;
    return (NO);
}

void exit_error(std::string str)
{
    std::cout << "ERROR : " << str << std::endl;
    exit(84);
}

void startGame(Client client)
{
    std::string cmd;
    std::string response;

    while (response != "dead\n") {
        if ((cmd = client.getNextCmd()) != "Stun") {
            client.sendTo(cmd);
            std::cout << "CMD= " << cmd << std::endl;
            response = client.recevFrom();
            std::cout << "RES= " << response;
            client.command(get_nbrFunc(cmd), response, cmd);
            client.draw_map();
        }
        if (client.updateFoodQuantity(cmd) == KO) {
            client.sendTo(client.getItineraireValue());
            std::cout << "CMD= " << cmd << std::endl;
            response = client.recevFrom();
            std::cout << "RES= " << cmd;
            client.command(get_nbrFunc(client.getItineraireValue()),
            response, client.getItineraireValue());
        }
        std::cout << std::endl;
    }
}

void initialiseClient(int ac, char **av)
{
    std::string msg;

    srand(time(0));
    Client client(ac, av);
    client.connection();
    std::cout << client.recevFrom();
    client.sendTo(client.getTeamName() + "\n");
    msg = client.recevFrom();
    if (msg != "ko\n") {
        client.initialiseMap(msg);
        startGame(client);
    }
    close(client.getSocket());
}

int main(int ac, char **av)
{
    if (is_error(ac, av) == YES)
        exit_error("not the right arrguments");
    initialiseClient(ac, av);
    return (0);
}
