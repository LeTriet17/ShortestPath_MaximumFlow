#include "GRAPH.h"
//THRESHOLD of loop has been set in GRAPH.h

int main()
{
   // Create a graph given in the above diagram
   Graph g(4, false); //doesn't have loops
   g.addEdge(0, 1, 1);
   g.addEdge(0, 2, 3);
   g.addEdge(0, 3, 2);
   g.addEdge(2, 0, 1);
   g.addEdge(2, 1, 3);
   g.addEdge(1, 3, 4);
   g.addEdge(2, 2, 6);
   int s = 2, d = 3;
   g.printAllPaths(s, d);
   Path p = g.kthPath(s, d, 2);
   p.printPath();
   return 0;
}
