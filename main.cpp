#include <iostream>
#include <stdlib.h>
#include "Graph.h"
#include <array>

#define EXCEPTION 1



Edge* GetInput(int& n, int& m) {
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

int main() {
	int n, m;
	Edge* edges = GetInput(n, m);
	
	Graph myGraph(n, m);
	myGraph.Fill(edges, m);
	//myGraph.printGraph();


	return 0;
}