#include "TreeNode.h"

/// <summary>
/// constructor
/// </summary>
/// <param name="InData"></param>
/// <param name="InParent"></param>
TreeNode::TreeNode(const int InData, TreeNode* InParent)
{
	//set the data
	Data = InData;

	//set the parent
	Parent = InParent;
}
