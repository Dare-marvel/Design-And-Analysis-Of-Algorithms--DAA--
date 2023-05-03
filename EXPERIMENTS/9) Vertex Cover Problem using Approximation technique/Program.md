### [Vertex Cover Problem](https://www.geeksforgeeks.org/introduction-and-approximate-solution-for-vertex-cover-problem/)

## Explanation of main logic of the function:
The printVertexCover function in the code is used to find the minimum vertex cover of an undirected graph using a greedy algorithm.

The function starts by initializing a boolean array visited of size V, where V is the number of vertices in the graph. All the values in the array are set to false initially.

The function then considers each vertex of the graph one by one. For each vertex u, it checks if visited[u] is false. If it is true, it means that the vertex u has already been covered by some other vertex in the previous iteration, so it moves to the next vertex.

If visited[u] is false, the function goes through all the adjacent vertices of u using an iterator i. For each adjacent vertex v, it checks if visited[v] is false. If it is also false, it means that both the vertices u and v are not yet covered by any other vertex, so the function selects this edge (u,v) and adds both u and v to the vertex cover set. It then marks visited[u] and visited[v] as true so that they are not considered in the next iteration.

The function continues this process for all vertices until all vertices are marked as visited.

Finally, the function prints the vertex cover set by iterating over all vertices and printing those vertices whose value in the visited array is true.

The algorithm follows a greedy approach by selecting an uncovered edge and adding its both endpoints to the vertex cover set. The greedy approach is guaranteed to find a vertex cover with size no more than twice the size of an optimal vertex cover.

## Time and Space Complexity:
### `Time Complexity`:
The time complexity of the function is `O(V+E)`, where V is the number of vertices and E is the number of edges in the graph. This is because the function loops through each vertex and its adjacent vertices, and each edge is processed only once.

### `Space Complexity`:
The space complexity of the function is `O(V)`, where V is the number of vertices in the graph. This is because the function uses a boolean array to keep track of visited vertices.

## Code:
```cpp
#include<iostream>
#include <list>
using namespace std;
 
// This class represents a undirected graph using adjacency list
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;  // Pointer to an array containing adjacency lists
public:
    Graph(int V);  // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    void printVertexCover();  // prints vertex cover
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); // Since the graph is undirected
}
 
// The function to print vertex cover
void Graph::printVertexCover()
{
    // Initialize all vertices as not visited.
    bool visited[V];
    for (int i=0; i<V; i++)
        visited[i] = false;
 
    list<int>::iterator i;
 
    // Consider all edges one by one
    for (int u=0; u<V; u++)
    {
        // An edge is only picked when both visited[u] and visited[v]
        // are false
        if (visited[u] == false)
        {
            // Go through all adjacents of u and pick the first not
            // yet visited vertex (We are basically picking an edge
            // (u, v) from remaining edges.
            for (i= adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = *i;
                if (visited[v] == false)
                {
                     // Add the vertices (u, v) to the result set.
                     // We make the vertex u and v visited so that
                     // all edges from/to them would be ignored
                     visited[v] = true;
                     visited[u]  = true;
                     break;
                }
            }
        }
    }
 
    // Print the vertex cover
    cout << "Vertex cover: ";
    for (int i=0; i<V; i++)
        if (visited[i])
          cout << i << " ";
    cout << endl;
}
 
// Driver program to test methods of graph class
int main()
{
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    Graph g(V);
    cout << "Enter the number of edges: ";
    cin >> E;
    cout << "Enter edges (u v):" << endl;
    for(int i=0; i<E; i++) {
        int u, v;
        cout << "Edge number: " << i + 1 << endl;
        cin >> u >> v;
        g.addEdge(u, v);
    }
 
    g.printVertexCover();
 
    return 0;
}
```
