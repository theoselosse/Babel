/*
** EPITECH PROJECT, 2021
** Server
** File description:
** Client
*/

#include "../include/Client.hpp"

Client::Client(int fd)
{
    _fd = fd;
    _onCall = false;
    _connected = false;
    _username = "Guest";
}

Client::~Client(){}

void Client::setConnected()
{
    if (_connected == true)
        _connected = false;
    else
        _connected = true;
}

void Client::setWaitingCall(int v)
{
    _waitingCall = v;
}

void Client::setUsername(std::string name)
{
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    _username = std::string(name);
}