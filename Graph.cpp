#include "Graph.h"
#include <iostream>
#include <stdlib.h>

#define EXCEPTION 1


void Graph::MakeEmptyGraph()
{
	neighborlist = new NeighborList[numOfVertices];
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

void Graph::DFS_Create()
{
    if (!dfs)
        {
        dfs = new DFS(*this);
        }
}

Stack Graph::DFS_Finish()
{
    DFS_Create();
    return dfs->GetFinishOrder();
}

void Graph::DFS::run()
{
	for (int i = 0; i < graph.numOfVertices; i++)
	{
		color[i] = vertesType::white;
	}
	for (int i = 0; i < graph.numOfVertices; i++)
    {
        if (color[i] == vertesType::white) {
            Visit(i);
        }
    }
}

void Graph::DFS::run(Stack &order) {
    for (int i = 0; i < graph.numOfVertices; i++)
    {
        color[i] = vertesType::white;
    }
    int v;
    while (!order.empty())
    {
        v = order.top();
        order.pop();
        if (color[v] == vertesType::white) {
            Visit(v);
        }
    }
}

void Graph::DFS::Visit(int u)
{
	color[u] = vertesType::gray;
	for (auto& pair : graph.neighborlist[u])
	{
		if (color[pair.first - 1] == vertesType::white)
		{
			pair.second = edgeType::tree;
			Visit(pair.first);
		}	
	}
	color[u] = vertesType::black;
    finishOrder.push(u + 1);
}

void Graph::GetInput()
{
    try
    {
        int n, m;
        std::cout << "Please enter number of vertices: ";
        std::cin >> n;
        if (n <= 0)
        {
            throw EXCEPTION;
        }
        MakeEmptyGraph(n);
        std::cout << "Please enter number of edges: ";
        std::cin >> m;
        if (m < 0 || m > n* (n - 1))
        {
            throw EXCEPTION;
        }
        for (int u, v, i = 0; i < m; i++)
        {
            std::cin >> u >> v;
            if (v > n || u > n || u == v || IsAdjacent(u,v))
            {
              throw EXCEPTION;
            }
            AddEdge(u, v);
        }
    }
    catch (...)
    {
        std::cout << "invalid input" << std::endl;
        exit(1);
    }
}

void Graph::CopyGraph(const Graph &graph, bool transpose)
{
    if (!transpose)
    {
        for (int i = 0; i < numOfVertices; i++)
        {
            neighborlist[i] = std::move(graph.neighborlist[i]);
        }
    }
    if (transpose)
    {
        for (int i = 0; i < numOfVertices; i++)
        {
            for (const auto& pair : graph.neighborlist[i]) {
                AddEdge(pair.first, i);
            }
        }
    }
}

void Graph::ResetEdgeTypes() {
    for (int i = 0; i < numOfVertices; i++)
    {
        for (auto& pair : neighborlist[i]) {
            pair.second = edgeType::undefiend;
        }
    }
}
