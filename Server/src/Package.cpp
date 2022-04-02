/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** Package
*/

#include "../include/Server.hpp"
#include "../include/Error.hpp"
#include "../include/Package.hpp"
#include "../include/Functions.hpp"


int Server::check_packages(char *cmd)
{
    if (cmd[0] == AUDIO) {
        Functions::Audio(cmd[1], cmd, this);
    }
    else if (cmd[0] == COMMUNICATION) {
        Functions::Communication(cmd[1], cmd, this);
    }
    return 1;
}

void Functions::Audio(unsigned char action, char *cmd, Server *s)
{
    std::vector<Client>::iterator c;

    for (auto it = s->_clients.begin(); it != s->_clients.end(); it++) {
        if ((*it).getFd() == s->current)
            c = it;
    }
    switch (action) {
        case Audio_t::CALL:
            call(s, &cmd[5], &(*c));
            break;
        case Audio_t::HANG_UP:
            hangup(s, cmd, &(*c));
            break;
        case Audio_t::ACCEPTED:
            accept_call(s, &cmd[5], &(*c));
            break;
        case Audio_t::DECLINE_CALL:
            decline_call(s, cmd, &(*c));
            break;
            
    }
}

void Functions::Communication(unsigned char action, char *cmd, Server *s)
{
    std::vector<Client>::iterator c;

    for (auto it = s->_clients.begin(); it != s->_clients.end(); it++) {
        if ((*it).getFd() == s->current)
            c = it;
    }
    switch (action) {
        case Communication_t::LOGIN:
            login(s, &cmd[5], &(*c));
            break;
        case Communication_t::LOGOUT:
            logout(s, cmd, &(*c));
            break;
        case Communication_t::ADD_FRIEND:
            add_friend(s, &cmd[5], &(*c));
            break;
        case Communication_t::REMOVE_FRIEND:
            remove_friend(s, &cmd[5], &(*c));
            break;
        case Communication_t::CALL_ANSWER:
            call_answer(s, cmd, &(*c));
            break;
    }
}