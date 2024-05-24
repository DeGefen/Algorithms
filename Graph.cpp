#include "Graph.h"
#include <iostream>
#include <stdlib.h>

#define EXCEPTION 1


void Graph::MakeEmptyGraph(int n)
{
	neighborlist = new NeighborList[n];
	numOfVertices = n;
}

bool Graph::IsAdjacent(int u, int v)
{
	auto it = neighborlist[u - 1].find(v);
	if (it != neighborlist[u - 1].end())
		return true;
	else
		return false;
}

NeighborList Graph::GetAdjList(int u)
{
	return neighborlist[u - 1];
}
void Graph::AddEdge(int u, int v)
{
	//std::cout << "CHECK " << u << " " << v << std::endl;
	neighborlist[u - 1].insert({v ,edgeType::undefiend });
}
void Graph::RemoveEdge(int u, int v)
{
	neighborlist[u - 1].erase(v);
}
void Graph::Fill(Edge* edges, int m)
{
	try
	{
		for (int i = 0; i < m; i++)
		{
			if (IsAdjacent(edges[i].in, edges[i].out))
			{
				throw EXCEPTION;
			}
			else
			{
				
				AddEdge(edges[i].in, edges[i].out);
			}
		}
	}
	catch (...)
	{
		std::cout << "invalid input" << std::endl;
		exit(1);
	}
	
}
void Graph::printGraph()
{
	for (int i = 0; i < numOfVertices; i++)
	{
		for (const auto& pair : neighborlist[i]) {
			std::cout << i+ 1 << " " << pair.first << std::endl;
		}
	}
}

Stack Graph::DFS()
{
	Stack myStack;
	int* color = new int[numOfVertices];
	for (int i = 0; i < numOfVertices; i++)
	{
		color[i] = vertesType::white;
	}
	for (int i = 0; i < numOfVertices; i++)
	{
		if (color[i] == vertesType::white)
		{
			DFS_VISIT(i, color, myStack);
		}
	}
	return myStack;
}
void Graph::DFS_VISIT(int u, int* color,Stack myStack)
{
	color[u] = vertesType::gray;
	for (auto& pair : neighborlist[u]) 
	{
		if (color[pair.first - 1] == vertesType::white)
		{
			pair.second = edgeType::tree;
			DFS_VISIT(pair.first, color,myStack);
		}	
	}
	color[u] = vertesType::black;
	myStack.push(u + 1);
}
