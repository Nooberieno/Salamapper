#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "TreeNode.h"
#include "rooter.h"

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