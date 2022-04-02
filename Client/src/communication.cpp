/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** communication
*/

#include "../include/Package.hpp"
#include "../include/Client.hpp"

void login(char *cmd)
{
    std::cout << "LOGIN OK" << std::endl;
}

void logout(char *cmd, Client *c)
{
    std::cout << "LOGOUT" << std::endl;
    //std::cout << (int)cmd[0] << std::endl;
    close(c->fd);
    exit(0);
}

void add_friend(char *cmd)
{
    std::cout << "add_friend" << std::endl;
}

void remove_friend(char *cmd)
{
    std::cout << "remove_friend" << std::endl;
}

void display_error(std::string error)
{
    std::cout << error << std::endl;
}

