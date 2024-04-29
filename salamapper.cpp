#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "TreeNode.h"
#include "rooter.h"
#include "parse.h"

void PrintTree(TreeNode* node, std::string& prefix, bool last = true, bool first = true) {
    if (node->parent != nullptr) {
        std::cout << prefix << (last ? "└─" : "├─") << node->id << std::endl;
    } else {
        std::cout << prefix << node->id << std::endl;
    }
    size_t original_length = prefix.length();
    first ? (prefix += last ? "" : "│  ") : (prefix += last ? "    " : "│  ");
    
    size_t children_count = node->children.size();
    for (size_t i = 0; i < children_count; i++) {
        PrintTree(node->children[i], prefix, i == children_count - 1, false);
    }
    prefix.erase(original_length);
}

int main(){
	std::string prefix = "";
	TreeNode* root = RootTree(Parse("1:2,3,5;2:3;3:4;4:;5:6,7;6:7;7:;"), "1");
	PrintTree(root, prefix);
	return 0;
}