#include "Graph.h"

#include <queue>

/// <summary>
/// default constructor
/// </summary>
Graph::Graph() = default;

/// <summary>
/// gets the data of the node
/// </summary>
/// <param name="InNode"></param>
/// <returns></returns>
int Graph::GetNodeData(const GraphNode* InNode)
{
	return InNode->Data;
}

/// <summary>
/// gets the connections of the node
/// </summary>
/// <param name="InNode"></param>
/// <returns></returns>
std::vector<GraphEdge*> Graph::GetNodeConnections(const GraphNode* InNode) const
{
	//create a vector for the connections
	std::vector<GraphEdge*> Connections;

	//iterate through the edges
	for (GraphEdge* Edge : Edges)
	{
		//if the edge contains the node
		if (Edge->From == InNode || Edge->To == InNode)
		{
			//add the edge to the connections
			Connections.push_back(Edge);
		}
	}

	//return the connections
	return Connections;
}


/// <summary>
/// gets the size of the graph
/// </summary>
/// <returns></returns>
int Graph::GetSize() const
{
	return int(Nodes.size());
}

/// <summary>
/// gets whether the graph is empty
/// </summary>
/// <returns></returns>
bool Graph::IsEmpty() const
{
	return Nodes.empty();
}

/// <summary>
/// gets all the nodes in the graph
/// </summary>
/// <returns></returns>
std::vector<GraphNode*> Graph::GetVertecies() const
{
	return Nodes;
}

/// <summary>
/// gets all the connections in the graph
/// </summary>
/// <returns></returns>
std::vector<GraphEdge*> Graph::GetEdges() const
{
	return Edges;
}

/// <summary>
/// adds a node to the graph
/// </summary>
/// <param name="Data"></param>
/// <param name="Data"></param>
/// <returns></returns>
GraphNode* Graph::AddNode(const int Data)
{
	//create a new node
	auto* NewNode = new GraphNode(Data);

	//add the node to graph
	Nodes.push_back(NewNode);

	//return the node
	return NewNode;
}

/// <summary>
/// adds a node to the graph at a random location
/// </summary>
/// <param name="Data"></param>
/// <returns></returns>
GraphNode* Graph::AddNodeAtRandom(int Data)
{
	//create a new node
	auto* NewNode = new GraphNode(Data);

	//add the node to graph
	Nodes.push_back(NewNode);

	//get a random node
	GraphNode* RandomNode = Nodes[rand() % Nodes.size()];

	//add an edge between the new node and the random node
	AddEdge(RandomNode, NewNode);

	//return the node
	return NewNode;
}

/// <summary>
/// adds a node to the graph at a random location with random connections
/// </summary>
/// <param name="Data"></param>
/// <returns></returns>
GraphNode* Graph::AddNodeWithEdgesAtRandom(int Data)
{
	//create a new node
	auto* NewNode = new GraphNode(Data);

	//get a random number between 0 and the number of nodes
	const int NumberOfEdges = rand() % Nodes.size();

	//add that many edges between the new node and a random node
	for (int Index = 0; Index < NumberOfEdges; ++Index)
	{
		//add an edge between the new node and a random node
		AddEdgeToRandom(NewNode);
	}

	//add the node to graph
	Nodes.push_back(NewNode);

	//return the node
	return NewNode;
}

/// <summary>
/// adds a connection to the graph
/// </summary>
/// <param name="From"></param>
/// <param name="To"></param>
/// <returns></returns>
GraphEdge* Graph::AddEdge(GraphNode* From, GraphNode* To)
{
	//create a new edge
	auto* NewEdge = new GraphEdge(From, To);

	//add the edge to graph
	Edges.push_back(NewEdge);

	//return the edge
	return NewEdge;
}

/// <summary>
/// adds a connection to the graph at a random location
/// </summary>
/// <param name="From"></param>
/// <returns></returns>
GraphEdge* Graph::AddEdgeToRandom(GraphNode* From)
{
	//get a random node
	GraphNode* RandomNode = Nodes[rand() % Nodes.size()];

	//get a random number between 0 and 1
	const int RandomNumber = rand() % 2;

	//initialize the start and end nodes
	GraphNode* StartNode;
	GraphNode* EndNode;

	//set whether the random node is the from or to node
	if (RandomNumber == 0)
	{
		StartNode = From;
		EndNode = RandomNode;
	}
	else
	{
		StartNode = RandomNode;
		EndNode = From;
	}
	

	//create a new edge
	auto* NewEdge = new GraphEdge(StartNode, EndNode);

	//check if the edge already exists
	if (std::find(Edges.begin(), Edges.end(), NewEdge) != Edges.end())
	{
		//delete the edge
		delete NewEdge;

		//return the edge
		return NewEdge;
	}

	//add the edge to graph
	Edges.push_back(NewEdge);

	//return the edge
	return NewEdge;
}

/// <summary>
/// removes a node from the graph
/// </summary>
/// <param name="Node"></param>
void Graph::RemoveNode(GraphNode* Node)
{
	//remove the node from graph
	Nodes.erase(std::remove(Nodes.begin(), Nodes.end(), Node), Nodes.end());

	//remove all edges connected to the node
	for (GraphEdge* Edge : Edges)
	{
		if (Edge->From == Node || Edge->To == Node)
		{
			RemoveEdge(Edge);
		}
	}
}

/// <summary>
/// removes a connection from the graph
/// </summary>
/// <param name="Edge"></param>
void Graph::RemoveEdge(GraphEdge* Edge)
{
	//remove the edge from graph
	Edges.erase(std::remove(Edges.begin(), Edges.end(), Edge), Edges.end());
}

/// <summary>
/// gets all the nodes between the start and end nodes
/// </summary>
/// <param name="Start"></param>
/// <param name="End"></param>
/// <returns></returns>
std::vector<GraphNode*> Graph::BreadthFirstSearch(GraphNode* Start, const GraphNode* End) const
{
	//create a queue for nodes to visit
	std::queue<GraphNode*> Queue;

	//create a vector for visited nodes
	std::vector<GraphNode*> Visited;

	//add the start node to the queue
	Queue.push(Start);

	//while the queue is not empty
	while (!Queue.empty())
	{
		//get the first node in the queue
		GraphNode* CurrentNode = Queue.front();

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

			//iterate through the node's connections
			for (const GraphEdge* Connection : this->GetNodeConnections(CurrentNode))
			{
				//get which of the connection's nodes is not the current node
				GraphNode* AdjacentNode = Connection->From == CurrentNode ? Connection->To : Connection->From;

				//push the adjacent node to the queue
				Queue.push(AdjacentNode);
			}
		}
	}

	//return the visited nodes
	return Visited;
}
