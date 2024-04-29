#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

#include "parse.h"

std::unordered_map<std::string, std::vector<std::string>> Parse(const std::string& format){
	std::unordered_map<std::string, std::vector<std::string>> g;
    std::istringstream ss(format);
    std::string token;
    while (std::getline(ss, token, ';')) {
        std::istringstream ss_token(token);
        std::string id_str;
        std::getline(ss_token, id_str, ':');
        std::string children_str;
        std::getline(ss_token, children_str);
        std::istringstream ss_children(children_str);
        std::string child;
        while (std::getline(ss_children, child, ',')) {
            g[id_str].push_back(child);
        }
    }
    return g;
}