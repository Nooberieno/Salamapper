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
