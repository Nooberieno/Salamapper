#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>
#include <iostream>

#include <salamapper/TreeNode.hpp>
#include <salamapper/rooter.hpp>
#include <salamapper/parse.hpp>
#include <salamapper/salamapper.h>

/*!
@brief Builds a rooted tree graph recursively based on a graph, can check for cycles

This function recursively constructs a tree from an unordered map representation of a graph
It handles cycle detection and can be configured to respond to cycles in different ways

@param g An unordered map representation of the graph where each key is a string id and the value is a vector of the id of its children as strings
@param node Pointer to the current TreeNode being processed
@param parent Pointer to the parent of node (nullptr in case of the root node)
@param visited A set of strings containing all id's of nodes that have been visited in the graph, used for detecting cycles
@param cycle_mode Enum for determining how cycles should be handled, either CYCLE_ERROR, CYCLE_WARN or CYCLE_IGNORE (defaults to CYCLE_ERROR)

@par 
	- CYCLE_ERROR: Throws an exception when a cycle is detected.
	- CYCLE_WARN: Prints a warning to stderr and continues, skipping the cyclic edge.
	- CYCLE_IGNORE: Silently ignores cyclic edges and continues.

@warning When using CYCLE_IGNORE it is the callers responsibility to ensure the graph is acyclic, if it is not undefined behaviour can occur
@throws std::runtime_error when a cycle is detected and cycle_mode is set to CYCLE_ERROR

@return TreeNode* Pointer to the root of the constructed tree

@note This function modifies the input TreeNode structure and the visited set

@warning Memory is dynamically allocated for new TreeNodes. The caller is responsible for proper deallocation by calling delete on the pointer to the root node
@warning Memory is dynamically allocated for new TreeNodes, this function may allocate a significant amount of memory based on the size and structure of the input graph

@note It is not recommended to use this function on its own, use the RootTree function instead
@see RootTree

@see TreeNode
@see CycleHandling

*/
TreeNode* BuildTree(std::unordered_map<std::string, std::vector<std::string>>& g, TreeNode* node, TreeNode* parent, std::unordered_set<std::string>& visited, enum CycleHandling cycle_mode = CYCLE_ERROR){
	visited.insert(node->id);
    for (const std::string& child_id : g[node->id]){
            if (parent != nullptr && child_id == parent->id){
				if (std::find(g[child_id].begin(), g[child_id].end(), node->id) != g[child_id].end()){
					switch (cycle_mode)
					{
					case CYCLE_ERROR:
						throw std::runtime_error("Cycle detected, child node cannot also be parrent node: " + parent->id + " -> " + node->id + " -> " + child_id + " Results in infinite loop");
            		case CYCLE_WARN:
						std::cerr << "Warning, Cycle detected: child node cannot also be parrent node: " + parent->id + " -> " + node->id + " -> " + child_id + " Results in infinite loop";
						continue;
            		case CYCLE_IGNORE:
						continue;
					}
					}
                	
			continue; 
		}
		if (visited.find(child_id) != visited.end()){
			switch (cycle_mode)
			{
			case CYCLE_ERROR:
				throw std::runtime_error("Cycle detected at nodes: " + child_id + " & " + node->id);
			case CYCLE_WARN:
				std::cerr << "Warning, Cycle detected at nodes:" + child_id + " & " + node->id;
				continue;
			case CYCLE_IGNORE:
				continue;
			}
		}
        TreeNode* child = new TreeNode(child_id, node);
        node->children.push_back(child);
		std::unordered_set<std::string> path_visited = visited;
        BuildTree(g, child, node, path_visited, cycle_mode);
    }
    return node;
}

/*!
@brief Creates a rooted tree graph from a graph representation
This function initializes the tree construction process by creating a root node and then calling the BuildTree function to construct the rest of the tree

@param g An unordered map representation of the graph where each key is a string id and the value is a vector of the id of its children as strings
@param root_id the id to be used for the root node of the tree
@param cycle_mode Enum for determining how cycles should be handled, either CYCLE_ERROR, CYCLE_WARN or CYCLE_IGNORE (defaults to CYCLE_ERROR)

@par 
	- CYCLE_ERROR: Throws an exception when a cycle is detected.
	- CYCLE_WARN: Prints a warning to stderr and continues, skipping the cyclic edge.
	- CYCLE_IGNORE: Silently ignores cyclic edges and continues.

@warning When using CYCLE_IGNORE it is the callers responsibilty to ensure the graph is acyclic, if not undefined behaviour can occur

@return TreeNode* Pointer to the root of the constructed tree

@throws std::invalid_argument If the graph is empty
@throws std::invalid_argument If the specified root id was not found in the graph
@throws std::runtime_error If a cycle was detected and cycle_mode was set to CYCLE_ERROR (thrown by BuildTree)

@note This function allocates memory for the root TreeNode. The caller is responsible for properly deallocating the entire tree by calling delete on the pointer to the root node
@warning This function may allocate a significant amount of memory based on the size and structure of the input graph

@see TreeNode
@see CycleHandling
@see BuildTree
*/
TreeNode* RootTree(std::unordered_map<std::string, std::vector<std::string>>& g, const std::string& root_id, enum CycleHandling cycle_mode = CYCLE_ERROR){
	if (g.empty()){
		throw std::invalid_argument("Empty graph");
	}
	if (g.find(root_id) == g.end()){
		throw std::invalid_argument("Root ID not found in graph");
	}
    TreeNode* root = new TreeNode(root_id, nullptr);
	std::unordered_set<std::string> visited;
    return BuildTree(g, root, nullptr, visited, cycle_mode);
}