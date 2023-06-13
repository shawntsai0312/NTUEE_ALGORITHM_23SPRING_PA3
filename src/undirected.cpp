#include <iostream>
#include <fstream>
#include <algorithm>
#include "undirected.h"
using namespace std;

Undirected::Undirected(int V, int E, Edge *edgeArr)
    : V(V),
      E(E),
      edgeArr(edgeArr){};

int Undirected::findRoot(int *parent, int index)
{
    if (parent[index] == -1)
        return index;
    return this->findRoot(parent, parent[index]);
}

void Undirected::unionSets(int *parent, int *rank, int x, int y)
{
    int xRoot = this->findRoot(parent, x);
    int yRoot = this->findRoot(parent, y);

    if (rank[xRoot] > rank[yRoot])
    {
        // y merge into x
        parent[yRoot] = xRoot;
    }
    else if (rank[xRoot] < rank[yRoot])
    {
        // x merge into y
        parent[yRoot] = xRoot;
    }
    else
    {
        // same rank => either one is fine
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

void Undirected::USolver(int &removedWeight, vector<Edge> &removedEdges)
{
    // Kruskal MST algorithm
    int *parent = new int[this->V];
    int *rank = new int[this->V];
    fill_n(parent, this->V, -1);
    fill_n(rank, this->V, 0);

    sort(this->edgeArr, this->edgeArr + this->E, Edge::CompareWeight);

    int verticesCounter = 0, edgesCounter = 0;
    while (verticesCounter < this->V && edgesCounter < this->E)
    {
        // cout << verticesCounter << "\t" << edgesCounter << "\n";
        Edge currEdge = this->edgeArr[edgesCounter];
        // cout<<currEdge.u<< " -- " << currEdge.v << " : " << currEdge.w << "\n\n";

        int uRoot = this->findRoot(parent, currEdge.u);
        int vRoot = this->findRoot(parent, currEdge.v);
        if (uRoot != vRoot)
        {
            this->unionSets(parent, rank, uRoot, vRoot);
            verticesCounter++;
        }
        else
        {
            removedWeight += currEdge.w;
            removedEdges.push_back(currEdge);
        }
        edgesCounter++;
    }
    delete[] parent;
    delete[] rank;
}
