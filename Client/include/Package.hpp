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
    ERROR,
}Type_t;

typedef enum {
    CALL_OK,
    HANG_UP_OK,
    RECEIVING_CALL_OK,
    ACCEPTED,
    DECLINE_CALL,
    MUTE_OK
}Audio_t;

typedef enum {
    LOGIN_OK,
    LOGOUT_OK,
    ADD_FRIEND_OK,
    REMOVE_FRIEND_OK,
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
