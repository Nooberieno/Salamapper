#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#include <salamapper/TreeNode.hpp>
#include <salamapper/rooter.hpp>
#include <salamapper/parse.hpp>
#include <salamapper/print.hpp>

int main(int argc, char* argv[]){
	if(argc == 2){
		printf("missing root node");
	}else if(argc >=3){
		std::string prefix_first = "";
		std::unordered_map<std::string, std::vector<std::string>> g = Parse(argv[1]);
		TreeNode *root = RootTree(g, argv[2]);
		PrintTree(root, prefix_first, true, true);
		delete(root);
	}
	return 0;
}