#include <iostream>
#include <algorithm>
#include <vector>
#include "directed.h"
using namespace std;

Directed::Directed(int V, int E, Edge *edgeArr)
    : V(V),
      E(E),
      edgeArr(edgeArr) {}

void Directed::DSolver(int &removedWeight, vector<Edge> &removedEdges)
{
    int weightAnswer1 = 0, weightAnswer2 = 0;
    vector<Edge> removedAnswer1, removedAnswer2;
    DKruskalAddBack(weightAnswer1, removedAnswer1);
    DKruskalGreedy(weightAnswer2, removedAnswer2);
    // cout << weightAnswer1 << "\t" << weightAnswer2 << "\n";
    if (weightAnswer1 <= weightAnswer2)
    {
        cout << "Add Back\n";
        removedWeight = weightAnswer1;
        removedEdges = removedAnswer1;
    }
    else
    {
        cout << "Greedy\n";
        removedWeight = weightAnswer2;
        removedEdges = removedAnswer2;
    }
}

void Directed::DKruskalAddBack(int &removedWeight, vector<Edge> &removedEdges)
{
    int URemovedWeight = 0;
    vector<Edge> URemovedEdges, URemainedEdges;

    bool *vAdded = new bool[this->V];
    fill_n(vAdded, this->V, true);

    UKruskal(URemovedWeight, URemovedEdges, URemainedEdges);
    vector<int> *adjList = new vector<int>[this->V];
    for (int i = 0; i < URemainedEdges.size(); i++)
    {
        adjList[URemainedEdges[i].u].push_back(URemainedEdges[i].v);
    }

    int removedEdgesCounter = 0;
    // cout << URemovedEdges.size() << "\n";
    while (removedEdgesCounter < URemovedEdges.size())
    {
        Edge currEdge = URemovedEdges[removedEdgesCounter];
        // cout << currEdge.u << "\t" << currEdge.v << "\t" << currEdge.w << "\t";
        // cout << removedEdgesCounter << "\t" << URemovedEdges.size() << "\t" << (removedEdgesCounter < URemovedEdges.size()) << "\n";
        if (currEdge.w > 0)
        {
            // only consider positive edges
            if (cycleChecker(currEdge, adjList, vAdded))
            {
                // add back => cycle exist => cannot add back
                removedEdges.push_back(currEdge);
                removedWeight += currEdge.w;
            }
            else
            {
                // add back => cycle does not exist => add back to lower the weight
                URemainedEdges.push_back(currEdge);
                adjList[currEdge.u].push_back(currEdge.v);
            }
        }
        else
        {
            removedEdges.push_back(currEdge);
            removedWeight += currEdge.w;
        }
        removedEdgesCounter++;
    }
}

int Directed::findRoot(int *parent, int index)
{
    if (parent[index] == -1)
        return index;
    return this->findRoot(parent, parent[index]);
}

void Directed::unionSets(int *parent, int *rank, int x, int y)
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

void Directed::UKruskal(int &URemovedWeight, vector<Edge> &URemovedEdges, vector<Edge> &URemainedEdges)
{
    // Kruskal MST algorithm
    int *parent = new int[V];
    int *rank = new int[V];
    fill_n(parent, V, -1);
    fill_n(rank, V, 0);

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
            URemainedEdges.push_back(currEdge);
        }
        else
        {
            URemovedWeight += currEdge.w;
            URemovedEdges.push_back(currEdge);
        }
        edgesCounter++;
    }
    delete[] parent;
    delete[] rank;
}

void Directed::DKruskalGreedy(int &removedWeight, vector<Edge> &removedEdges)
{
    // sort vertices by weight (decreasing order)
    // add an edge each time and check if cycles exists
    //      case 1 : if new vertices added => ok
    //      case 2 : if no new vertices added => check cycle

    sort(this->edgeArr, this->edgeArr + this->E, Edge::CompareWeight);
    bool *vAdded = new bool[this->V];
    fill_n(vAdded, this->V, false);

    vector<Edge> resultEdges;
    vector<int> *adjList = new vector<int>[this->V];

    int edgesCounter = 0;
    while (edgesCounter < this->E)
    {
        Edge currEdge = edgeArr[edgesCounter];
        // cout << currEdge.u << "\t" << currEdge.v << "\t" << currEdge.w << "\n";
        if (vAdded[currEdge.u] && vAdded[currEdge.v])
        {
            if (cycleChecker(currEdge, adjList, vAdded))
            {
                // cout << "remove\n";
                removedWeight += currEdge.w;
                removedEdges.push_back(currEdge);
            }
            else
            {
                // cout << "add1\n";
                vAdded[currEdge.u] = true;
                vAdded[currEdge.v] = true;
                resultEdges.push_back(currEdge);
                adjList[currEdge.u].push_back(currEdge.v);
            }
        }
        else
        {
            // new vertices added => add
            // cout << "add2\n";
            vAdded[currEdge.u] = true;
            vAdded[currEdge.v] = true;
            resultEdges.push_back(currEdge);
            adjList[currEdge.u].push_back(currEdge.v);
        }
        edgesCounter++;
    }
    delete[] vAdded;
    delete[] adjList;
}

bool Directed::cycleChecker(Edge temp, vector<int> *adjList, bool *vAdded)
{
    vector<int> *tempAdjList = new vector<int>[this->V];
    for (int i = 0; i < this->V; i++)
    {
        tempAdjList[i] = adjList[i];
    }
    tempAdjList[temp.u].push_back(temp.v);

    bool *tempVAdded = new bool[V];
    for (int i = 0; i < this->V; i++)
    {
        tempVAdded[i] = vAdded[i];
    }
    tempVAdded[temp.u] = true;
    tempVAdded[temp.v] = true;

    vector<DfsState> dfsState(this->V, White);
    for (int vertex = 0; vertex < this->V; ++vertex)
    {
        if (tempVAdded[vertex])
        {
            // cout << "now visiting\t" << vertex << "\t";
            if (dfsState[vertex] == White)
            {
                if (cycleDfs(vertex, dfsState, tempAdjList))
                {
                    // cout << "cycle exists\n";
                    return true;
                }
            }
            // cout << "return cycle does not exist\n";
        }
    }
    delete[] tempAdjList;
    delete[] tempVAdded;
    return false;
}

bool Directed::cycleDfs(int vertex, vector<DfsState> &dfsState, vector<int> *adjList)
{
    dfsState[vertex] = Grey;
    for (int i = 0; i < adjList[vertex].size(); i++)
    {
        // cout<<adjList[vertex][i]<<"\t";
        if (dfsState[adjList[vertex][i]] == Grey)
        {
            // cout << "return grey\n";
            return true;
        }
        else if (dfsState[adjList[vertex][i]] == White)
        {
            if (cycleDfs(adjList[vertex][i], dfsState, adjList))
            {
                // cout << "return white\n";
                return true;
            }
        }
    }
    dfsState[vertex] = Black;
    // cout << "return black\n";
    return false;
}
