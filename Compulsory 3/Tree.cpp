#include "Tree.h"
#include "TreeNode.h"
#include <queue>

/// <summary>
/// gets the root of the tree
/// </summary>
/// <returns></returns>
TreeNode* Tree::GetRoot() const
{
	return Root;
}

/// <summary>
/// gets a random node in the tree
/// </summary>
/// <returns></returns>
TreeNode* Tree::GetRandomNode() const
{
	//if the tree is empty, return null
	if (IsEmpty())
	{
		return nullptr;
	}

	//get all the nodes in the tree
	const std::vector<TreeNode*> Nodes = BreadthFirstSearch(GetRoot());

	//get a random node
	TreeNode* RandomNode = Nodes[rand() % Nodes.size()];

	//return the random node
	return RandomNode;
}

/// <summary>
/// gets the parent of the node
/// </summary>
/// <param name="InNode"></param>
/// <returns></returns>
TreeNode* Tree::GetParent(const TreeNode* InNode)
{
	return InNode->Parent;
}

/// <summary>
/// gets the children of the node
/// </summary>
/// <param name="InNode"></param>
/// <returns></returns>
std::vector<TreeNode*> Tree::GetChildren(TreeNode* InNode)
{
	return InNode->Children;
}

int Tree::GetSize() const
{
	//the size of the tree
	int Size = 0;

	//get all the nodes in the tree
	const std::vector<TreeNode*> Nodes = BreadthFirstSearch(GetRoot());

	//for each node in the tree
	for (const TreeNode* Node : Nodes)
	{
		//get the depth of the node
		const int Depth = GetDepth(Node);

		//check if the node's depth is greater than the size
		if (Depth > Size)
		{
			//set the size to the depth
			Size = Depth + 1;	
		}
	}

	//return the size
	return Size;
}


/// <summary>
/// gets the depth of the node
/// </summary>
/// <param name="InNode"></param>
/// <returns></returns>
int Tree::GetDepth(const TreeNode* InNode) const
{
	//if the node is the root, return 1
	if (IsRoot(InNode))
	{
		return 0;
	}

	//otherwise, return the depth of the parent + 1
	return GetDepth(GetParent(InNode)) + 1;
}

/// <summary>
/// gets whether the tree is empty or not
/// </summary>
/// <returns></returns>
bool Tree::IsEmpty() const
{
	return Root == nullptr;
}

/// <summary>
/// gets whether the node is the root or not
/// </summary>
/// <param name="InNode"></param>
/// <returns></returns>
bool Tree::IsRoot(const TreeNode* InNode) const
{
	return InNode == Root;
}

/// <summary>
/// gets whether the node has any children or not
/// </summary>
/// <param name="InNode"></param>
/// <returns></returns>
bool Tree::IsLeaf(const TreeNode* InNode)
{
	return InNode->Children.empty();
}

/// <summary>
/// adds a node to the tree
/// </summary>
/// <param name="Data"></param>
/// <param name="Parent"></param>
void Tree::Add(const int Data, TreeNode* Parent)
{
	//create a new node
	auto* NewNode = new TreeNode(Data, Parent);

	//check if the tree is empty
	if (IsEmpty())
	{
		//set the root to the new node
		Root = NewNode;
	}
	//check if the parent is not null
	else if (Parent != nullptr)
	{
		//add the new node to the parent's children
		Parent->Children.push_back(NewNode);

		//set the parent of the new node
		NewNode->Parent = Parent;
	}
	//otherwise, add the new node to the root's children
	else
	{
		//add the new node to the root's children
		Root->Children.push_back(NewNode);

		//set the parent of the new node
		NewNode->Parent = Root;
	}
}

/// <summary>
/// adds a node to a random node in the tree
/// </summary>
/// <param name="Data"></param>
void Tree::AddAtRandom(const int Data)
{
	//if the tree is empty, add the node to the root
	if (IsEmpty())
	{
		Add(Data);
	}

	//otherwise, add the node to a node
	else
	{
		//get a random node
		TreeNode* RandomNode = GetRandomNode();

		//add the node to the random node
		Add(Data, RandomNode);
	}
}

/// <summary>
/// deletes a node from the tree
/// </summary>
/// <param name="InNode"></param>
void Tree::DeleteNode(TreeNode* InNode)
{
	//if the node is the root, delete the tree
	if (IsRoot(InNode))
	{
		//delete the tree
		DeleteNodeHelper(InNode);

		//set the root to null
		Root = nullptr;
	}

	//otherwise, delete the node
	else
	{
		//get the parent of the node
		TreeNode* Parent = GetParent(InNode);

		//remove the node from the parent's children
		Parent->Children.erase(std::remove(Parent->Children.begin(), Parent->Children.end(), InNode), Parent->Children.end());

		//delete the node
		DeleteNodeHelper(InNode);
	}
}

std::vector<TreeNode*> Tree::BreadthFirstSearch(TreeNode* Start, const TreeNode* End)
{
	//create a queue for nodes to visit
	std::queue<TreeNode*> Queue;

	//create a vector for visited nodes
	std::vector<TreeNode*> Visited;

	//add the start node to the queue
	Queue.push(Start);

	//while the queue is not empty
	while (!Queue.empty())
	{
		//get the first node in the queue
		TreeNode* CurrentNode = Queue.front();

		//remove the node from the queue
		Queue.pop();

		//if the node has not been visited
		if (std::find(Visited.begin(), Visited.end(), CurrentNode) == Visited.end())
		{
			//add the node to visited
			Visited.push_back(CurrentNode);

			//if the node is the end node
			if (CurrentNode == End)
			{
				//return the visited nodes
				return Visited;
			}

			//add the adjacent nodes to the queue
			for (TreeNode* AdjacentNode : GetChildren(CurrentNode))
			{
				Queue.push(AdjacentNode);
			}
		}
	}

	//return the visited nodes
	return Visited;
}

/// <summary>
/// helper function for deleting a node with all of its children
/// </summary>
/// <param name="InNode"></param>
void Tree::DeleteNodeHelper(const TreeNode* InNode)
{
	//if the node is null, return
	if (InNode == nullptr)
	{
		return;
	}

	//delete the children of the node
	for (const TreeNode* Child : InNode->Children)
	{
		DeleteNodeHelper(Child);
	}

	//delete the node
	delete InNode;
}
