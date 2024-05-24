#pragma once
#include <map>
#include <stack>
#include <iostream>
#include <stdlib.h>


using Stack = std::stack<int>;

using NeighborList = std::map<int, int>;
struct Edge {
	int in;
	int out;
};

class Graph {
protected:
	enum edgeType
	{
		tree = 0, //green
		back = 1, //red
		forward = 2, //blue
		cross = 3, //cross
		undefiend = 4 //und
	};

	enum vertesType
	{
		white = 0,
		gray = 1,
		black = 2,
	};

	int numOfVertices;
	int numOfEdges;
	NeighborList* neighborlist;
	void MakeEmptyGraph(int n);
	void DFS();
	Stack DFS_VISIT(int u, int* color, Stack myStack);

public:
	
	Graph(int n, int m) : numOfEdges(m) { MakeEmptyGraph(n); }
	bool IsAdjacent(int u, int v);
	NeighborList GetAdjList(int u);
	void AddEdge(int u, int v);
	void RemoveEdge(int u, int v);
	void Fill(Edge* edges, int m);
	void printGraph();
};