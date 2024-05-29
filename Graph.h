#pragma once
#include "Using.h"
#include <iostream>
#include <stdlib.h>

class SuperGraph;

class Graph
{
protected:

	enum edgeType { tree, back, forward, cross, undefined };
	int m_NumOfVertices;
	int m_NumOfEdges;
	NeighborList* m_Neighborlist;
	void MakeEmptyGraph(int numOfvertices);
	void CopyGraph(const Graph& graph, bool transpose);
	void ResetEdgeTypes();
	Stack DFS_With_Finish();
	void DFS_Create(Stack* order = nullptr);
	class DFS
	{
		enum vertesType { white, gray, black };

		Stack finishOrder;
		int* color;
		Graph& graph;

		void run();
		void run(Stack* order);
		void Visit(int u, int v);
	public:
		DFS(Graph& graph, Stack* order = nullptr) : graph(graph)
		{
			color = new int[graph.m_NumOfVertices];
			if (order)
			{
				run(order);
			}
			else
			{
				run();
			}
		}
		Stack GetFinishOrder()
		{
			return finishOrder;
		}
		~DFS()
		{
			delete[] color;
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

	bool IsAdjacent(int u, int v);
	NeighborList GetAdjList(int u);
	void AddEdge(int u, int v);
	void RemoveEdge(int u, int v);
	void Fill(Edge* edges, int m);
	void printGraph();
	static Edge* GetInput(int& n, int& m);
	~Graph()
	{
		delete dfs;
		delete[] m_Neighborlist;
	}
};