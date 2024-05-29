#include "SuperGraph.h"

void SuperGraph::BuildSuperGraph(Graph& graph)
{
	Stack order = graph.DFSWithFinish(); //first DFS run in regular order
	Graph graphT(graph, TRANSPOSE); //builds transpose graph
	graphT.DFSCreate(&order);//second DFS run with end order
	int* componentsArray = graphT.GetComponetsArray();
	Queue componentsOrder = graphT.GetComponetsOrder();
	int componentsAmount = graphT.GetComponetsCount();
	int vertex;
	int* lastFatherArray = new int[componentsAmount];

	std::fill(lastFatherArray, lastFatherArray+ componentsAmount, -1);
	MakeEmptyGraph(componentsAmount);
	while (!componentsOrder.empty())
	{
		vertex = componentsOrder.front();
		for (auto& pair : graph.m_Neighborlist[vertex - 1])
		{
			if (componentsArray[pair.first - 1] != componentsArray[vertex - 1] && lastFatherArray[componentsArray[pair.first - 1] - 1] != componentsArray[vertex - 1])
			{
				
				AddEdge(componentsArray[vertex - 1], componentsArray[pair.first - 1]);
				lastFatherArray[componentsArray[pair.first - 1] - 1] = componentsArray[vertex - 1];
			}
		}

		componentsOrder.pop();
	}
	delete[] lastFatherArray;
}
void SuperGraph::printStats()
{
	std::cout << m_NumOfVertices << " " << m_NumOfEdges;
}

