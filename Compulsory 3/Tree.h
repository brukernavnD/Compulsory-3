#pragma once

#include <vector>

#include "TreeNode.h"

class Tree
{
public:

	//root node
	TreeNode* Root = nullptr;

	//Access functions
	TreeNode* GetRoot() const;
	TreeNode* GetRandomNode() const;
	static TreeNode* GetParent(const TreeNode* InNode);
	static std::vector<TreeNode*> GetChildren(TreeNode* InNode);

	//Query functions
	int GetSize() const;
	int GetDepth(const TreeNode* InNode) const;
	bool IsEmpty() const;
	bool IsRoot(const TreeNode* InNode) const;
	static bool IsLeaf(const TreeNode* InNode);

	//insertion functions
	void Add(int Data, TreeNode* Parent = nullptr);
	void AddAtRandom(int Data);

	//deletion functions
	void DeleteNode(TreeNode* InNode);

	//traversal functions
	static std::vector<TreeNode*> BreadthFirstSearch(TreeNode* Start, const TreeNode* End = nullptr);

private:

	//recursive helper functions
	static void DeleteNodeHelper(const TreeNode* InNode);
};

