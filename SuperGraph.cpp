#include "SuperGraph.h"
#include "Using.h"

#define TRANSPOSE true

void SuperGraph::BuildSuperGraph(Graph& graph)
{
	Stack order = graph.DFS_With_Finish();

	while (!order.empty())
	{
		std::cout << order.top() << std::endl;
		order.pop();
	}

	//Graph graphT(graph, TRANSPOSE);
	//graphT.DFS_Create(&order);
	//stronglyConnectedComponents = graphT.DFS_transpose();
}