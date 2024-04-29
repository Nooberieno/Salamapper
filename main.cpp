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
	//turn into rooted treegraph
}

TreeNode* RootTree(const std::unordered_map<std::string, std::vector<std::string>>&g, const std::string& root_id){
	TreeNode* root = new TreeNode(root_id, nullptr);
	return BuildTree(g, root, nullptr);
}