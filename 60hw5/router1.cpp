#include "router.h"
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;


Router::Router(const int **capacities, int numRouters)
{
	graph = new int *[numRouters];
	residual = new int*[numRouters];
	number = numRouters;
	for (int i = 0; i < numRouters; ++i)
	{
		graph[i]= new int [numRouters];
		residual[i]= new int [numRouters];
		for (int j = 0; j < numRouters; ++j)
		{
			graph[i][j]= capacities[i][j];
			residual[i][j]=capacities[i][j];

		}
	}
} // Router()


int Router::solve(int NYCPos)
{
	int u, v;
	int parent[number];
	int maxflow=0;
	while (findpath(NYCPos,parent))
    {
        int path_flow = INT_MAX;
        for (v=NYCPos; v!=0; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, residual[u][v]);
        }
 
        for (v=NYCPos; v != 0; v=parent[v])
        {
            u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
 
        maxflow += path_flow;
    }
 
    
    return maxflow;
} 

bool Router::findpath(int NYCPos, int *parent)
{
	bool blackorwhite[number];
    for (int i = 0; i < number; ++i)
    {
    	blackorwhite[i]=0;
    }
   
 
    queue <int> q;
    q.push(0);
    blackorwhite[0] = true;
    parent[0] = -1;
 

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<number; v++)
        {
            if (blackorwhite[v]==false && residual[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                blackorwhite[v] = true;
            }
        }
    }
 
    return (blackorwhite[NYCPos]);
}

