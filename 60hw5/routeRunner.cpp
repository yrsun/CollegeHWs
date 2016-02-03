// Author: Sean Davis 
// Created on May 19, 2014, 12:07 AM

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "CPUTimer.h"
#include "router.h"
using namespace std;

int** readFile(const char *filename, int *numRouters, int *solution, 
  int *NYCPos)
{
  char *ptr, *line = new char[150000];
  ifstream inf(filename);
  inf.getline(line, 150000);
  *numRouters = atoi(strtok(line, ","));
  *NYCPos = atoi(strtok(NULL, ","));
  *solution = atoi(strtok(NULL, ","));
  int **capacities = new int*[*numRouters];

  for(int i = 0; i < *numRouters; i++)
  {
    capacities[i] = new int[*numRouters];
    
    for(int j = 0; j < *numRouters; j++)
      capacities[i][j] = 0;
    
    inf.getline(line, 150000);
    ptr = strtok(line, ",");
    
    while(ptr)
    {
      int pos = atoi(ptr);
      capacities[i][pos] = atoi(strtok(NULL, ","));
      ptr = strtok(NULL, ",");
    }
  } // for each router
  
  return capacities;
} // readFile())


int main(int argc, char** argv) {
  int numRouters, solution, NYCPos, totalFlow;
  double startTime, endTime;
  int **capacities = readFile(argv[1], &numRouters, &solution, &NYCPos);
  startTime = getCPUTime();
  Router *router = new Router((const int**)capacities, numRouters);
  
  for(int i = 0; i < numRouters; i++)
    delete[] capacities[i];
  
  totalFlow = router->solve(NYCPos);
  endTime = getCPUTime();
  
  if(totalFlow != solution)
    cout << "Yours: " << totalFlow << " Solution: "  << solution << endl;
  
  cout << "CPU time: " << endTime - startTime << endl;
  return 0;
} // main())

