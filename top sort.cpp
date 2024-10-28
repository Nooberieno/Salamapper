#include <salamapper/top sort.hpp>

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <algorithm>

/*!
@brief Preforms Kahn's topological sort algorithm in a directed rooted tree graph

This function implements Kahn's algorithm to topological sort the vertices/nodes of a directed graph
It returns the vertices/nodes in topological sort if the graph is a Directed Acyclic Graph(DAG) and throws an error if the graph contains cycles

@param g A const reference to an unordered map representation of the graph where each key is a string id and the value is a vector of the id's of its children as strings

@return std::vector<std::string> A vector of id's as string sorted in topological order

@throws std::invalid_argument If the graph contains a cycle

@note This function returns the topological order in a sink to source method, meaning that in the case of a rooted tree graph, the root comes last in the ordering rather then first
	Example: 
	@code
	Root
	├─Child1
	│  ├─GrandChild1
	│  └─GrandChild2
	└─Child2
	   └─GrandChild3
	@endcode
	returns Grandchild3 Child2 GrandChild2 GrandChild1 Child1 Root

@warning This function assumes that all vertices/nodes are reachable, unreachable vertices/node will not be included in the output
*/
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
