#include <salamapper/salamapper.h>
#include <salamapper/parse.hpp>
#include <salamapper/print.hpp>
#include <salamapper/rooter.hpp>
#include <salamapper/TreeNode.hpp>
#include <salamapper/top sort.hpp>

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>

struct TreeHandle{
	TreeNode *root;
	std::unordered_map<std::string, std::vector<std::string>> graph;

	~TreeHandle(){delete root;};
};

TreeHandle* CreateTree(const char* format_string, const char* root_id, enum CycleHandling cycle_mode = CYCLE_ERROR){
	try
	{
		TreeHandle* handle = new TreeHandle();
		handle->graph = Parse(format_string);
		handle->root = RootTree(handle->graph, root_id, cycle_mode);
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
		handle->root = nullptr;
		delete(handle);
		handle = nullptr;
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

char* TopSortKahnHandle(const TreeHandle* handle){
	try
	{
		std::vector<std::string> TopOrder = KahnTopSort(handle->graph);
		std::string result_str;
		for (size_t i = 0; i < TopOrder.size(); i++){
			result_str += TopOrder[i];
			if (i < TopOrder.size() -1) result_str += ",";
		}
		char* result = new char[result_str.length() + 1];
		strcpy(result, result_str.c_str());
		return result;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

char* TopSortKahnString(const char* format_string){
	try{
		std::unordered_map<std::string, std::vector<std::string>> g = Parse(format_string);
		std::vector<std::string> TopOrder = KahnTopSort(g);
		std::string result_str;
		for (size_t i = 0; i < TopOrder.size(); i++){
			result_str += TopOrder[i];
			if (i < TopOrder.size() -1) result_str += ",";
		}
		char* result = new char[result_str.length() + 1];
		strcpy(result, result_str.c_str());
		return result;
	}
	catch(const std::exception& e){
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}
