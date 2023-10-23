#pragma once

#include "GraphEdge.h"
#include "GraphNode.h"

//class for graphs made of connected nodes
class Graph
{

public:

	//constructor
	Graph();

	//container for nodes
	std::vector<GraphNode*> Nodes;

	//container for edges
	std::vector<GraphEdge*> Edges;

	//access functions
	static int GetNodeData(const GraphNode* InNode);
	std::vector<GraphEdge*> GetNodeConnections(const GraphNode* InNode) const;

	//query functions
	int GetSize() const;
	bool IsEmpty() const;
	std::vector<GraphNode*> GetVertecies() const; //get nodes
	std::vector<GraphEdge*> GetEdges() const;


	//insertion functions
	GraphNode* AddNode(int Data);
	GraphNode* AddNodeAtRandom(int Data);
	GraphNode* AddNodeWithEdgesAtRandom(int Data);
	GraphEdge* AddEdge(GraphNode* From, GraphNode* To);
	GraphEdge* AddEdgeToRandom(GraphNode* From);

	//deletion functions
	void RemoveNode(GraphNode* Node);
	void RemoveEdge(GraphEdge* Edge);

	//traversal functions
	std::vector<GraphNode*> BreadthFirstSearch(GraphNode* Start, const GraphNode* End) const;
};

