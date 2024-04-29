#include <string>
#include <vector>
#include <unordered_map>

#include <salamapper/TreeNode.h>
#include <salamapper/rooter.h>
#include <salamapper/parse.h>

TreeNode* BuildTree(const std::string& format, TreeNode* node, TreeNode* parent){
    auto g = Parse(format);
    for (const auto& child_id : g[node->id]){
            if(parent != nullptr && child_id == parent->id){
                continue;
            }
        TreeNode* child = new TreeNode(child_id, node);
        node->children.push_back(child);
        BuildTree(format, child, node);
    }
    return node;
}

TreeNode* RootTree(const std::string& format, const std::string& root_id){
    TreeNode* root = new TreeNode(root_id, nullptr);
    return BuildTree(format, root, nullptr);
}