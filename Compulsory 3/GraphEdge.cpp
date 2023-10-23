#include "GraphEdge.h"

/// <summary>
/// constructor
/// </summary>
/// <param name="Start"></param>
/// <param name="End"></param>
GraphEdge::GraphEdge(GraphNode* Start, GraphNode* End)
{
	From = Start;
	To = End;
}
