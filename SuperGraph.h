#pragma once
#include "Graph.h"

class SuperGraph : public Graph
{
public:
	//input: graph
	void BuildSuperGraph(Graph& graph);//build the super graph of given graph
	SuperGraph(Graph& graph)
	{
		BuildSuperGraph(graph);
	}
};