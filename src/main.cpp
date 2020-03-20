/*
** EPITECH PROJECT, 2019
** Work
** File description:
** main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

std::vector<std::string> names;
std::vector<std::string> l1;
std::vector<std::string> l2;
std::vector<std::vector<std::string>> links;
std::vector<int> done;
std::vector<int> dat;

int nameId(std::string name)
{
    for (int i = 0; i < names.size(); i++)
        if (!names[i].compare(name))
            return (i);
    return (-1);
}

bool isDone(int id)
{
    for (int i = 0; i < done.size(); i++)
        if(done[i] == id)
            return (true);
    return (false);
}

void search(int id, std::string person, int val)
{
    std::vector<std::string> l = links[id];
    for (int i = 0; i < l.size(); i++) {
        if (!l[i].compare(person)) {
            dat.push_back(val + 1);
        }
    }
    for (int i = 0; i < l.size(); i++) {
        int _id = nameId(l[i]);
        if (!isDone(_id)) {
            done.push_back(_id);
            search(_id, person, val + 1);
        }
    }
}

bool validNb(std::string val)
{
    for (int i = 0; i < val.size(); i++)
        if(!(val[i] >= '0' && val[i] <= '9'))
            return (false);
    return (true);
}

bool nameExists(std::string name)
{
    for (int i = 0; i < names.size(); i++)
        if (names[i] == name)
            return (true);
    return (false);
}

int main(int ac, char **av)
{
    if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
        std::cout << "USAGE" << std::endl;
        std::cout << "\t" << av[0] << " file [n | p1 p2]" << std::endl;
        std::cout << "DESCRIPTION" << std::endl;
        std::cout << "\tfile\tfile that contains the list of Facebook connections" << std::endl;
        std::cout << "\tn\tmaximum length of the paths" << std::endl;
        std::cout << "\tpi\tname of someone in the file" << std::endl;
        return (0);
    }
    if (ac != 3 && ac != 4) {
        std::cerr << "Bad usage." << std::endl;
        return (84);
    }
    std::string line;
    std::ifstream infile(av[1]);
    std::string delim(" is friends with ");
    std::vector<std::string> data;
    while (std::getline(infile, line))
    {
        std::string d(line.c_str());
        data.push_back(d);
        if (line.find(delim) != std::string::npos) {
            size_t pos = 0;
            std::string token;
            while ((pos = line.find(delim)) != std::string::npos) {
                token = line.substr(0, pos);
                if (!nameExists(token)) {
                    names.push_back(token);
                    //std::cout << token << std::endl;
                }
                l1.push_back(token);
                line.erase(0, pos + delim.length());
            }
            if (!nameExists(line)) {
                names.push_back(line);
                //std::cout << line << std::endl;
            }
            l2.push_back(line);
        }
    }
    if (data.size() == 0) {
        std::cout << "error" << std::endl;
        return (84);
    }
    std::sort(names.begin(), names.end(), std::greater<std::string>());
    for (int y = 0; y < names.size(); y++) {
        std::vector<std::string> vec;
        //std::cout << names[y] << std::endl;
        for (int i = 0; i < l1.size() && i < l2.size(); i++) {
            if (names[y] == l1[i])
                vec.push_back(l2[i]);
            else if (names[y] == l2[i])
                vec.push_back(l1[i]);
        }
        links.push_back(vec);
    }
    if (ac == 3 && validNb(av[2])) {
        bool printed = false;
        for (int i = names.size() - 1; i >= 0; i--)
            std::cout << names[i] << std::endl;
        std::cout << std::endl;
        for (int x = links.size() - 1; x >= 0; x--) {
            for (int k = names.size() - 1; k >= 0; k--) {
                for (int y = links[x].size() - 1; y >= 0; y--) {
                    if (links[x][y].compare(names[k]) == 0) {
                        std::cout << "1";
                        if (k != 0)
                            std::cout << " ";
                        printed = true;
                        break;
                    }
                }
                if (!printed) {
                    std::cout << "0";
                    if (k != 0)
                        std::cout << " ";   
                }
                printed = false;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    } else if (ac == 4) {
        if (!strcmp(av[2], av[3])) {
            std::cout << "Degree of separation between " << av[2] << " and " << av[3] << ": " << std::to_string(0) << std::endl;
            return (0);
        }
        if (!nameExists(av[2]) || !nameExists(av[3])) {
            std::cout << "Degree of separation between " << av[2] << " and " << av[3] << ": -1" << std::endl;
            return (0);
        }
        int id = nameId(av[2]);
        done.push_back(id);
        search(id, av[3], -1);
        if (dat.size() == 0)
            std::cout << "Degree of separation between " << av[2] << " and " << av[3] << ": " << std::to_string(-1) << std::endl;
        else {
            int min = dat[0];
            for (int i = 0; i < dat.size(); i++)
                if (dat[i] < min)
                    min = dat[i];
            std::cout << "Degree of separation between " << av[2] << " and " << av[3] << ": " << std::to_string(min) << std::endl;
        }
    } else {
        std::cerr << "Bad usage." << std::endl;
        return (84);
    }
    return (0);
}