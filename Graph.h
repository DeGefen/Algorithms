#pragma once
#include "Using.h"

class SuperGraph;

class Graph
{
protected:
	enum edgeType { tree, back, forward, cross, undefined }; //enum for edge classification
	int m_NumOfVertices = 0; //Number of Vertices
	int m_NumOfEdges = 0; //Number of Edges
	int* m_ComponentsArray = nullptr; //Components connections Array.
	int m_ComponentsCount; //Number of Components
	Queue m_ComponentsOrder; //order of vertrices in teh components of second DFS
	NeighborList* m_Neighborlist; //graph neighbor list

	//input: Number of Vertices
	void MakeEmptyGraph(int numOfvertices);//initialization of th graph with given amount of vertices

	//input: graph, transpose flag
	void CopyGraph(const Graph& graph, bool transpose);//copying the given graph with its edges according to the flag

	Stack DFSWithFinish();//running DFS algorithm with regular order
	//output: stack with finish order of vertices

	//input: order of vetrices stack
	void DFSCreate(Stack* order = nullptr);//running DFS algorithm with given order depending on the input
	
	//nested class for the DFS algorithm
	class DFS
	{
		enum vertesType { white, gray, black };//enum for vertices classification

		Stack m_FinishOrder;//finish order stack of vertices
		int* m_Color = nullptr;//color array as in DFS algorithm
		Graph& m_Graph;//graph that the algorithm is running on
		
		void Run(); //run DFS in regular order

		//input: order of vetrices stack
		void Run(Stack* order); //run DFS in given order

		//input: U verice, root of the tree, flag to undersatnd wich DFS it is. first or second in Sharir's algorithm
		void Visit(int u, int root = NULLROOT, bool second = !SECONDDFS);//visit as in DFS with improvments according to input

	public:
		DFS(Graph& graph, Stack* order = nullptr) : m_Graph(graph) 
		{
			m_Color = new int[graph.m_NumOfVertices];
			if (order)
			{
				graph.m_ComponentsCount = 0;
				graph.m_ComponentsArray = new int[graph.m_NumOfVertices];
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

	friend DFS;
	friend SuperGraph;
	DFS* dfs = nullptr;

public:
	Graph() = default; 
	Graph(int n) { MakeEmptyGraph(n); }
	Graph(const Graph& graph, bool transpose = false)
	{
		MakeEmptyGraph(graph.m_NumOfVertices);
		CopyGraph(graph, transpose);
	}

	int* GetComponetsArray();
	//return the data member array

	Queue GetComponetsOrder();
	//return the data member Queue

	int GetComponetsCount();
	////return the data member integer value

	//input: two vertices
	bool IsAdjacent(int u, int v);
	//output: true if v is adjecent of u

	//input: vertice u
	NeighborList GetAdjList(int u);
	//output: Neighbor List of U

	//input: two vertices
	void AddEdge(int u, int v);//adds u -> v edge to the graph

	//input: two vertices
	void RemoveEdge(int u, int v);//removes u -> v edge to the graph

	//input: array of edges, amount of edges
	void Fill(Edge* edges, int m);//adds the edges to the graph

	void PrintGraph();//prints the graph

	//input: number of vertices, number of edges
	static Edge* GetInput(int& n, int& m);//gets input from user according to the given values
	//output: array of edges

	~Graph()
	{
		delete dfs;
		delete[] m_Neighborlist;
		delete[] m_ComponentsArray;
	}
};