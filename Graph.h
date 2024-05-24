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

class SuperGraph;

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

	int numOfVertices;
	int numOfEdges;
	NeighborList* neighborlist;

	void MakeEmptyGraph();
    void GetInput();
    void CopyGraph(const Graph &graph, bool transpose);
    void ResetEdgeTypes();

	Stack DFS_Finish();
    void DFS_Create();

    class DFS
        {
        enum vertesType {white, gray, black};

        Stack finishOrder;
        int* color;
        Graph& graph;

        void run();
        void run(Stack &order);
        void Visit(int u);
    public:
        DFS(Graph &graph): graph(graph)
        {
            color = new int[graph.numOfVertices];
            void run();
        }
        Stack GetFinishOrder() {
            return finishOrder;
        }
        ~DFS() {
            delete [] color;
        }
    };
    friend DFS;
    friend SuperGraph;

    DFS* dfs = nullptr;

public:
	
    Graph() = default;
	Graph(int n) : numOfVertices(n) { MakeEmptyGraph(); }
    Graph(const Graph &graph, bool transpose = false): numOfVertices(graph.numOfVertices)
    {
        MakeEmptyGraph();
        CopyGraph(graph, transpose);
    }
	bool IsAdjacent(int u, int v);
	NeighborList GetAdjList(int u);
	void AddEdge(int u, int v);
	void RemoveEdge(int u, int v);
	void Fill(Edge* edges, int m);
	void printGraph();
    void SarirKosaraju();

    ~Graph() {
        delete dfs;
        delete [] neighborlist;
    }
};