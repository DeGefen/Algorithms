#pragma once
#include "Graph.h"
#include <iostream>
#include <stdlib.h>


class SuperGraph : protected Graph {
protected:
	int* stronglyConnectedComponents;
	int* lastEdgeAdded;


public:
	SuperGraph()
	{
		stronglyConnectedComponents = new int(numOfVertices);
		lastEdgeAdded = new int(numOfVertices);
	}
};