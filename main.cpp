#include <iostream>
#include <stdlib.h>
#include "Graph.h"
#include <array>
#include "Using.h"
#include "SuperGraph.h"

#define EXCEPTION 1


int main() {
	int n, m;
	Edge* edges = Graph::GetInput(n, m);

	Graph myGraph(n, m);
	myGraph.Fill(edges, m);
	
	std::cout << std::endl;
	SuperGraph::BuildSuperGraph(myGraph);

	return 0;
}