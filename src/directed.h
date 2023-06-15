#ifndef _DIRECTED_H
#define _DIRECTED_H

#include <vector>
#include "edge.h"
using namespace std;

enum DfsState
{
    White, // unvisited
    Grey,  // visiting
    Black  // visited
};

class Directed
{
public:
    Directed(int V, int E, Edge *edgeArr);
    void DSolver(int &removedWeight, vector<Edge> &removedEdges);

private:
    int V;
    int E;
    Edge *edgeArr;

    void DKruskalAddBack(int &removedWeight, vector<Edge> &removedEdges);
    void UKruskal(int &URemovedWeight, vector<Edge> &URemovedEdges, vector<Edge> &URemainEdges);
    int findRoot(int *root, int index, int myIndex);
    void unionSets(int *root, int *rank, int x, int y);

    void DKruskalGreedy(int &removedWeight, vector<Edge> &removedEdges);
    bool cycleChecker(Edge temp, vector<int> *adjList, bool *vAdded);
    bool cycleDfs(int vertex, vector<DfsState> &state, vector<int> *adjList);
};

#endif