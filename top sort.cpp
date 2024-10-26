#include <salamapper/top sort.hpp>

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <algorithm>

std::vector<std::string> KahnTopSort(const std::unordered_map<std::string, std::vector<std::string>> &g){
    std::unordered_map<std::string, int> in_degree;
    for (std::unordered_map<std::string, std::vector<std::string>>::const_iterator it = g.begin(); it != g.end(); it++){
        if(in_degree.find(it->first) == in_degree.end()){
            in_degree[it->first] = 0;
        }
        for (std::vector<std::string>::const_iterator to = it->second.begin(); to != it->second.end(); to++){
            in_degree[*to]++;
        }
    }
    std::queue<std::string> q;
    for (std::unordered_map<std::string, int>::const_iterator it = in_degree.begin(); it != in_degree.end(); it++){
        if (it->second == 0){
            q.push(it->first);
        }
    }
    std::vector<std::string> order;
    while (!q.empty()){
        std::string at = q.front();
        q.pop();
        order.push_back(at);

        if (g.find(at) != g.end()){
            for (std::vector<std::string>::const_iterator to = g.at(at).begin(); to != g.at(at).end(); to++){
                in_degree[*to]--;
                if (in_degree[*to] == 0){
                    q.push(*to);
                }
            }
        }
    }
    if (order.size() != in_degree.size()){
        throw std::invalid_argument("Graph is not acyclic detected a cycle");
    }
	std::reverse(order.begin(), order.end());
    return order;
}
