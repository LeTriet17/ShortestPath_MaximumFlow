#include "Dinic.h"
#include "fordFulkerson.h"
// Driver Code
int main()
{

   //EXAMPLE DINIC ALGORITHM

   Graph g(6);
   g.addEdge(0, 1, 10);
   g.addEdge(0, 2, 10);
   g.addEdge(1, 2, 2);
   g.addEdge(1, 3, 4);
   g.addEdge(1, 4, 8);
   g.addEdge(2, 4, 9);
   g.addEdge(3, 5, 10);
   g.addEdge(4, 3, 6);
   g.addEdge(4, 5, 10);
   int d_source = 0;
   int d_des = 5;
   cout << "Maximum flow of Dinic's Algorithm from " << d_source << " to " << d_des << " is " << g.DinicMaxflow(0, 5) << endl;

   // EXAMPLE FF ALGORITHM
   int graph[V][V] = {{0, 10, 10, 0, 0, 0}, {0, 0, 2, 4, 8, 0}, {0, 0, 0, 0, 9, 0}, {0, 0, 9, 0, 0, 10}, {0, 0, 0, 6, 0, 10}, {0, 0, 0, 0, 0, 0}};
   int ff_source = 0;
   int ff_des = 5;
   cout << "Maximum flow of Ford-Fulkerson Algorithm from " << ff_source << " to " << ff_des << " is " << fordFulkerson(graph, 0, 5) << endl;
}