#include <string>
#include <vector>
#include <unordered_map>

#include <salamapper/TreeNode.h>
#include <salamapper/rooter.h>
#include <salamapper/parse.h>

TreeNode* BuildTree(std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent){
    for (const auto& child_id : g[node->id]){
            if(parent != nullptr && child_id == parent->id){
                continue;
            }
        TreeNode* child = new TreeNode(child_id, node);
        node->children.push_back(child);
        BuildTree(g, child, node);
    }
    return node;
}

TreeNode* RootTree(std::unordered_map<std::string, std::vector<std::string>>& g, const std::string& root_id){
    TreeNode* root = new TreeNode(root_id, nullptr);
    return BuildTree(g, root, nullptr);
}