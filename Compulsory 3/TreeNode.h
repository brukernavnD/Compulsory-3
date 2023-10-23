#pragma once

#include <vector>

//TreeNode class for each node in a tree
class TreeNode
{
public:
	//data stored in the node
	int Data;

	//pointer to the parent node
	TreeNode* Parent = nullptr;

	//vector of pointers to the children nodes
	std::vector<TreeNode*> Children;

	//constructor
	explicit TreeNode(int InData, TreeNode* InParent = nullptr);
};
		
