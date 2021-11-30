#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define THRESHOLD 3
// A directed graph using
// adjacency list representation
struct AdjVer
{
   int vertex;
   int weight;
   AdjVer(int a, int b)
   {
      vertex = a;
      weight = b;
   }
   AdjVer()
   {
      vertex = 0;
      weight = 0;
   }
};
struct Vertex
{
   int loop;
   bool hasLoop;
   vector<AdjVer> adj;
   Vertex()
   {
      loop = 0;
      hasLoop = false;
   }
};
struct Path
{
   vector<int> path;
   int length;
   Path()
   {
      length = 0;
   }
   void printPath()
   {
      for (int i = 0; i < path.size(); i++)
      {
         cout << path[i] << " ";
      }
      cout << endl;
   }
   int getLength()
   {
      return length;
   }
};
bool comparePath(Path a, Path b)
{
   return a.length < b.length;
}
class Graph
{
   int V;
   bool containsLoop; // No. of vertices in graph
   vector<vector<int>> conEdges;
   // A recursive function used by printAllPaths()
   void printAllPathsUtil(int, int, bool[], vector<int>, vector<vector<int>> &);
   bool isLoop(vector<int> &, int);

public:
   vector<Vertex> vertices;                // Pointer to an array containing adjacency lists
   Graph(int V, bool containsLoop = true); // Constructor
   void addEdge(int v, int u, int w);
   void addConEdge(int v, int u);
   vector<Path> getAllPaths(int s, int d);
   Path kthPath(int s, int d, int k);
   Path pathWithEdge(int, int);
   int size() { return V; }
   void printAllPaths(int s, int d);
};

Graph::Graph(int V, bool containsLoop)
{
   this->V = V;
   this->containsLoop = containsLoop;
   vertices.resize(V);
}

void Graph::addEdge(int u, int v, int w)
{
   vertices[u].adj.push_back(AdjVer(v, w)); // Add v to u’s list.
   if (u == v && containsLoop)
      vertices[u].hasLoop = true;
}

// Prints all paths from 's' to 'd'
vector<Path> Graph::getAllPaths(int s, int d)
{
   // Mark all the vertices as not visited
   bool *visited = new bool[V];

   // Create an array to store paths
   vector<int> path;

   // Initialize all vertices as not visited
   for (int i = 0; i < V; i++)
      visited[i] = false;
   vector<vector<int>> res;
   // Call the recursive helper function to print all paths
   printAllPathsUtil(s, d, visited, path, res);
   int len = res.size();
   for (int i = 0; i < len; i++)
   {
      vector<int> loopPos;

      for (int j = 0; j < res[i].size(); j++)
      {
         if (vertices[res[i][j]].hasLoop)
         {
            loopPos.push_back(j);
            for (int k = 1; k < THRESHOLD; k++)
            {
               vector<int> tmpPath = res[i];
               for (int l = 1; l <= k; l++)
                  tmpPath.insert(tmpPath.begin() + j + l, res[i][j]);
               res.push_back(tmpPath);
            }
         }
      }
      if (containsLoop)
      {
         for (int k = 1; k < THRESHOLD; k++)
         {
            vector<int> tmpPath = res[i];
            vector<int> tmpLoopPos = loopPos;

            for (int p = 1; p <= k; p++)
            {
               for (int m = 0; m < tmpLoopPos.size(); m++)
               {
                  tmpPath.insert(tmpPath.begin() + tmpLoopPos[m] + p, res[i][tmpLoopPos[m]]);
               }
            }
            res.push_back(tmpPath);
         }
      }
   }
   vector<Path> paths;
   for (int i = 0; i < res.size(); i++)
   {
      Path p;
      p.length = 0;
      for (int j = 0; j < res[i].size() - 1; j++)
      {
         int weight = 0;
         for (int k = 0; k < vertices[res[i][j]].adj.size(); k++)
         {
            if (vertices[res[i][j]].adj[k].vertex == res[i][j + 1])
            {
               weight = vertices[res[i][j]].adj[k].weight;
               break;
            }
         }
         p.length += weight;
      }
      p.path = res[i];
      paths.push_back(p);
   }
   return paths;
}

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[],
                              vector<int> path, vector<vector<int>> &res)
{
   // Mark the current node and store it in path[]
   visited[u] = true;
   path.push_back(u);

   // If current vertex is same as destination, then print
   // current path[]
   if (u == d)
   {
      res.push_back(path);
   }
   else // If current vertex is not destination
   {
      // Recur for all the vertices adjacent to current vertex
      for (int i = 0; i < vertices[u].adj.size(); i++)
      {
         // if (u == vertices[u].adj[i])
         // {
         //    vertices[u].loop++;
         //    if (vertices[u].loop < THRESHOLD)
         //    {
         //       printAllPathsUtil(vertices[u].adj[i], d, visited, path, res);
         //    }
         // }
         // else
         if (!visited[(vertices[u].adj[i].vertex)])
            printAllPathsUtil(vertices[u].adj[i].vertex, d, visited, path, res);
      }
   }

   // Remove current vertex from path[] and mark it as unvisited
   path.clear();
   visited[u] = false;
}
bool Graph::isLoop(vector<int> &path, int u)
{
   for (int i = 0; i < path.size(); i++)
   {
      if (path[i] == u)
         return true;
   }
   return false;
}
Path Graph::kthPath(int s, int d, int k)
{
   vector<Path> paths = getAllPaths(s, d);
   sort(paths.begin(), paths.end(), comparePath);
   return k > paths.size() ? paths[paths.size() - 1] : paths[k - 1];
}
void Graph::addConEdge(int v, int u)
{
   conEdges.push_back({v, u});
}
Path Graph::pathWithEdge(int s, int d)
{
   vector<vector<int>> miniPaths;
   miniPaths.push_back({s, conEdges[0][0]});
   for (int i = 0; i < conEdges.size(); i++)
   {
      miniPaths.push_back(conEdges[i]);
      if (i != conEdges.size() - 1)
         miniPaths.push_back({conEdges[i][1], conEdges[i + 1][0]});
   }
   miniPaths.push_back({conEdges[conEdges.size() - 1][1], d});
   vector<Path> paths;
   for (int i = 0; i < miniPaths.size(); i++)
   {
      paths.push_back(kthPath(miniPaths[i][0], miniPaths[i][1], 1));
   }
   Path res;
   for (int i = 0; i < paths.size(); i++)
   {
      res.length += paths[i].length;
      res.path.insert(res.path.end(), paths[i].path.begin(), paths[i].path.end());
      if (i != paths.size() - 1)
         res.path.pop_back();
   }
   return res;
}
void Graph::printAllPaths(int s, int d) {
   vector<Path> paths = getAllPaths(s, d);
   sort(paths.begin(), paths.end(), comparePath);
   for (int i = 0; i < paths.size(); i++)
   {
      cout<<"Path "<<i+1<<": ";
      for (int j = 0; j < paths[i].path.size(); j++)
      {
         cout << paths[i].path[j] << " ";
      }
      cout << endl;
      cout<<"Length: "<<paths[i].length<<endl;
   }
}
