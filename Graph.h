#pragma once
#include "Using.h"

class SuperGraph;

class Graph
{
protected:
	enum edgeType { tree, back, forward, cross, undefined}; //enum for edge classification
	int m_NumOfVertices = 0; //Number of Vertices
	int m_NumOfEdges = 0; //Number of Edges
	Vertex* m_ComponentsArray = nullptr; //Components connections Array.
	int m_ComponentsCount = 0; //Number of Components
	Queue m_ComponentsOrder; //order of vertices in teh components of second DFS
	NeighborList* m_NeighborList = nullptr; //graph neighbor list

	//input: Number of Vertices
	void MakeEmptyGraph(int i_NumOfVertices);//initialization of th graph with given amount of vertices

	//input: graph, transpose flag
	void CopyGraph(const Graph& graph, bool transpose);//copying the given graph with its edges according to the flag

	//input: order of vertices stack
	void DFSCreate(Stack* order = nullptr);//running DFS algorithm with given order depending on the input
	
	//nested class for the DFS algorithm
	class DFS
	{
		enum vertexType { white, gray, black };//enum for vertices classification

		Stack m_FinishOrder;//finish order stack of vertices
		Vertex* m_Color = nullptr;//color array as in DFS algorithm
		Graph& m_Graph;//graph that the algorithm is running on
		
		void Run(); //run DFS in regular order

		//input: order of vertices stack
		void Run(Stack* order); //run DFS in given order

		//input: U vertex, root of the tree, flag to understand which DFS it is. first or second in Sharir's algorithm
		void Visit(Vertex u, Vertex root = NULLROOT, bool second = !SECONDDFS);//DFS visit with changes based on input

	public:
		DFS(Graph& graph, Stack* order = nullptr) : m_Graph(graph)
		{
			m_Color = new Vertex[graph.m_NumOfVertices];
			if (order)
			{
				graph.m_ComponentsCount = 0;
				graph.m_ComponentsArray = new Vertex[graph.m_NumOfVertices];
				Run(order);
			}
			else
			{
				Run();
			}
		}
		Stack GetFinishOrder()
		{
			return m_FinishOrder;
		}
		
		~DFS()
		{
			delete[] m_Color;
		}
	};
    DFS* m_DFS = nullptr;
	friend DFS;
	friend SuperGraph;

public:
	Graph() = default;
	explicit Graph(int n) { MakeEmptyGraph(n); }
	Graph(const Graph& graph, bool transpose = false)
	{
		MakeEmptyGraph(graph.m_NumOfVertices);
		CopyGraph(graph, transpose);
	}

	Vertex * GetComponentsArray() const;
	//return the data member array

	Queue GetComponentsOrder() const;
	//return the data member Queue

	int GetComponentsCount() const;
	////return the data member integer value

    //input: vertex u
    NeighborList& GetAdjList(Vertex u) const;
    //output: Neighbor List of U

	//input: two vertices
	bool IsAdjacent(Vertex u, Vertex v) const;
	//output: true if v is adjacent of u

	//input: two vertices
	void AddEdge(Vertex u, Vertex v);//adds u -> v edge to the graph

	//input: two vertices
	void RemoveEdge(Vertex u, Vertex v);//removes u -> v edge to the graph

	//input: edges
	void Fill(Edges edges);//adds the edges to the graph

    void PrintInfo() const;//prints number of vertices and edges

	void PrintGraph() const;//prints the graph

	//input: number of vertices, number of edges
	static Edges GetInput(int& n, int& m);//gets input from user according to the given values
	//output: array of edges

	~Graph()
	{
		delete m_DFS;
		delete[] m_NeighborList;
		delete[] m_ComponentsArray;
	}
};