#include <unordered_map>
#include <vector>
#include <string>

#include "TreeNode.h"
#include "rooter.h"

TreeNode* BuildTree(const std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent){
	for(const auto& child_id : g.at(node->id)){
		if(parent != nullptr && child_id == parent->id){
			continue;
		}
		TreeNode* child = new TreeNode(child_id, parent);
		node->children.push_back(child);
		BuildTree(g, child, node);
	}
	return node;
}

TreeNode* RootTree(const std::unordered_map<std::string, std::vector<std::string>>&g, const std::string& root_id){
	TreeNode* root = new TreeNode(root_id, nullptr);
	return BuildTree(g, root, nullptr);
}