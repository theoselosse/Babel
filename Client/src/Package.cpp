/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** Package
*/

#include "../include/Client.hpp"
#include "../include/Functions.hpp"
#include "../include/Package.hpp"
#include "../include/Error.hpp"

int Client::check_packages(char *cmd)
{
    //std::cout << "retour du server: '" << cmd << "'" << std::endl;
    if (cmd[0] == AUDIO) {
        Functions::Audio(cmd[1], &cmd[5], this);
    }
    else if (cmd[0] == COMMUNICATION) {
        Functions::Communication(cmd[1], cmd, this);
    }
    else if (cmd[0] == ERROR) {
        Functions::Error(cmd[1], error_val);
    }
    return 1;
}

void Functions::Audio(unsigned int action, char *cmd, Client *c)
{
    switch (action) {
        case Audio_t::CALL_OK:
            call(cmd, c);
            break;
        case Audio_t::HANG_UP_OK:
            hangup(cmd, c);
            break;
        case Audio_t::RECEIVING_CALL_OK:
            receive_call(cmd, c);
            break;
        case Audio_t::ACCEPTED:
            accept_call(cmd, c);
            break;
    }
}

void Functions::Communication(unsigned int action, char *cmd, Client *c)
{
    switch (action) {
        case Communication_t::LOGIN_OK:
            login(cmd);
            break;
        case Communication_t::LOGOUT_OK:
            logout(cmd, c);
            break;
        case Communication_t::ADD_FRIEND_OK:
            add_friend(cmd);
            break;
        case Communication_t::REMOVE_FRIEND_OK:
            remove_friend(cmd);
            break;
    }
}

void Functions::Error(unsigned int action, std::vector<std::string> val)
{
    if (action > val.size())
        return;
    else
        display_error(val[action]);
}