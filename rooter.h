#ifndef ROOTER_H
#define ROOTER_H

#include <unordered_map>
#include <string>
#include <vector>

TreeNode* BuildTree(const std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent){}

TreeNode* RootTree(const std::unordered_map<std::string, std::vector<std::string>>&g, const std::string& root_id){}

#endif