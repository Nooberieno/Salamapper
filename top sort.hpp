#ifndef TOPSORT_H
#define TOPSORT_H

#include <unordered_map>
#include <vector>
#include <string>

std::vector<std::string> KahnTopSort(const std::unordered_map<std::string, std::vector<std::string>>& g);

#endif
