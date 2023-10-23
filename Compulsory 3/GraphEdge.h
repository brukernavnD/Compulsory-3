#pragma once

#include "GraphNode.h"

class GraphEdge
{
public:

	//a pointer to the node this edge starts from
	GraphNode* From;

	//a pointer to the node this edge leads to
	GraphNode* To;

	//constructor
	GraphEdge(GraphNode* Start, GraphNode* End);
};

