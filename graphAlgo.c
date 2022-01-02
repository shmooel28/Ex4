#include <stdlib.h>
#define MAX 2000000
#define N 10
int Graph[][];

int creatNewGraph(int n)
{   
    int **Graph = malloc(n*sizeof(int*));
    int i,j;
    for (i=0;i<n;i++)
    {
        Graph[i] = malloc(n*sizeof(int));
    }
    for (i = 0; i<n;i++)
        for(j=0;j<n;j++)
        {
            Graph[i][j] = -1;
        }

}
int addEdge(int **Graph, int src, int dest, int w)
{
    Graph[src][dest] = w;
}
int removeEdge(int **Graph, int src, int dest)
{
    Graph[src][dest] = -1;
}
int shortPath(int mat[][N])
{
    int dist[N][N];
    path_len(dist,mat);
    int i, j;
    scanf("%d%d", &i, &j);
    if (dist[i][j]==MAX||i==j)
    {
        printf("-1\n");
    }
    else{printf("%d\n",dist[i][j]);}
    return 1;
}
int path_len(int dist[][N], int mat[][N])
{
    int i,j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i==j) 
            {
                dist[i][j] = 0;
            }
            else
                if (mat[i][j]==0)
                {
                    dist[i][j] = MAX;
                }
                else
                    dist[i][j] = mat[i][j];
        }
    }
    int l, k, g;
    for (k = 0; k < N; k++)
    {
        for (l = 0; l < N; l++)
        {
            for (g = 0; g < N; g++)
            {
                if (dist[l][g] > dist[l][k]+dist[k][g])
                    dist[l][g] = dist[l][k]+dist[k][g];
            }
        }
    }
    return 1;
}
int tsp(int arr[])
{

}
