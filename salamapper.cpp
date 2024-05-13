#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

#include <salamapper/TreeNode.hpp>
#include <salamapper/rooter.hpp>
#include <salamapper/parse.hpp>
#include <salamapper/print.hpp>

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

int main(int argc, char* argv[]){
	// if(argc == 1){
	// 	printf("missing map and root node\n");
	// }else if(argc == 2){
	// 	printf("missing root node\n");
	// }else if(argc >=3){
	// 	std::string prefix_first = "";
	// 	auto g = Parse(argv[1]);
	// 	TreeNode *root = RootTree(g, argv[2]);
	// 	PrintTree(root, prefix_first);
	// 	delete(root);
	// }
	switch(argc){
		case(1):
			printf("Error: missing map and root node\n");
		case(2):
			printf("Error: missing root node\n");
		default:
			std::string prefix_first = "";
			auto g = Parse(argv[1]);
			TreeNode *root = RootTree(g, argv[2]);
			PrintTree(root, prefix_first);
			delete(root);
	}
	return 0;
}
