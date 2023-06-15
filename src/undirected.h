#ifndef _UNDIRECTED_H
#define _UNDIRECTED_H

#include <vector>
#include "edge.h"
using namespace std;

class Undirected
{
public:
    Undirected(int V, int E, Edge *edgeArr);
    void USolver(int &removedWeight, vector<Edge> &removedEdges);

private:
    int V;
    int E;
    Edge *edgeArr;
    int findRoot(int *root, int index, int myIndex);
    void unionSets(int *root, int *rank, int x, int y);
};

#endif