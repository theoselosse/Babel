/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** Functions
*/

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <iostream>
#include "Server.hpp"


namespace Functions {
    void Audio(unsigned char, char *, Server *s);
    void Communication(unsigned char, char *, Server *s);
    void Error(unsigned char, char *, Server *s);
};

void call(Server *, char *, Client *);
void hangup(Server *, char *, Client *);
void accept_call(Server *, char *, Client *);
void decline_call(Server *, char *, Client *);

void login(Server *, char *, Client *);
void logout(Server *, char *, Client *);
void add_friend(Server *, char *, Client *);
void remove_friend(Server *, char *, Client *);
void call_answer(Server *server, char *cmd, Client *c);

#endif /* !FUNCTIONS_HPP_ */
