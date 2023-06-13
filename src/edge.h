#ifndef _EDGE_H
#define _EDGE_H

using namespace std;

struct Edge
{
    int u, v, w;
    static bool CompareWeight(const Edge &a, const Edge &b)
    {
        return (a.w > b.w);
    }
};

#endif