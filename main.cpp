#include "SuperGraph.h"

int main() 
{
	int n, m;
	Edges edges = Graph::GetInput(n, m);
	Graph myGraph(n);
	myGraph.Fill(edges);
	SuperGraph mySuperGraph(myGraph);
    std::cout << std::endl;
	mySuperGraph.PrintInfo();

	return 0;
}