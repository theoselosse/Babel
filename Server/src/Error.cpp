/*
** EPITECH PROJECT, 2021
** Server
** File description:
** Error
*/

#include "../include/Error.hpp"

Error::Error(const std::string &msg)
{
    this->_msg = msg;
}

const char *Error::what(void) const noexcept
{
    return (this->_msg.c_str());
}