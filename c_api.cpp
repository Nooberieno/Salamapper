#include <salamapper/salamapper.h>
#include <salamapper/parse.hpp>
#include <salamapper/print.hpp>
#include <salamapper/rooter.hpp>
#include <salamapper/TreeNode.hpp>

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

struct TreeHandle{
	TreeNode *root;
	std::unordered_map<std::string, std::vector<std::string>> graph;
};

TreeHandle* CreateTree(const char* format_string, const char* root_id){
	try
	{
		TreeHandle* handle = new TreeHandle();
		handle->graph = Parse(format_string);
		handle->root = RootTree(handle->graph, root_id);
		return handle;
	}
	catch(const std::exception &e)
	{
		std::cerr << "Error creating tree: " << e.what() << std::endl;
		return nullptr;
	}
	catch(...)
	{
		return nullptr;
	}
	
}

void ClearTree(TreeHandle* handle){
	if (handle){
		delete(handle->root);
		delete(handle);
	}
}

char* GetTree(TreeHandle* handle){
	if (!handle || !handle->root) return nullptr;

	try
	{
		std::string prefix;
		std::stringstream ss;
		std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
		PrintTree(handle->root, prefix, true, true);
		std::cout.rdbuf(old);
		std::string result = ss.str();
		char* c_str = new char[result.length() + 1];
		strcpy(c_str, result.c_str());
		return c_str;
	}
	catch(...)
	{
		return nullptr;
	}
	
}

void FreeString(char* str){
	delete[] str;
}