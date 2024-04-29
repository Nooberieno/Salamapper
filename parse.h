#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, std::vector<std::string>> Parse(const std::string& format);

#endif