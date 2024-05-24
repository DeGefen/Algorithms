#include "Graph.h"
#include <iostream>
#include <stdlib.h>
#include "Using.h"


void Graph::MakeEmptyGraph(int i_NumOfvertices)
{
	m_NumOfVertices = i_NumOfvertices;
	m_Neighborlist = new NeighborList[m_NumOfVertices];
}

bool Graph::IsAdjacent(int i_U, int i_V)
{
	auto it = m_Neighborlist[i_U - 1].find(i_V);

	return (it != m_Neighborlist[i_U - 1].end());	
}

NeighborList Graph::GetAdjList(int i_U)
{
	return m_Neighborlist[i_U - 1];
}

void Graph::AddEdge(int i_U, int i_V)
{
	m_Neighborlist[i_U - 1].insert({ i_V ,edgeType::undefined });
}

void Graph::RemoveEdge(int i_U, int i_V)
{
	m_Neighborlist[i_U - 1].erase(i_V);
}

void Graph::Fill(Edge* i_Edges, int i_M)
{
	try
	{
		for (int i = 0; i < i_M; i++)
		{
			if (IsAdjacent(i_Edges[i].in, i_Edges[i].out))
			{
				throw EXCEPTION;
			}
			else
			{
				AddEdge(i_Edges[i].in, i_Edges[i].out);
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
	for (int i = 0; i < m_NumOfVertices; i++)
	{
		for (const auto& pair : m_Neighborlist[i]) 
		{
			std::cout << i + 1 << " " << pair.first << std::endl;
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
	for (int i = 0; i < graph.m_NumOfVertices; i++)
	{
		color[i] = vertesType::white;
	}
	for (int i = 0; i < graph.m_NumOfVertices; i++)
	{
		if (color[i] == vertesType::white) 
		{
			Visit(i);
		}
	}
}

void Graph::DFS::run(Stack& io_Order) 
{
	int v;
	for (int i = 0; i < graph.m_NumOfVertices; i++)
	{
		color[i] = vertesType::white;
	}
	
	while (!io_Order.empty())
	{
		v = io_Order.top();
		io_Order.pop();
		if (color[v] == vertesType::white) 
		{
			Visit(v);
		}
	}
}

void Graph::DFS::Visit(int i_U)
{
	color[i_U] = vertesType::gray;
	for (auto& pair : graph.m_Neighborlist[i_U])
	{
		if (color[pair.first - 1] == vertesType::white)
		{
			pair.second = edgeType::tree;
			Visit(pair.first);
		}
	}
	color[i_U] = vertesType::black;
	finishOrder.push(i_U + 1);
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
			if (v > n || u > n || u == v || IsAdjacent(u, v))
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

void Graph::CopyGraph(const Graph& i_Graph, bool i_transpose)
{
	if (!i_transpose)
	{
		for (int i = 0; i < m_NumOfVertices; i++)
		{
			m_Neighborlist[i] = std::move(i_Graph.m_Neighborlist[i]);
		}
	}
	else
	{
		for (int i = 0; i < m_NumOfVertices; i++)
		{
			for (const auto& pair : i_Graph.m_Neighborlist[i])
			{
				AddEdge(pair.first, i);
			}
		}
	}
}

void Graph::ResetEdgeTypes() 
{
	for (int i = 0; i < m_NumOfVertices; i++)
	{
		for (auto& pair : m_Neighborlist[i]) 
		{
			pair.second = edgeType::undefined;
		}
	}
}