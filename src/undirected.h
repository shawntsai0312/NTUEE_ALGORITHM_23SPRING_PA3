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
    int findRoot(int *parent, int index);
    void unionSets(int *parent, int *rank, int x, int y);
};

#endif