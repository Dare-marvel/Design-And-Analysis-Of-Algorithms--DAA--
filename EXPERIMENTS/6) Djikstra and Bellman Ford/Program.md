### Bellman-Ford Algorithm
##### [Link 1](https://www.youtube.com/watch?v=HYefC2QRNbg&ab_channel=eLearningBihar)
##### [Link 2](https://www.youtube.com/watch?v=T_jIM6_JrQM&ab_channel=Tutorialspoint)

### [Dijkstra's Algorithm](https://www.youtube.com/watch?v=XB4MIexjvY0&ab_channel=AbdulBari)

## Explanation of the main functions :
### `Dijkstra's Algorithm`

This code implements Dijkstra's algorithm to find the shortest path from a given source vertex to all other vertices in a weighted graph.

The function minDistance is a helper function that takes three arguments:

* dist: an array of distances from the source vertex to each vertex in the graph
* sptSet: an array that keeps track of whether a vertex is already included in the shortest path tree
* n: the number of vertices in the graph
It loops through all the vertices and finds the vertex with the minimum distance value that is not already in the shortest path tree (sptSet value is 0). It returns the index of the vertex with the minimum distance.

The dijkstra function takes three arguments:

* graph: a 2D array representing the weighted graph
* src: the index of the source vertex
* n: the number of vertices in the graph
The function first initializes dist and sptSet arrays with INT_MAX and 0 values respectively. It sets the distance of the source vertex to 0.

Then, for each vertex in the graph, it selects the vertex u with the minimum distance that is not already included in the shortest path tree. It sets sptSet[u] to 1 to include it in the shortest path tree.

For each neighbor vertex v of u, it updates the distance value of v if the following conditions are met:

v is not already included in the shortest path tree
there is an edge from u to v
the total weight of the path from the source to v through u is smaller than the current value of dist[v]
Finally, the function calls the printSolution function to print the shortest distances to all vertices from the source vertex.

### `Bellman Ford Algorithm`
The bellmanFord function implements the Bellman-Ford algorithm for finding the shortest path from a source vertex to all other vertices in a weighted directed graph with no negative-weight cycles. The function takes in three parameters:

* graph: A 2D array of size V x V representing the adjacency matrix of the input graph, where V is the number of vertices in the graph.
* src: An integer representing the index of the source vertex.
* n: An integer representing the number of vertices in the graph.
The function first initializes an array dist of size n to store the shortest distance from the source vertex to each vertex in the graph. It sets the distance to the source vertex as 0, and the distance to all other vertices as infinity (represented by the INT_MAX constant).

The function then performs n-1 iterations of the following loop:
```c
for (int i = 1; i <= n - 1; i++)
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
```
In each iteration, the function checks every edge in the graph and updates the distance to the destination vertex v if it can be improved by going through the source vertex u. Specifically, if there exists an edge from u to v, and the distance to u is not infinity (meaning there is a path from the source to u), and the distance to v through u is shorter than the current distance to v, the distance to v is updated to the new shorter distance. This process is repeated for every vertex in the graph, resulting in the shortest path to all vertices being found after n-1 iterations.

Finally, the function checks for the presence of negative-weight cycles by iterating through every edge in the graph again and checking if there exists a shorter path from src to v through u, which indicates the presence of a negative-weight cycle. If such a cycle is found, the function prints a message to the console and returns.

If no negative-weight cycles are present in the graph, the function calls printSolution to print the shortest distance to each vertex from the source vertex.


## Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 100

// Finds the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[], int n)
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Prints the constructed distance array
void printSolution(int dist[], int n, int graph[][V])
{
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\n", i, dist[i]);
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}

// Function that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
void dijkstra(int graph[][V], int src, int n)
{
    int dist[n], sptSet[n];

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++)
    {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = 1;
        for (int v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution(dist, n, graph);
}

// Function that implements Bellman-Ford's single source shortest path algorithm for a graph represented using adjacency matrix representation
void bellmanFord(int graph[][V], int src, int n)
{
    int dist[n];
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= n - 1; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
    // Check for negative-weight cycles
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                printf("Graph contains negative-weight cycle\n");
                return;
            }

    printSolution(dist, n, graph);
}

int main()
{
    int n, graph[V][V], src;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("\nEnter the source vertex:\n");
    scanf("%d", &src);
    
    printf("Dijkstra's Algorithm\n");
    dijkstra(graph, src, n);

    printf("\nEnter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter the source vertex:\n");
    scanf("%d", &src);
    
    printf("Bellman-Ford Algorithm\n");
    bellmanFord(graph, src, n);

    return 0;
}
```
