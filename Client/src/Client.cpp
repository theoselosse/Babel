/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** client
*/

#include "../include/Client.hpp"
#include "../include/Package.hpp"
#include "../include/Functions.hpp"
#include <cstring>
#include <math.h>

static bool running;

Client::Client()
{
    error_val.push_back("NOT_LOGGED_IN");
    error_val.push_back("ALREADY_LOGGED_IN");
    error_val.push_back("USR_ALREADY_LOGGED_IN");
    error_val.push_back("INVALID_USERNAME");
    error_val.push_back("BUSY");
    error_val.push_back("SELF_CALLING");
    error_val.push_back("UNKNOWN_USR");
    error_val.push_back("ALREADY_FRIEND");
    error_val.push_back("TIMEOUT");
    error_val.push_back("DECLINED");
    error_val.push_back("TARGET_BUSY");
}

Client::~Client(){}

void Client::s_open()
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        throw Error("socket() error");
}

void Client::s_close_socket()
{
    if (close(fd) == -1)
        throw Error("close() error");
}

void Client::s_connect(int port, char *ip)
{
    socklen_t size;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    size = sizeof(struct sockaddr_in);
    if (connect(fd, (const struct sockaddr *) &sockaddr, size) == -1) {
        s_close_socket();
        throw Error("connect() error");
    }
}

bool parse_entry(char *buffer)
{
    char *end = NULL;
    int end_pos;

    end = strstr(buffer, "123TD");
    if (!end)
        return false;
    end_pos = strlen(buffer) - strlen(end);
    buffer[end_pos] = '\0';
    return true;
}

void Client::read_client()
{
    size_t size = 0;
    char buffer[5016];
    bool running = true;

    while (running) {
        if ((size = read(fd, buffer, 5016)) > 0) {
            buffer[size] = '\0';
            if (check_packages(buffer) == 1)
                write(0, buffer, strlen(buffer));
        }
        running = parse_entry(buffer);
    }
}

void Client::read_client_bis()
{
    size_t size = 0;
    char buffer[5016];
    bool running = true;

    while (running) {
        if ((size = read(_fds[0], buffer, 5016)) > 0) {
            buffer[size] = '\0';
            if (check_packages(buffer) == 1)
                write(0, buffer, strlen(buffer));
        }
        running = parse_entry(buffer);
    }
}

void Client::split_package(char b0, char b1, int size, char *buf)
{
    int nb_p = ceil(size / 120) + 1;
    int j = 0;
    unsigned char sz = 0;
    std::string cont;

    std::cout << "nb: " << nb_p << std::endl;
    for (int i = 0; i < nb_p; i++) {
        if (i + 1 == nb_p)
            sz = size % 120;
        else
            sz = 120;
        for (; j < (i + 1) * 120 && j < strlen(buf); j++) {
            cont += buf[j];
        }
        dprintf(fd, "%c%c%c%c%c%s\n", b0, b1, sz, i + 1, nb_p, cont.c_str());
        usleep(2500);
        cont.clear();
    }
}

bool Client::send_client()
{
    char buffer[204800];
    char b[3];
    size_t size = 0;
    int total_p = 0;
    unsigned char s = 0;

    memset(buffer, 0, 204800);
    if ((size = read(0, buffer, 204800)) > 0) {
        buffer[size] = '\0';
        if (strlen(buffer) <= 2)
            return true;
        for (int i = 0; i < 3; i++)
            b[i] = buffer[i] - '0';
        if (strlen(buffer) > 3) {
            total_p = strlen(buffer) - 3;
        }
        if (total_p <= 120) {
            s = total_p;
            std::string str(buffer);
            str.erase(0, 2);
            dprintf(fd, "%c%c%c%c%c%s\n", b[0], b[1], s, 1, 1, str.c_str());
        } else
            split_package(b[0], b[1], total_p, &buffer[2]);
        return true;
    }
    return false;
}

int Client::execute_action()
{
    if (FD_ISSET(STDIN_FILENO, &fd_read)) {
        return send_client();
    }
    else if (FD_ISSET(fd, &fd_read)) {
        read_client();
    }
    return true;
}

void handle_sigint(int sig)
{
    (void)sig;
    running = 0;
}

void Client::exec_client()
{
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    running = 1;

    while (running != 0) {
        if (calling) {
            std::cout << "STOP!\n";
            dprintf(fd, "%c%c%c%c%c", COMMUNICATION, CALL_ANSWER, 0, 1, 1);
            calling = false;
        }
        FD_ZERO(&fd_read);
        FD_SET(fd, &fd_read);
        FD_SET(STDIN_FILENO, &fd_read);
        if (select(fd + 1, &fd_read, NULL, NULL, NULL) == -1) {
            if (errno == EINTR)
                continue;
            else
                throw Error("select() error");
        }
        running = execute_action();
    }   
    exit(0);
}

void Client::setup_client(char *ip, int port)
{
    s_open();
    s_connect(port, ip);
}