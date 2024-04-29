#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class TreeNode{
	public:
		std::string id;
		TreeNode* parent;
		std::vector<TreeNode*> children;

		//constructor
		TreeNode(const std::string& id, TreeNode* parent){}

		//destructor
		~TreeNode(){
			for(auto child : children){
				delete child;
			}
		}
};

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

void PrintTree(TreeNode* node){
	//print the tree to the standard output in a pactree style format
}

std::unordered_map<std::string, std::vector<std::string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"D", "E"}},
        {"C", {"F", "G"}},
        {"D", {}},
        {"E", {}},
        {"F", {}},
        {"G", {}}
    };

int main(){
	PrintTree(RootTree(graph, "A"));
	return 0;
}