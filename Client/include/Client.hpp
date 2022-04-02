/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <future>
#include <thread>
#include <chrono>
#include "Error.hpp"

typedef void (*func_ptr)(unsigned int, std::string);

class Client {
    public:
        Client();
        ~Client();

        void setup_client(char *ip, int port);
        void s_open();
        void s_close_socket();
        void s_connect(int, char *);
        void exec_client();
        int execute_action();

        void read_client();
        void read_client_bis();
        bool send_client();

        int check_packages(char *cmd);
        void split_package(char b0, char b1, int size, char *buf);


        fd_set fd_read;
        int fd;
        int port;
        struct sockaddr_in sockaddr;
        bool connected = false;
        std::map<unsigned char, func_ptr> type_func;
        std::vector<std::string> error_val;

        std::vector<int> _fds;
        std::future_status status;
        bool calling = false;
    protected:
    private:
};

#endif /* !CLIENT_HPP_ */
