#ifndef PRINT_H
#define PRINT_H

#include <string>

#include <salamapper/TreeNode.h>

void PrintTree(TreeNode* node, std::string& prefix, bool last, bool first);

#endif