#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <salamapper/parse.hpp>

/*! /brief Parses a formatted string into a map of string vectors

This function takes a string and parses it into an unordered map where each key is a string id and the corresponding value is the vector containing the string ids of its children

@param format A string containing the formmatted string to parse
	The expected format is 
	"ID1:child1,child2,...;ID2:child1,child2,..;"
	Example: "1:2,3,5;2:3;3:4;4:;5:6,7;6:7;7:;"

@return std::unordered_map<std::string, std::vector<std::string>>
	An unordered map where each key is a string id and the value is a vector of the id of its children as strings

@throws std::invalid_argument If the string is empty or does not contain a colon(:)
@throws std::invalid_argument If any id in the format string is empty
	Example: "1:2,3;:3;3:;" (missing id after 1's children have been declared)
				    ^ Mistake right here
@throws std::invalid_argument If a colon(:) is missing after an id
*/
std::unordered_map<std::string, std::vector<std::string>> Parse(const std::string& format) {
    std::unordered_map<std::string, std::vector<std::string>> g;
    std::istringstream ss(format);
    std::string token;
	if (format.empty() || format.find(":") == std::string::npos){
		throw std::invalid_argument("Invalid format string");
	}
    while (std::getline(ss, token, ';')) {
        std::istringstream ss_token(token);
        std::string id_str;
        if (!std::getline(ss_token, id_str, ':')){
			throw std::invalid_argument("Invalid format: missing colon");
		}
		if (id_str.empty()){
			throw std::invalid_argument("Invalid format: empty ID");
		}
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