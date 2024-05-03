#ifndef ROOTER_H
#define ROOTER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <salamapper/TreeNode.h>

TreeNode* BuildTree(std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent);

TreeNode* RootTree(std::unordered_map<std::string, std::vector<std::string>>& g, const std::string& root_id);

#endif