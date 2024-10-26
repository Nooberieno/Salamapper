#include <salamapper/top sort.hpp>

#include <stdexcept>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

std::vector<std::string> KahnTopSort(const std::unordered_map<std::string, std::vector<std::string>> &g){
    std::vector<std::string> result;
    std::unordered_map<std::string, int> in_degree;
    for (const std::pair<const std::basic_string<char>, std::vector<std::basic_string<char>>>& pair : g){
        in_degree[pair.first] = 0;
        for (const std::string& child : pair.second){
            if (in_degree.find(child) == in_degree.end()){
                in_degree[child] = 0;
            }
        }
    }
    for (const std::pair<const std::basic_string<char>, std::vector<std::basic_string<char>>>& pair : g){
        for (const std::string& child : pair.second){
            in_degree[child]++;
        }
    }
    std::queue<std::string> q;
    for (const struct std::pair<const std::basic_string<char>, int>& pair: in_degree){
        if (pair.second == 0){
            q.push(pair.first);
        }
    }
    while (!q.empty()){
        std::string current = q.front();
        q.pop();
        result.push_back(current);
        if (g.find(current) != g.end()){
            for (const std::string& neighbour : g.at(current)){
                in_degree[neighbour]--;
                if(in_degree[neighbour] == 0){
                    q.push(neighbour);
                }
            }
        }
    }
    if (result.size() != in_degree.size()){
        throw std::runtime_error("Graph contains cycle");
    }
    return result;
}
