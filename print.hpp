#ifndef PRINT_H
#define PRINT_H

#include <string>

#include <salamapper/TreeNode.hpp>

void PrintTree(TreeNode* node, std::string& prefix, bool last, bool first);

#endif