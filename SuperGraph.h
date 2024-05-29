#pragma once
#include "Graph.h"
#include <iostream>
#include <stdlib.h>
#include "Using.h"


class SuperGraph : protected Graph {
protected:
	int* stronglyConnectedComponents;
	int* lastEdgeAdded;

	

public:
	static void BuildSuperGraph(Graph& graph);
	SuperGraph(Graph& graph)
	{
		BuildSuperGraph(graph);
	}
};