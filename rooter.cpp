#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include <salamapper/TreeNode.hpp>
#include <salamapper/rooter.hpp>
#include <salamapper/parse.hpp>

TreeNode* BuildTree(std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent){
    for (const auto& child_id : g[node->id]){
            if(parent != nullptr && child_id == parent->id){
                continue;
            }
        TreeNode* child = new TreeNode(child_id, node);
        node->children.push_back(child);
        BuildTree(g, child, node);
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
    return BuildTree(g, root, nullptr);
}