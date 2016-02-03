// Authors: Yiru Sun

#ifndef ROUTER_H
#define	ROUTER_H


#include <iostream>
#include <limits.h>
#include <vector>
#include <string.h>
#include <queue>


using namespace std;


class Router {
public:
  Router(const int **capacities, int numRouters);
  int solve(int NYCPos);
  int findpath(int NYCPos);
  int **graph;
  vector <int> *g;
  int **residual;
//  int *current;
  int *parent;
  int number;
  int path_flow;


private:

};

#endif	/* ROUTER_H */

