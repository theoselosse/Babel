/*
** EPITECH PROJECT, 2021
** Dev
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <utility>
#include "Client.hpp"

class Server {
    public:
        Server();
        ~Server();

        void s_socket();

        void setup_network(int port);

        void s_close_socket(int);
        void s_close_client(int);
        void s_bind(int);
        void s_listen();
        void s_accept();

        void accept_client();
        void select_client();
        void add_to_list();
        void is_active();
        void remove_client();

        int check_packages(char *cmd);

        std::vector<Client> _clients;
        typedef void (*func_ptr)(unsigned char, char *, Server *s);
        std::map<unsigned char, func_ptr> type_func;
        int new_c;
        int current;
        int m_sock;
        int fd_server;
        int port;
        struct sockaddr_in addr;
        socklen_t addrlen;
        fd_set fd_read;

        std::pair<int, int> target; // fd / _waitingCall

    protected:
    private:
};

std::vector<unsigned char> intToBytes(int paramInt);

#endif /* !SERVER_HPP_ */
