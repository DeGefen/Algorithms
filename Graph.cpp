#include "Graph.h"

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
	m_NumOfEdges++;
}

void Graph::RemoveEdge(int i_U, int i_V)
{
	m_Neighborlist[i_U - 1].erase(i_V);
	m_NumOfEdges--;
}

void Graph::Fill(Edge* io_Edges, int i_M)
{
	try
	{
		for (int i = 0; i < i_M; i++)
		{
			if (IsAdjacent(io_Edges[i].in, io_Edges[i].out))
			{
				throw EXCEPTION;
			}
			else
			{
				AddEdge(io_Edges[i].in, io_Edges[i].out);
			}
		}
	}
	catch (...)
	{
		std::cout << "invalid input" << std::endl;
		exit(1);
	}
	delete[] io_Edges;
}

void Graph::PrintGraph()
{
	for (int i = 0; i < m_NumOfVertices; i++)
	{
		for (const auto& pair : m_Neighborlist[i])
		{
			std::cout << i + 1 << " " << pair.first << std::endl;
		}
	}
}

void Graph::DFSCreate(Stack* order)
{
	if (!dfs)
	{
		dfs = new DFS(*this, order);
		 
	}
}

Stack Graph::DFSWithFinish()
{
	DFSCreate();

	return dfs->GetFinishOrder();
}

void Graph::DFS::Run()
{
	for (int i = 0; i < m_Graph.m_NumOfVertices; i++)
	{
		m_Color[i] = vertesType::white;
	}

	for (int i = 1; i <= m_Graph.m_NumOfVertices; i++)
	{
		if (m_Color[i-1] == vertesType::white)
		{
			Visit(i);
		}
	}
}

void Graph::DFS::Run(Stack* io_Order)
{
	int v;
	for (int i = 0; i < m_Graph.m_NumOfVertices; i++)
	{
		m_Color[i] = vertesType::white;
	}

	while (!io_Order->empty())
	{
		v = io_Order->top();
		io_Order->pop();
		if (m_Color[v-1] == vertesType::white)
		{
			m_Graph.m_ComponentsCount++;
			Visit(v, m_Graph.m_ComponentsCount, SECONDDFS);
		}
	}
}

void Graph::DFS::Visit(int i_U, int root = NULLROOT, bool second = !SECONDDFS)
{
	if (second)
	{
		m_Graph.m_ComponentsOrder.push(i_U);
	}

	m_Color[i_U - 1] = vertesType::gray;
	for (auto& pair : m_Graph.m_Neighborlist[i_U - 1])
	{
		if (m_Color[pair.first - 1] == vertesType::white)
		{
			pair.second = edgeType::tree;
			Visit(pair.first, root, second);
		}
	}

	m_Color[i_U - 1] = vertesType::black;
	if (second)
	{
		m_Graph.m_ComponentsArray[i_U - 1] = root;
	}
	else
	{
		m_FinishOrder.push(i_U);
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
				AddEdge(pair.first, i+1);
			}
		}
	}
}

Edge* Graph::GetInput(int& n, int& m)
{
	try
	{
		std::cout << "Please enter number of vertices: ";
		std::cin >> n;
		if (n <= 0)
		{
			throw EXCEPTION;
		}
		std::cout << "Please enter number of edges: ";
		std::cin >> m;
		if (m < 0 || m > n* (n - 1))
		{
			throw EXCEPTION;
		}
		Edge* edges = new Edge[m];
		for (int i = 0; i < m; i++)
		{
			std::cin >> edges[i].in >> edges[i].out;
			if (edges[i].in > n || edges[i].out > n || edges[i].in == edges[i].out)
			{
				delete[] edges;
				throw EXCEPTION;
			}
		}
		return edges;
	}
	catch (...)
	{
		std::cout << "invalid input" << std::endl;
		exit(1);
	}
}

int* Graph::GetComponetsArray()
{
	return m_ComponentsArray;
}

Queue Graph::GetComponetsOrder()
{
	return m_ComponentsOrder;
}

int Graph::GetComponetsCount()
{
	return m_ComponentsCount;
}