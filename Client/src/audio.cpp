/*
** EPITECH PROJECT, 2021
** B-CPP-500-LIL-5-1-babel-hugo.humez
** File description:
** audio
*/

#include "../include/Package.hpp"
#include "../include/Client.hpp"

void call(char *cmd, Client *c)
{
    std::cout << "CALL OK for: " << cmd << std::endl;

    std::string s(cmd);
    std::string delimiter = ">=<";
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
    }

    std::future<int> future = std::async(std::launch::async, [](){ 
        std::this_thread::sleep_for(std::chrono::seconds(10));
        return 10;
    });
    std::cout << "waiting... for answer\n";
    c->status = future.wait_for(std::chrono::seconds(10));
    c->calling = true;

}

void hangup(char *cmd, Client *c)
{
    std::cout << "HANGUP OK" << std::endl;
}

void receive_call(char *cmd, Client *c)
{
    std::cout << "RECEIVE CALL from: " << cmd << std::endl;
    std::cout << "TYPE 03 to accept or 04 to decline" << std::endl;
    std::string s(cmd);
    std::string delimiter = ">=<";
    size_t pos = 0;
    std::string token;


    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
    }
}

void accept_call(char *cmd, Client *c)
{
    std::cout << "ACCEPTED" << std::endl;
}

// CA  SERVER  CB

// CA 00CB √
//SERVER -> CA CALLOK √
//CA ENVOIE LA DEMANDE D'APPEL A CB  √
//CA SLEEP 10 Sec √
//CB -> CA ACCEPT / DECLINE √

//CA CRÉE LE SERVER
// CA -> CONNECTTOI

// CA 44 -> 