#pragma once
#include <map>
#include <stack>

#define EXCEPTION 1

struct Edge {
	int in;
	int out;
};

using Stack = std::stack<int>;
using NeighborList = std::map<int, int>;