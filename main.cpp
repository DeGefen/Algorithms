#include <iostream>
#include <stdlib.h>
#include "Graph.h"
#include "Using.h"
#include "SuperGraph.h"

int main() 
{
	int n, m;
	Edge* edges = Graph::GetInput(n, m);
	Graph myGraph(n, m);

	myGraph.Fill(edges, m);
	std::cout << std::endl;

	SuperGraph mySuperGraph(myGraph);

	mySuperGraph.printStats();

	return 0;
}