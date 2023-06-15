#include <iostream>
#include <fstream>
#include <algorithm>
#include "undirected.h"
using namespace std;

Undirected::Undirected(int V, int E, Edge *edgeArr)
    : V(V),
      E(E),
      edgeArr(edgeArr){};

int Undirected::findRoot(int *root, int index, int myIndex)
{
    if (root[index] == -1)
    {
        if (index != myIndex)
        {
            root[myIndex] = index;
        }
        return index;
    }
    return this->findRoot(root, root[index], myIndex);
}

void Undirected::unionSets(int *root, int *rank, int x, int y)
{
    int xRoot = this->findRoot(root, x, x);
    int yRoot = this->findRoot(root, y, y);

    if (rank[xRoot] > rank[yRoot])
    {
        // y merge into x
        root[yRoot] = xRoot;
    }
    else if (rank[xRoot] < rank[yRoot])
    {
        // x merge into y
        root[yRoot] = xRoot;
    }
    else
    {
        // same rank => either one is fine
        root[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

void Undirected::USolver(int &removedWeight, vector<Edge> &removedEdges)
{
    // Kruskal MST algorithm
    int *root = new int[this->V];
    int *rank = new int[this->V];
    fill_n(root, this->V, -1);
    fill_n(rank, this->V, 0);

    sort(this->edgeArr, this->edgeArr + this->E, Edge::CompareWeight);

    int verticesCounter = 0, edgesCounter = 0;
    while (verticesCounter < this->V && edgesCounter < this->E)
    {
        // cout << verticesCounter << "\t" << edgesCounter << "\n";
        Edge currEdge = this->edgeArr[edgesCounter];
        // cout << currEdge.u << " -- " << currEdge.v << " : " << currEdge.w << "\n\n";
        int uRoot = this->findRoot(root, currEdge.u, currEdge.u);
        int vRoot = this->findRoot(root, currEdge.v, currEdge.v);
        if (uRoot != vRoot)
        {
            this->unionSets(root, rank, uRoot, vRoot);
            verticesCounter++;
        }
        else
        {
            removedWeight += currEdge.w;
            removedEdges.push_back(currEdge);
        }
        edgesCounter++;
    }
    delete[] root;
    delete[] rank;
}
