/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** Functions
*/

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <iostream>
#include <vector>
#include "Client.hpp"

namespace Functions {
    void Audio(unsigned int, char *, Client *);
    void Communication(unsigned int, char *, Client *);
    void Error(unsigned int, std::vector<std::string>);
};

    void call(char *cmd, Client *);
    void hangup(char *cmd, Client *);
    void receive_call(char *cmd, Client *c);
    void accept_call(char *cmd, Client *c);

    void login(char *);
    void logout(char *, Client *);
    void add_friend(char *);
    void remove_friend(char *);

    void display_error(std::string);


#endif /* !FUNCTIONS_HPP_ */
