#pragma once
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <exception>


#define EXCEPTION std::exception() //throw exception
#define NULLROOT (-1) //"null" equivalent of int for vertices
#define NULLVALUE (-1) // //"null" value indication
#define TRANSPOSE true //bool for transpose graph
#define SECONDDFS true //bool for second DFS run in the algorithm

using Vertex = int;

//edges struct
struct Edge 
{
    Vertex in = NULLVALUE; //source edge
    Vertex out = NULLVALUE; //destination edge
};

using Stack = std::stack<Vertex>;
using NeighborList = std::map<Vertex, int>;
using Queue = std::queue<Vertex>;
using Edges = std::queue<Edge>;