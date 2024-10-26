#include <salamapper/top sort.hpp>
#include <salamapper/parse.hpp>

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

int main(){
    std::string format = "1:2,3;2:4;3:4;4:";
    std::unordered_map<std::string, std::vector<std::string>> g = Parse(format);
    std::vector<std::string> ordered = KahnTopSort(g);
    std::cout << "Topological order: ";
    for (const std::string& node: ordered){
        std::cout << node << " ";
    }
    std::cout << std::endl;
    return 0;
}
