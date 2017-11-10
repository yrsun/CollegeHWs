//Yiru Sun
#include "router.h"
#include <iostream>
#include <limits.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;


Router::Router(const int **capacities, int numRouters)
{
	graph = new int *[numRouters];
	residual = new int*[numRouters];
    parent = new int[numRouters];
//    current = new int[numRouters];
    g = new vector <int> [numRouters];
	number = numRouters;
	for (int i = 0; i < numRouters; ++i)
	{

		graph[i]= new int [numRouters];
		residual[i]= new int [numRouters];
		for (int j = 0; j < numRouters; ++j)
		{
			graph[i][j]= capacities[i][j];
			residual[i][j]=0;
            if(capacities[i][j]!=0)
            {
                g[i].push_back(j);
                g[j].push_back(i);
            }

		}
	}
} // Router()


int Router::solve(int NYCPos)
{
	int maxflow=0;
	while (true)
    {
        path_flow=findpath(NYCPos);
        if(path_flow==0) 
            break;
        else maxflow+=path_flow;
    }   
    return maxflow;
} 

int Router::findpath(int NYCPos)
{
    bool b[number];
    for (int i = 0; i < number; ++i)
    {
       parent[i]=-1;
       b[i]=0;
    }

    int c, path, pre;
    queue <int> q;
    q.push(0);

    b[0]=true;
    parent[0]=-1;

    while(!q.empty())
    {
        c = q.front();
        q.pop();
       // if(c==NYCPos) break;
        for (int i = 0; i < g[c].size(); ++i)
        {
            int to = g[c][i];
            if(b[to]==false&&graph[c][to]>0)
            {                 
                q.push(to);
                b[to]=true;
                parent[to]=c;
                if (to==NYCPos)
                {
                    break;
                }
            }
        }
    }

    c=NYCPos;
    path=INT_MAX;

    while(parent[c]>-1)
    {
        pre=parent[c];
        path = (path<graph[pre][c])?path:graph[pre][c];
        c=pre;
    }

    c=NYCPos;
    while(parent[c]>-1)
    {
        pre=parent[c];
        graph[pre][c]-=path;
        graph[c][pre]+=path;
        c=pre;
    }


    if (path == INT_MAX)
    {
        return 0;
    }else
    {
        return path;
    }
}

