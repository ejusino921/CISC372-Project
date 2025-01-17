#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#define INFINITY 9999
#define MAX 15000

void dijkstra(int G[MAX][MAX], int n, int startnode);

int main()
{
    int G[MAX][MAX];
    int n = 15000; //number of vertices
    for(int i = 0; i < n;i++) {
    	for(int j = 0; j < n;j++) {
    	    G[i][j] = rand()%100;
    	}
    }//set matrix
    int u = 0;// start node
    dijkstra(G, n, u);
    return 0;
}

void dijkstra(int G[MAX][MAX], int n, int startnode)
{
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    
    clock_t tic = clock();

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (G[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = G[i][j];
    //initialize pred[],distance[] and visited[]
    for (i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < n - 1)
    {
        mindistance = INFINITY;
        //nextnode gives the node at minimum distance
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        //check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    //print the path and distance of each node
    for (i = 0; i < n; i++)
        if (i != startnode)
        {
            //printf("\nDistance of node%d=%d", i, distance[i]);
            //printf("\nPath=%d", i);
            j = i;
            do
            {
                j = pred[j];
                //printf("<-%d", j);
            } while (j != startnode);
        }
    clock_t toc = clock();
    printf("time=%.2f seconds\n", (double)(toc - tic)/ CLOCKS_PER_SEC);
}