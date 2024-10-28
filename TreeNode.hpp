#ifndef TREENODE_H
#define TREENODE_H

#include <vector>
#include <string>

/*!
@class TreeNode
@brief Represents a node in a tree data structure

This class implements a node for a tree data structure, containing an id, a pointer to its parent and a vector of pointers to its children

@note this class implements a constructor and a destructor, the deconstructor recursively deletes all child nodes to avoid memory leaks
*/
class TreeNode{
	public:
		std::string id;
		TreeNode* parent;
		std::vector<TreeNode*> children;

	//constructor
	TreeNode(const std::string& id, TreeNode* parent): id(id), parent(parent) {}

	//destructor
	~TreeNode(){
		for (TreeNode* child : children){
			if(child != nullptr){
				delete child;
			}
		}
	}
};
#endif