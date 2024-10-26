#ifndef ROOTER_H
#define ROOTER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <salamapper/TreeNode.hpp>
#include <salamapper/salamapper.h>

TreeNode* BuildTree(std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent, enum CycleHandling cycle_mode);

TreeNode* RootTree(std::unordered_map<std::string, std::vector<std::string>>& g, const std::string& root_id, enum CycleHandling cycle_mode);

#endif