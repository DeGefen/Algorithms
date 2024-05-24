#include <iostream>
#include <stdlib.h>
#include "Graph.h"
#include <array>
#include "Using.h"

#define EXCEPTION 1


int main() {
	int n, m;
	Edge* edges = Graph::GetInput(n, m);

	Graph myGraph(n, m);
	myGraph.Fill(edges, m);
	myGraph.printGraph();

	return 0;
}