/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** Package
*/

#ifndef PACKAGE_HPP_
#define PACKAGE_HPP_

#include <iostream>

typedef enum {
    AUDIO,
    COMMUNICATION,
    ERROR
}Type_t;

typedef enum {
    CALL,
    HANG_UP,
    RECEIVING_CALL,
    ACCEPTED,
    DECLINE_CALL,
    MUTE
}Audio_t;

typedef enum {
    LOGIN,
    LOGOUT,
    ADD_FRIEND,
    REMOVE_FRIEND,
    CALL_ANSWER
}Communication_t;

typedef enum {
    NOT_LOGGED_IN,
    ALREADY_LOGGED_IN,
    USR_ALREADY_LOGGED_IN,
    INVALID_USERNAME,
    BUSY,
    SELF_CALLING,
    UNKNOWN_USR,
    ALREADY_FRIEND,
    TIMEOUT,
    DECLINED
}Error_t;

#endif /* !PACKAGE_HPP_ */
