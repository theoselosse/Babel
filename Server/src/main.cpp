/*
** EPITECH PROJECT, 2021
** Server
** File description:
** main
*/

#include "../include/network.hpp"

bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();

    while (it != s.end() && std::isdigit(*it)) 
        it++;
    return !s.empty() && it == s.end();
}

void check_args(int ac, char **av)
{
    if (ac != 2)
        throw Error("Not the right number of arguments");
    if (!is_number(av[1]))
        throw Error("Port is not an appropriate value");
}

int main(int ac, char **av)
{
    Server server;
    char *buffer;

    try {
        check_args(ac, av);
        server.setup_network(atoi(av[1]));
        server.accept_client();
        server.s_close_socket(server.fd_server);
        return 0;
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 84;
    }
}