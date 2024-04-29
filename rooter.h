#ifndef ROOTER_H
#define ROOTER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <salamapper/TreeNode.h>

TreeNode* BuildTree(const std::string& format, TreeNode* node, TreeNode* parent);

TreeNode* RootTree(const std::string& format, const std::string& root_id);

#endif