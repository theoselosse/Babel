/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** communication
*/

#include "../include/Package.hpp"
#include "../include/Server.hpp"

void login(Server *server, char *cmd, Client *c)
{
    std::string n(cmd);
    if (c->isConnected() == true) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, ALREADY_LOGGED_IN, 0, 1, 1);
        return;
    }
    if (strlen(cmd) <= 2 || strlen(cmd) > 62) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, INVALID_USERNAME, 0, 1, 1);
            return;
    }
    n.erase(std::remove(n.begin(), n.end(), '\n'), n.end());
    for (auto it = server->_clients.begin(); it != server->_clients.end(); it++) {
        if ((*it).getUsername() == n && (*it).isConnected()) {
            dprintf(c->getFd(), "%c%c%c%c%c", ERROR, USR_ALREADY_LOGGED_IN, 0, 1, 1);
            return;
        }
    }
    c->setConnected();
    c->setUsername(n);
    std::cout << c->getUsername() << " just joined" << std::endl;
    dprintf(c->getFd(), "%c%c%zu%c%c%s", COMMUNICATION, LOGIN, strlen(cmd), 1, 1, c->getUsername().c_str());
}

void logout(Server *server, char *cmd, Client *c)
{
    std::cout << "logout" << std::endl;
    dprintf(server->current, "%c%c%c%c%c\n", COMMUNICATION, LOGOUT, 0, 1, 1);
}

void add_friend(Server *server, char *cmd, Client *c)
{
    if (c->isConnected() == false) {
        dprintf(c->getFd(), "%c%c%c%c%c", 2, 0, 0, 1, 1);
        return;
    }
    if (strlen(cmd) <= 2 || strlen(cmd) > 62) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, INVALID_USERNAME, 0, 1, 1);
            return;
    }
    std::cout << "add_friend" << std::endl;
    dprintf(c->getFd(), "%c%c%c%c%c", 1, ADD_FRIEND, 0, 1, 1);
}

void remove_friend(Server *server, char *cmd, Client *c)
{
    if (c->isConnected() == false) {
        dprintf(c->getFd(), "%c%c%c%c%c", 2, 0, 0, 1, 1);
        return;
    }
    if (strlen(cmd) <= 2 || strlen(cmd) > 62) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, INVALID_USERNAME, 0, 1, 1);
            return;
    }
    std::cout << "remove_friend" << std::endl;
}

void call_answer(Server *server, char *cmd, Client *c)
{
    std::cout << "answer from pending call..." << std::endl;
    
    switch (server->target.second) {
    case 0:
        dprintf(server->current, "%c%c%c%c%c\n", ERROR, TIMEOUT, 0, 1, 1);
        break;
    case 1:
        dprintf(server->current, "%c%c%c%c%c\n", AUDIO, ACCEPTED, 0, 1, 1);
        break;
    case 2:
        dprintf(server->current, "%c%c%c%c%c\n", ERROR, DECLINED, 0, 1, 1);
        break;
    }
    server->target.first = 0;
    server->target.second = 0;
}