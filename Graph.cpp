#include "Graph.h"

void Graph::MakeEmptyGraph(int i_NumOfVertices)
{
	m_NumOfVertices = i_NumOfVertices;
    m_NeighborList = new NeighborList[m_NumOfVertices];
}

NeighborList& Graph::GetAdjList(Vertex i_U) const
{
    return m_NeighborList[i_U - 1];
}

bool Graph::IsAdjacent(Vertex i_U, Vertex i_V) const
{
	auto it = GetAdjList(i_U).find(i_V);

	return (it != GetAdjList(i_U).end());
}


void Graph::AddEdge(Vertex i_U, Vertex i_V)
{
    GetAdjList(i_U).insert({i_V , edgeType::undefined });
	m_NumOfEdges++;
}

void Graph::RemoveEdge(Vertex i_U, Vertex i_V)
{
    GetAdjList(i_U).erase(i_V);
	m_NumOfEdges--;
}

void Graph::Fill(Edges io_Edges)
{
	try
	{
        Edge edge;
		while(!io_Edges.empty())
		{
            edge = io_Edges.front();
            io_Edges.pop();
			if (IsAdjacent(edge.in, edge.out))
			{
				throw EXCEPTION;
			}
			else
			{
				AddEdge(edge.in, edge.out);
			}
		}
	}
	catch (...)
	{
		std::cout << "invalid input" << std::endl;
		exit(1);
	}
}

void Graph::PrintGraph() const
{
	for (int i = 1; i <= m_NumOfVertices; i++)
	{
		for (const auto& pair : GetAdjList(i))
		{
			std::cout << i << " " << pair.first << std::endl;
		}
	}
}

void Graph::PrintInfo() const
{
    std::cout << m_NumOfVertices << " " << m_NumOfEdges;
}

void Graph::DFSCreate(Stack* order)
{
	if (!m_DFS)
	{
        m_DFS = new DFS(*this, order);
		 
	}
}

void Graph::DFS::Run()
{
	for (int i = 0; i < m_Graph.m_NumOfVertices; i++)
	{
		m_Color[i] = vertexType::white;
	}

	for (int i = 1; i <= m_Graph.m_NumOfVertices; i++)
	{
		if (m_Color[i-1] == vertexType::white)
		{
			Visit(i);
		}
	}
}

void Graph::DFS::Run(Stack* io_Order)
{
    Vertex v;
	for (int i = 0; i < m_Graph.m_NumOfVertices; i++)
	{
		m_Color[i] = vertexType::white;
	}

	while (!io_Order->empty())
	{
		v = io_Order->top();
		io_Order->pop();
		if (m_Color[v-1] == vertexType::white)
		{
			m_Graph.m_ComponentsCount++;
			Visit(v, m_Graph.m_ComponentsCount, SECONDDFS);
		}
	}
}

void Graph::DFS::Visit(Vertex i_U, Vertex root, bool second)
{
    m_Color[i_U - 1] = vertexType::gray;
	for (auto& pair : m_Graph.GetAdjList(i_U))
	{
		if (m_Color[pair.first - 1] == vertexType::white)
		{
			pair.second = edgeType::tree;
			Visit(pair.first, root, second);
		}
        else if (m_Color[pair.first - 1] == vertexType::gray)
        {
            pair.second = edgeType::back;
        }
	}

	m_Color[i_U - 1] = vertexType::black;
	if (second)
	{
        m_Graph.m_ComponentsOrder.push(i_U);
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
		for (int i = 1; i <= m_NumOfVertices; i++)
		{
            GetAdjList(i) = std::move(i_Graph.GetAdjList(i));
		}
	}
	else
	{
		for (int i = 1; i <= m_NumOfVertices; i++)
		{
			for (const auto& pair : i_Graph.GetAdjList(i))
			{
				AddEdge(pair.first, i);
			}
		}
	}
}

Edges Graph::GetInput(int& n, int& m)
{
	try
	{
		std::cout << "Please enter number of vertices: ";
		std::cin >> n;
		if (n < 0)
		{
			throw EXCEPTION;
		}
		std::cout << "Please enter number of edges: ";
		std::cin >> m;
		if (m < 0 || m > (n*(n - 1))/2)
		{
			throw EXCEPTION;
		}
		Edges edges;
        Edge edge;
        if (m > 0)
        {
            std::cout << "Please enter edges:\n";
        }
		for (int i = 0; i < m; i++)
		{
			std::cin >> edge.in >> edge.out;
			if (edge.in > n || edge.out > n || edge.in == edge.out)
            {
                throw EXCEPTION;
            }
            else
            {
                edges.push(edge);
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

int* Graph::GetComponentsArray() const
{
	return m_ComponentsArray;
}

Queue Graph::GetComponentsOrder() const
{
	return m_ComponentsOrder;
}

int Graph::GetComponentsCount() const
{
	return m_ComponentsCount;
}