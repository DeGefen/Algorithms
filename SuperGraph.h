#pragma once
#include "Graph.h"
#include <iostream>
#include <stdlib.h>


class SuperGraph : protected Graph {
protected:
	int* stronglyConnectedComponents;
	int* lastEdgeAdded;

    void BuildSuperGraph(Graph &graph);

public:
	SuperGraph(Graph &graph)
	{
        BuildSuperGraph(graph);
	}
};