/*
** EPITECH PROJECT, 2021
** Server
** File description:
** Server
*/

#include <signal.h>
#include <strings.h>
#include "../include/Server.hpp"
#include "../include/Error.hpp"
#include "../include/Package.hpp"
#include "../include/Functions.hpp"

static bool running;

Server::Server()
{
    type_func[AUDIO] = Functions::Audio;
    type_func[COMMUNICATION] = Functions::Communication;
}

Server::~Server()
{}

void Server::s_socket()
{
    fd_server = socket(AF_INET, SOCK_STREAM, 0);
    m_sock = fd_server;
    if (fd_server == -1)
        throw Error("socket() error");
}

void Server::s_bind(int port)
{
    struct sockaddr_in addr;
    socklen_t size;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    size = sizeof(struct sockaddr_in);
    if (bind(fd_server, (const struct sockaddr *) &addr, size) == -1 || port <= 0) {
        s_close_socket(fd_server);
        throw Error("bind() error");
    }
    std::cout << "Use port " << port << " to connect" << std::endl;
}

void Server::s_listen()
{
    if (listen(fd_server, 10) != 0) {
        s_close_socket(fd_server);
        throw Error("listen() error");
    }
}

void Server::s_close_socket(int fd_socket)
{
    if (close(fd_socket) == -1) {
        throw Error("close() error");
    }
}

void Server::s_close_client(int fd_socket)
{
    unsigned char type = COMMUNICATION;
    unsigned char action = LOGOUT;

    dprintf(fd_socket, "%c%c%c%c%c", type, action, 0, 1, 1);
    s_close_socket(fd_socket);
}

void Server::s_accept()
{
    addrlen = sizeof(addr);
    char ip[16];

    if ((new_c = accept(fd_server,
        (struct sockaddr *) &addr, (socklen_t *) &addrlen)) < 0) {
        throw Error("accept() error\n");
    }
    bzero(&addr, sizeof(addr));
    getsockname(fd_server, (struct sockaddr *) &addr, &addrlen);
    inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));
    std::cout << ip << std::endl;
    std::cout << ntohs(addr.sin_port) << std::endl;
    std::cout << "New user joined with fd: " << new_c << " and ip: " << ip << std::endl;
}

void Server::add_to_list(void)
{
    Client c(new_c);
    _clients.push_back(c);
}

void Server::select_client(void)
{
    int activity;
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fd_read);
    FD_SET(fd_server, &fd_read);
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        current = (*it).getFd();
        if (current > 0)
            FD_SET(current, &fd_read);
        if (current > m_sock)
            m_sock = current;
    }
    activity = select(m_sock + 1, &fd_read, NULL, NULL, &tv);
    if (activity < 0) {
        if (errno == EINTR) {
            s_close_socket(fd_server);
            exit(0);
        }
        perror("select() error");
    }
}

void Server::remove_client()
{
    if (_clients.empty())
        return;
    for (auto it = _clients.begin(); it != _clients.end() && !_clients.empty(); it++) {
        if (!_clients.empty() && (*it).getFd() == current) {
            s_close_client((*it).getFd());
            _clients.erase(it);
            std::cout << "User with fd: "<< (*it).getFd() << " is leaving us :(\n"; 
            return;
        }
    }
}

void Server::is_active()
{
    int msg_size;
    char buffer[1025];

    for (auto i = _clients.begin(); i != _clients.end(); i++) {
        current = (*i).getFd();
        if (FD_ISSET(current, &fd_read)) {
            if ((msg_size = read(current, buffer, 1024)) == 0) {
                remove_client();
                return;
            } else {
                buffer[msg_size] = '\0';
                if (check_packages(buffer) == 0) {
                    write(fd_server, "500 Wrong command\r\n", 20);
                }
                else if ((*i).isQuitting() == true)
                    remove_client();
            }
        }
    }
}

void handle_sigint(int sig)
{
    (void)sig;
    running = 1;
}

void Server::accept_client(void)
{
    running = 0;
    signal(SIGINT, handle_sigint);
    while (running != 1) {
        
        select_client();
        if (FD_ISSET(fd_server, &fd_read)) {
            s_accept();
            add_to_list();
        }
        is_active();
    }
    if (_clients.size() > 0) {
        for (auto i = _clients.begin(); i != _clients.end(); i++) {
            s_close_client((*i).getFd());
        }
    }
}