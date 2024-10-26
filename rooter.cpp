#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>
#include <iostream>

#include <salamapper/TreeNode.hpp>
#include <salamapper/rooter.hpp>
#include <salamapper/parse.hpp>
#include <salamapper/salamapper.h>


TreeNode* BuildTree(std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent, std::unordered_set<std::string>& visited, enum CycleHandling cycle_mode = CYCLE_ERROR){
	visited.insert(node->id);
    for (const std::string& child_id : g[node->id]){
            if (parent != nullptr && child_id == parent->id){
				if (std::find(g[child_id].begin(), g[child_id].end(), node->id) != g[child_id].end()){
					switch (cycle_mode)
					{
					case CYCLE_ERROR:
						throw std::runtime_error("Cycle detected, child node cannot also be parrent node: " + parent->id + " -> " + node->id + " -> " + child_id + " Results in infinite loop");
            		case CYCLE_WARN:
						std::cerr << "Warning, Cycle detected: child node cannot also be parrent node: " + parent->id + " -> " + node->id + " -> " + child_id + " Results in infinite loop";
						continue;
            		case CYCLE_IGNORE:
						continue;
					}
					}
                	
			continue; 
		}
		if (visited.find(child_id) != visited.end()){
			switch (cycle_mode)
			{
			case CYCLE_ERROR:
				throw std::runtime_error("Cycle detected at nodes: " + child_id + " & " + node->id);
			case CYCLE_WARN:
				std::cerr << "Warning, Cycle detected at nodes:" + child_id + " & " + node->id;
				continue;
			case CYCLE_IGNORE:
				continue;
			}
		}
        TreeNode* child = new TreeNode(child_id, node);
        node->children.push_back(child);
		std::unordered_set<std::string> path_visited = visited;
        BuildTree(g, child, node, path_visited, cycle_mode);
    }
    return node;
}

TreeNode* RootTree(std::unordered_map<std::string, std::vector<std::string>>& g, const std::string& root_id, enum CycleHandling cycle_mode = CYCLE_ERROR){
	if (g.empty()){
		throw std::invalid_argument("Empty graph");
	}
	if (g.find(root_id) == g.end()){
		throw std::invalid_argument("Root ID not found in graph");
	}
    TreeNode* root = new TreeNode(root_id, nullptr);
	std::unordered_set<std::string> visited;
    return BuildTree(g, root, nullptr, visited, cycle_mode);
}