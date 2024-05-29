#pragma once
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <stdlib.h>


#define EXCEPTION 1 //some value to throw exception
#define NULLROOT -1 //"null" equivalent of int for vetrices
#define TRANSPOSE true //bool for transpose graph
#define SECONDDFS true //bool for seconf DFS run in the algorithm

//edgee struct
struct Edge 
{
	int in; //source edge
	int out; //destination edge
};

using Stack = std::stack<int>;
using NeighborList = std::map<int, int>;
using Queue = std::queue<int>;