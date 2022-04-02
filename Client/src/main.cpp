/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** main
*/

#include "../include/Error.hpp"
#include "../include/Client.hpp"

bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();

    while (it != s.end() && std::isdigit(*it)) 
        it++;
    return !s.empty() && it == s.end();
}

void check_args(int ac, char **av)
{
    if (ac != 3)
        throw Error("Not the right number of arguments");
    if (!is_number(av[2]))
        throw Error("Port is not an appropriate value");
}

int main(int ac, char **av)
{
    Client client;

    try {
        check_args(ac, av);
        client.setup_client(av[1], atoi(av[2]));
        client.exec_client();
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 84;
    }
}