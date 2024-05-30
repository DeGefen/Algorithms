#include "SuperGraph.h"

void SuperGraph::BuildSuperGraph(Graph& graph)
{
    graph.DFSCreate(); //first DFS run in regular order
    Stack order = graph.m_DFS->GetFinishOrder();
	Graph graphT(graph, TRANSPOSE); //builds transpose graph
	graphT.DFSCreate(&order);//second DFS run with reversed finish order
	int* componentsArray = graphT.GetComponentsArray();
	Queue componentsOrder = graphT.GetComponentsOrder();
	int componentsAmount = graphT.GetComponentsCount();
    Vertex vertex;
    Vertex componentA;
    Vertex componentB;
	auto* lastFatherArray = new Vertex[componentsAmount];

	std::fill(lastFatherArray, lastFatherArray+ componentsAmount, NULLVALUE);
	MakeEmptyGraph(componentsAmount);
	while (!componentsOrder.empty())
	{
		vertex = componentsOrder.front();
        componentsOrder.pop();
        for (auto& pair : graph.m_NeighborList[vertex - 1])
		{
            componentA = componentsArray[vertex - 1];
            componentB = componentsArray[pair.first - 1];
			if (componentA != componentB && lastFatherArray[componentB - 1] != componentA)
			{
				AddEdge(componentA, componentB);
				lastFatherArray[componentB - 1] = componentA;
			}
		}
	}
	delete[] lastFatherArray;
}