#pragma once
#include "Graph.h"
#include "Using.h"

class SuperGraph : protected Graph
{
public:

	//input: graph
	void BuildSuperGraph(Graph& graph);//build the super graph of given graph
	SuperGraph(Graph& graph)
	{
		BuildSuperGraph(graph);
	}
	void printStats();
};