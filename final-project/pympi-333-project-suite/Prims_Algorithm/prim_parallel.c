#include <stdio.h>
#include <limits.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int minKey(int key[], int visited[], int V, int nthreads)
{
    int min = INT_MAX, index, i;
#pragma omp parallel num_threads(nthreads)
    {
        int index_local = index;
        int min_local = min;

// do not need synchronization after the loop, hence nowait
#pragma omp for nowait // I referred to a resource for this and researched what "no wait" does
        for (i = 0; i < V; i++)
        {
            if (visited[i] == 0 && key[i] < min_local)
            {
                min_local = key[i];
                index_local = i;
            }
        }

// We want to avoid a race condition here as min_local
#pragma omp critical
        {
            if (min_local < min)
            {
                min = min_local;
                index = index_local;
            }
        }
    }

    return index;
}

void printMST(int from[], int n, int **graph, int V)
{
    int i;
    printf("Edge   Weight\n");
    for (i = 1; i < V; i++)
        printf("%d - %d    %d \n", from[i], i, graph[i][from[i]]);
}

void primMST(int **graph, int V, int nthreads)
{
    int from[V];
    int key[V];
    int visited[V];
    int i, count;
    for (i = 0; i < V; i++)
        key[i] = INT_MAX, visited[i] = 0;

    key[0] = 0;
    from[0] = -1;

    for (count = 0; count < V - 1; count++)
    {
        int u = minKey(key, visited, V, nthreads);
        visited[u] = 1;

        int v;
#pragma omp parallel for schedule(static) num_threads(nthreads)
        for (v = 0; v < V; v++)
        {
            if (graph[u][v] && visited[v] == 0 && graph[u][v] < key[v])
                from[v] = u, key[v] = graph[u][v];
        }
    }
}

int main(int argc, char *argv[])
{
    // exit the program if number of vertices are not entered
    if (argc <= 1)
    {
        printf("You did not enter the number of vertices, the program will exit now :( ...\n");
        exit(1);
    }

    // Getting number of vertices in a graph
    int V = atoi(argv[1]);

    int nthreads = 1;
    // Getting the input for number of threads from cmd line
    if (argc > 1)
        nthreads = strtol(argv[2], NULL, 10);

    // int graph[V][V];
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int x = 0; x < V; x++)
        graph[x] = (int *)malloc(V * sizeof(int));
    int i, j;
    // Generate random adjacency matrix
    srand(time(NULL));
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            graph[i][j] = rand() % 10;

    for (i = 0; i < V; i++)
    {
        graph[i][i] = 0;
    }

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            graph[j][i] = graph[i][j];

    double start = omp_get_wtime();
    primMST(graph, V, nthreads);
    double end = omp_get_wtime();
    printf("Elapsed Time: %f\nNumber of Threads: %d\n", end - start, nthreads);

    return 0;
}