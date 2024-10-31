#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

#include <salamapper/TreeNode.hpp>
#include <salamapper/print.hpp>

/*!
@brief Prints a rooted tree structure in a hierarchical, ASCII-art style

This function recursively prints a tree structure, using certain Unicode symbols to represent the hierarchy and relationship between nodes

@param node Pointer to the current node being printed
@param prefix Reference to a string containing the current line prefix for formatting, for the best results initialize it as an empty string
@param last Boolean indicating wether the current node is the last child of its parent (defaults to true)
@param first Boolean indicating if this is the first call for the root node (defaults to true)

@note This function prints to the standard output directly and does not return a value

@par ASCII Art Representation:
	- Root nodes are printed without any prefix.
	- Non-root nodes use "└─" if they are the last child, or "├─" otherwise.
	- Vertical lines (│) are used to connect siblings visually.

@warning This function assumes that the TreeNode structure has been properly initialized and that circulair references do not exist in the tree

Example output:
@code
Root
├─Child1
│  ├─GrandChild1
│  └─GrandChild2
└─Child2
   └─GrandChild3
@endcode
@see TreeNode
@see CycleHandling
*/
void PrintTree(TreeNode* node, std::string& prefix, bool last = true, bool first = true){
	if(node->parent != nullptr){
		std::cout<< prefix << (last? "└─" : "├─") << node->id <<std::endl;
	}else{
		std::cout<< prefix << node->id << std::endl;
	}
	size_t original_length = prefix.length();
	first? (prefix += last? "" : "│  ") : (prefix += last? "    " : "│  ");
	
	size_t children_count = node->children.size();
	for(size_t i = 0; i < children_count; i++){
		PrintTree(node->children[i], prefix, i == children_count - 1, false);
	}
	prefix.erase(original_length);
}