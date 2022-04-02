/*
** EPITECH PROJECT, 2021
** Dev
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

class Client {
    public:
        Client(int fd);
        ~Client();

        std::string getUsername() const {return _username;};
        int getFd() const {return _fd;};
        bool isConnected() const {return _connected;};
        int isWaiting() const {return _waitingCall;};
        bool isQuitting() const {return _quitting;};
        bool isOnCall() const {return _onCall;};
        std::vector<std::string> getContacts() const {return _contacts;};

        void setConnected();
        void setWaitingCall(int);
        void setUsername(std::string);

    protected:
    private:
        std::string _username;
        int _fd;
        bool _connected;
        bool _onCall = false;
        bool _quitting;
        int _waitingCall = -1;

        char ip[16];

        std::vector<std::string>_contacts;
};

#endif /* !CLIENT_HPP_ */
