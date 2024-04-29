#ifndef TREENODE_H
#define TREENODE_H

#include <vector>
#include <string>

class TreeNode{
	public:
		std::string id;
		TreeNode* parent;
		std::vector<TreeNode*> children;

	//constructor
	TreeNode(const std::string& id, TreeNode* parent): id(id), parent(parent) {}

	//destructor
	~TreeNode(){
		for (auto child : children){
			if(child != nullptr){
				delete child;
			}
		}
	}
};
#endif