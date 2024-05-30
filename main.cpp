#include "SuperGraph.h"

int main() 
{
    try
    {
        int n, m;
        Edges edges = Graph::GetInput(n, m);
        Graph myGraph(n);
        myGraph.Fill(edges);
        SuperGraph mySuperGraph(myGraph);
        std::cout << std::endl;
        mySuperGraph.PrintInfo();
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        exit(1);
    }
    catch (...)
    {
        std::cout << "Error: unknown error" << std::endl;
        exit(1);
    }
	return 0;
}