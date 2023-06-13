#include <iostream>
#include <fstream>
#include "edge.h"
#include "directed.h"
#include "undirected.h"

using namespace std;

int main(int argc, char *argv[])
{
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    char mode;
    fin >> mode;
    int V = 0, E = 0;
    fin >> V >> E;
    Edge *edgeArr = new Edge[E];
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        fin >> u >> v >> w;
        Edge temp;
        temp.u = u;
        temp.v = v;
        temp.w = w;
        edgeArr[i] = temp;
    }
    int removedWeight = 0;
    vector<Edge> removedEdges;
    if (mode == 'u')
    {
        Undirected undirected(V, E, edgeArr);
        undirected.USolver(removedWeight, removedEdges);
        // cout << removedWeight << "\n";
        // for (int i = 0; i < remainedEdges.size(); i++)
        // {
        //     cout << remainedEdges[i].u << " "
        //          << remainedEdges[i].v << " "
        //          << remainedEdges[i].w << "\n";
        // }
        fout << removedWeight << "\n";
        for (int i = 0; i < removedEdges.size(); i++)
        {
            fout << removedEdges[i].u << " "
                 << removedEdges[i].v << " "
                 << removedEdges[i].w << "\n";
        }
    }
    if (mode == 'd')
    {
        Directed directed(V, E, edgeArr);
        directed.DSolver(removedWeight, removedEdges);
        // cout << removedWeight << "\n";
        // for (int i = 0; i < removedEdges.size(); i++)
        // {
        //     cout << removedEdges[i].u << " "
        //          << removedEdges[i].v << " "
        //          << removedEdges[i].w << "\n";
        // }
        fout << removedWeight << "\n";
        for (int i = 0; i < removedEdges.size(); i++)
        {
            fout << removedEdges[i].u << " "
                 << removedEdges[i].v << " "
                 << removedEdges[i].w << "\n";
        }
    }
}