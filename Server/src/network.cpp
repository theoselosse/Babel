/*
** EPITECH PROJECT, 2021
** Server
** File description:
** network
*/

#include "../include/network.hpp"

void Server::setup_network(int port)
{
    s_socket();
    s_bind(port);
    s_listen();
}