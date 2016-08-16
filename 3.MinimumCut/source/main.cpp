//Copyright 2016 <Shunji Lin>

#include "adjacencyList.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

const int N_NODES = 200;
const int ITERATIONS = 1000;

int main(int argc, char *argv[])
{
  int minCutEdges = N_NODES;

  AdjacencyList adjList(N_NODES);
  
  std::ifstream infile("../kargerMinCut.txt");
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    int u, v;
    iss >> u;
    while (iss >> v) {
      adjList.insertEdge(u-1, v-1);
    }
  }


  for (int i = 0; i < ITERATIONS; ++i) {
    printf("iteration : %d\n", i);
    srand(i);
    AdjacencyList adjListCopy = adjList;

    while (adjListCopy.nodeCount() > 2) {
      adjListCopy.contractRandomEdge();
    }

    if (adjListCopy.edgeCount() < minCutEdges) {
      minCutEdges = adjListCopy.edgeCount();
    }
  }

  printf("possible min cut edge count is: %d\n", minCutEdges);
  
  return 0;
}
