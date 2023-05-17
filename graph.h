#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 100
#define INF INT_MAX

int no_vertices;

//prototyping here:
void print_graph(int adj[no_vertices][no_vertices]);
void bfs(int adj[][no_vertices], int start);
void dfs(int adj[][no_vertices], int visited[], int start);
void shortestPath(int adj[][MAX_VERTICES], int numVertices, int start, int end);


void bfs(int adj[][no_vertices], int start)
{

    FILE *BFS = fopen("BFS.txt", "w");
    int *visited, *queue;
    int front = 0, rear = -1;

    visited = (int*)calloc(no_vertices, sizeof(int));
    queue = (int*)malloc(no_vertices * sizeof(int));

    queue[++rear] = start;
    visited[start] = 1;

    fprintf(BFS, "BFS: ", start);
    while (front <= rear)
    {
        start = queue[front++];
        printf("%d\t", start);

        fprintf(BFS, " %d\t", start);

        for (int i = 0; i < no_vertices; i++)
        {
            if (adj[start][i] == 1 && visited[i] != 1)
            {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }

    free(visited);
    free(queue);
    fclose(BFS);
}



void dfs(int adj[][no_vertices], int visited[], int start)
{

    printf("%d\t", start);

    visited[start] = 1;

    for (int i = 0; i < no_vertices; i++)
    {
        if (visited[i] != 1 && adj[start][i] == 1)
        {
            dfs(adj, visited, i);
        }
    }

}


void print_graph(int adj[no_vertices][no_vertices])
{
    FILE *fp = fopen("matrix.txt", "w");
    for (int i = 0; i < no_vertices; i++)
    {
        for (int j = 0; j < no_vertices; j++)
        {
            printf(" %d  ",adj[i][j]);
            fprintf(fp, " %d ||", adj[i][j]);
        }
        printf("\n");
        fprintf(fp, "\n");
        
    }
    fclose(fp);
    
}

void shortestPath(int adj[][MAX_VERTICES], int numVertices, int start, int end)
{
    int cost[MAX_VERTICES][MAX_VERTICES], distance[MAX_VERTICES], pred[MAX_VERTICES];
    int visited[MAX_VERTICES], count, minDistance, nextNode, i, j;

    FILE *path = fopen("Shortest Path.txt", "w");
    
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            if (adj[i][j] == 0)
                cost[i][j] = INT_MAX;
            else
                cost[i][j] = adj[i][j];
        }
    }

    for (i = 0; i < numVertices; i++) {
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    while (count < numVertices) {
        minDistance = INT_MAX;
        nextNode = -1;

        for (i = 0; i < numVertices; i++) {
            if (distance[i] < minDistance && !visited[i]) {
                minDistance = distance[i];
                nextNode = i;
            }
        }

        if (nextNode == -1) {
            break;
        }

        visited[nextNode] = 1;
        
        for (i = 0; i < numVertices; i++) {
            if (!visited[i] && minDistance + cost[nextNode][i] < distance[i]) {
                distance[i] = minDistance + cost[nextNode][i];
                pred[i] = nextNode;
            }
        }
        count++;
    }

    // Printing the distance
    if (distance[end] == INT_MAX) {
        printf("No path found from node %d to node %d\n", start, end);
        fprintf(path, "No path found from node %d to node %d\n", start, end);
    } else {
        printf("Shortest distance from node %d to node %d: %d\n", start, end, distance[end]);
        fprintf(path, "Shortest distance from node %d to node %d: %d\n", start, end, distance[end]);
    }

    fclose(path);
}


#endif