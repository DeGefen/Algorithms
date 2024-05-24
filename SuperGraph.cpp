#include "SuperGraph.h"
#include "Using.h"

#define TRANSPOSE true

void SuperGraph::BuildSuperGraph(Graph& graph)
{
	Stack order = graph.DFS_Finish();
	Graph graphT(graph, TRANSPOSE);
	graphT.DFS_Create(&order);
	stronglyConnectedComponents = graphT.DFS_transpose();

}