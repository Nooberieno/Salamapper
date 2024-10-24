#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>

#include <salamapper/TreeNode.hpp>
#include <salamapper/rooter.hpp>
#include <salamapper/parse.hpp>

TreeNode* BuildTree(std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent, std::unordered_set<std::string>& visited){
	visited.insert(node->id);
    for (const std::string& child_id : g[node->id]){
            if (parent != nullptr && child_id == parent->id){
				if (std::find(g[child_id].begin(), g[child_id].end(), node->id) != g[child_id].end()){
                	throw std::runtime_error("Cycle detected, child not cannot also be parrent: " + parent->id + " -> " + node->id + " -> " + child_id + " Results in infinite loop");
            }
			continue; 
		}
		if (visited.find(child_id) != visited.end()){
			throw std::runtime_error("Cycle detected at node: " + child_id);
		}
        TreeNode* child = new TreeNode(child_id, node);
        node->children.push_back(child);
        BuildTree(g, child, node, visited);
    }
    return node;
}

TreeNode* RootTree(std::unordered_map<std::string, std::vector<std::string>>& g, const std::string& root_id){
	if (g.empty()){
		throw std::invalid_argument("Empty graph");
	}
	if (g.find(root_id) == g.end()){
		throw std::invalid_argument("Root ID not found in graph");
	}
    TreeNode* root = new TreeNode(root_id, nullptr);
	std::unordered_set<std::string> visited;
    return BuildTree(g, root, nullptr, visited);
}