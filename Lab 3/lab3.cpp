/* Spencer Walls */ 
/* CCPS 616 */
/* Lab 3 */

#include <climits> 
#include <fstream>
#include <vector>

/* This function finds the node with the minimum distance
to the tree */
int min_dist(int distance[], bool visited[], int V) 
{  
    int min_idx; 
    int min_dist = INT_MAX;
      
    for (int v = 0; v < V; v++) 
    {
        if (visited[v] == false && distance[v] < min_dist) 
        {
            min_dist = distance[v];
            min_idx = v; 
        }
    }

    return min_idx; 
}   

/* This function finds a minimum spanning tree of a graph
using Prim's algorithm */
void prims_MST(std::vector<std::vector<int> > graph, int parent[], int V) 
{ 
    int distance[V];  
    bool visited[V];  

    for (int i = 0; i < V; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false; 
    }
      
    parent[0] = -1; 
    distance[0] = 0;
  
    for (int j = 0; j < V - 1; j++) 
    { 
        int closest_v = min_dist(distance, visited, V); 
  
        visited[closest_v] = true; 
  
        for (int v = 0; v < V; v++)
        {
            if (graph[closest_v][v] && visited[v] == false && graph[closest_v][v] < distance[v])
            { 
                parent[v] = closest_v;
                distance[v] = graph[closest_v][v]; 
            }
        }
    } 
} 

int main(int argc, char **argv) 
{ 
    std::ifstream input_file(argv[1]);
    int V = 0;
    input_file >> V;

    std::vector<std::vector<int> > graph(V, std::vector<int>(V));

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            input_file >> graph[i][j];
        }  
    }

    int parent[V];                    
                         
    prims_MST(graph, parent, V);
     
    std::vector<std::vector<int> > MST(V, std::vector<int>(V)); 

    for (int i = 1; i < V; i++)
    { 
        MST[i][parent[i]] = graph[i][parent[i]];
        MST[parent[i]][i] = graph[i][parent[i]];
    } 

    std::ofstream output_file;
    output_file.open("graphMST.txt");

    output_file << V << std::endl;

    for (int j = 0; j < V; j++)
    {
        for (int k = 0; k < V; k++)
        {
            output_file << MST[j][k] << " ";
        }
        output_file << std::endl;
    }

    return 0; 
}