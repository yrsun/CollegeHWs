// Authors: ??

#ifndef ROUTER_H
#define	ROUTER_H


#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>


using namespace std;


class Router {
public:
  Router(const int **capacities, int numRouters);
  int solve(int NYCPos);
  bool findpath(int NYCPos, int *parent);
  int **graph;
  int **residual;
  int number;


private:

};

#endif	/* ROUTER_H */

