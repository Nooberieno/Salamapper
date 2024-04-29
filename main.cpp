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
		TreeNode(const std::string& id, TreeNode* parent): id(id), parent(parent){}

		//destructor
		~TreeNode(){
			for(auto child : children){
				if(child != nullptr){
					delete child;
				}
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

void PrintTree(TreeNode* node, std::string& prefix, bool last = true){
	if(node->parent != nullptr){
		std::cout<< prefix << (last? "└─" : "├─") << node->id <<std::endl;
	}else{
		std::cout<< prefix << "    " << node->id <<std::endl;
	}
	prefix += last? "    " : "│  ";
	size_t children_count = node->children.size();
	for(size_t i = 0; i < children_count; i++){
		PrintTree(node->children[i], prefix, i == children_count - 1);
	}
}

std::unordered_map<std::string, std::vector<std::string>> g = {
        {"A", {"B", "C"}},
        {"B", {"D", "E"}},
        {"C", {"F", "G"}},
        {"D", {}},
        {"E", {}},
        {"F", {}},
        {"G", {}}
    };

int main(){
	std::string prefix = "";
	TreeNode* root = RootTree(g, "A");
	PrintTree(root, prefix);
	return 0;
}