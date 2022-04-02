/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** audio
*/

#include "../include/Package.hpp"
#include "../include/Server.hpp"

void call(Server *server, char *cmd, Client *c)
{
    if (c->isConnected() == false) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, NOT_LOGGED_IN, 0, 1, 1);
        return;
    }
    if (strlen(cmd) <= 2 || strlen(cmd) > 62) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, INVALID_USERNAME, 0, 1, 1);
        return;
    }
    std::string name(cmd);
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    if (name == "Guest") {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, INVALID_USERNAME, 0, 1, 1);
        return;
    }
    if (c->getUsername() == name) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, SELF_CALLING, 0, 1, 1);
            return;
    }
    for (auto it = server->_clients.begin(); it != server->_clients.end(); it++) {
        if ((*it).getUsername() == name) {
            if (!(*it).isOnCall()) {
                std::cout << "call -> " << (*it).getUsername() << std::endl;
                std::string content(c->getUsername());
                content += ">=<";
                content += std::to_string(c->getFd());

                std::string ct((*it).getUsername());
                ct += ">=<";
                ct += std::to_string((*it).getFd());

                dprintf(c->getFd(), "%c%c%zu%c%c%s", AUDIO, CALL, strlen(ct.c_str()), 1, 1, ct.c_str());
                server->target = std::make_pair((*it).getFd(), 0);
                dprintf((*it).getFd(), "%c%c%zu%c%c%s", AUDIO, RECEIVING_CALL, strlen(content.c_str()), 1, 1, content.c_str());
                return;
            } else {
                dprintf(c->getFd(), "%c%c%c%c%c", ERROR, BUSY, 0, 1, 1);
                return;
            }
        }
    }
    dprintf(c->getFd(), "%c%c%c%c%c", ERROR, UNKNOWN_USR, 0, 1, 1);
}

void hangup(Server *server, char *cmd, Client *c)
{
    if (c->isConnected() == false) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, NOT_LOGGED_IN, 0, 1, 1);
        return;
    }
}

void accept_call(Server *server, char *cmd, Client *c)
{
    if (c->isConnected() == false) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, NOT_LOGGED_IN, 0, 1, 1);
        return;
    }
    if (server->target.first == 0 && server->target.second == 0) {
        std::cout << "NOT QUEUED CALL" << std::endl;
        return;
    }
    server->target.second = 1;
}

void decline_call(Server *server, char *cmd, Client *c)
{
    if (c->isConnected() == false) {
        dprintf(c->getFd(), "%c%c%c%c%c", ERROR, NOT_LOGGED_IN, 0, 1, 1);
        return;
    }
    if (server->target.first == 0 && server->target.second == 0) {
        std::cout << "NOT QUEUED CALL" << std::endl;
        return;
    }
    server->target.second = 2;
}