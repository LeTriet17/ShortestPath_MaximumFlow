#include "GRAPH.h"


int main()
{
   // Create a graph given in the above diagram
   Graph g(4, true);
   g.addEdge(0, 1, 1);
   g.addEdge(0, 2, 3);
   g.addEdge(0, 3, 2);
   g.addEdge(2, 0, 1);
   g.addEdge(2, 1, 3);
   g.addEdge(1, 3, 4);
   g.addEdge(2, 2, 6);
   g.addConEdge(0, 1); // add constraint edge
   g.addConEdge(1, 3); // add constraint edge
   int s = 2, d = 3;
   Path p = g.pathWithEdge(s, d);
   p.printPath();
   return 0;
}
