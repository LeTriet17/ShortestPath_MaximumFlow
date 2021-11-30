#include "Dinic.h"
// Driver Code
int main()
{

   Graph g(6);
   g.addEdge(0, 1, 8);
   g.addEdge(0, 3, 11);
   g.addEdge(1, 2, 11);
   g.addEdge(1, 3, 1);
   g.addEdge(2, 4, 7);
   g.addEdge(2, 5, 4);
   g.addEdge(3, 1, 10);
   g.addEdge(3, 4, 12);
   g.addEdge(4, 1, 4);
   g.addEdge(4, 5, 15);
   int d_source = 0;
   int d_des = 5;
   cout << "Maximum flow of Dinic's Algorithm from " << d_source << " to " << d_des << " is " << g.DinicMaxflow(0, 5) << endl;
}