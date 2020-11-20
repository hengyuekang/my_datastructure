#pragma once
#include "Queue.h"
// state of vertex
typedef enum
{
    UNDISCOVERED,
    DISCOVERED,
    VISITED
} VStatus;
// state of edge in tree from a graph
typedef enum
{
    UNDETERMINED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD
} EType;
// vertex,edge
template <typename Tv, typename Te>
class Graph
{
private:
    // reset all the vertexes and edges

    void reset()
    {
        // n:number of vertexes
        for (int i = 0; i < n; i++)
        {
            // label of status and time
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;
            // (tree)parent node,priority
            parent(i) = -1;
            priority(i) = INT_MAX;
            // all the edges
            for (int j = 0; j < n; j++)
            {
                if (exists(i, j))
                {
                    type(i, j) = UNDETERMINED;
                }
            }
        }
    }
    // breadth first search
    void BFS(int, int &);
    // depth first search
    void DFS(int, int &);
    // decompose bi-connected component based on DFS
    void BCC(int, int &, Stack<int> &);
    // topological sorting based on DFS
    bool TSort(int, int &, Stack<Tv> *);
    template <typename PU>
    // priority first search
    void PFS(int, PU);

public:
    //vertex
    // the number
    int n;
    // return serial number
    virtual int insert(Tv const &) = 0;
    virtual Tv remove(int) = 0;
    // data
    virtual Tv &vertex(int) = 0;
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
    // the first adjacent vertex
    virtual int firstNbr(int) = 0;
    virtual int nextNbr(int, int) = 0;
    virtual VStatus &status(int) = 0;
    virtual int &dTime(int) = 0;
    virtual int &fTime(int) = 0;
    virtual int &parent(int) = 0;
    virtual int &priority(int) = 0;
    // edges
    // the number
    int e;
    virtual bool exists(int, int) = 0;
    virtual void insert(Te const &, int, int, int) = 0;
    virtual Te remove(int, int) = 0;
    virtual EType &type(int, int) = 0;
    virtual Te &edge(int, int) = 0;
    virtual int &weight(int, int) = 0;
    // algorithm
    void bfs(int);
    void dfs(int);
    void bcc(int);
    Stack<Tv> *tSort(int);
    void prim(int);
    void dijkstra(int);
    template <typename PU>
    void pfs(int, PU);
};
template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)
{
    reset();
    int clock = 0;
    int v = s;
    do
    {
        if (status(v) == UNDISCOVERED)
        {
            BFS(v, clock);
        }

    } while (s != (v = (++v % (this->n))));
}
template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock)
{
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);
    while (!Q.empty())
    {
        int v = Q.dequeue();
        dTime(v) = ++clock;
        for (int u = firstNbr(v); - 1 < u; u = nextNbr(v, u))
        {
            if (status(u) == UNDISCOVERED)
            {
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(v, u) = TREE;
                parent(u) = v;
            }
            else
            {
                type(v, u) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}
template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s)
{
    reset();
    int clock = 0;
    int v = s;
    do
    {
        if (status(v) == UNDISCOVERED)
        {
            DFS(v, clock);
        }

    } while (s != (v = (++v % (this->n))));
}
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock)
{
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    // for (int u = firstNbr(v); - 1 < u < (this->n); u = firstNbr(v))
    // {
    //     if (status(u) == UNDISCOVERED)
    //     {
    //         status(u) = DISCOVERED;
    //         type(v, u) = TREE;
    //         parent(u) = v;
    //     }
    //     else
    //     {
    //         type(v, u) = CROSS;
    //     }
    //     v = u;
    // }
    for (int u = firstNbr(v); - 1 < u; u = nextNbr(v, u))
    {
        switch (u)
        {
        case UNDISCOVERED:
        {
            status(v, u) = TREE;
            parent(u) = v;
            DFS(u, clock);
            break;
        }
        case DISCOVERED:
        {
            status(v,u)=BACKWARD;
            break;
        }
        default:
            {
                status(v,u)=(dTime(v)<dTime(u)?:FORWARD:CROSS);
                break;
            }
        }
    }
    status(v) = VISITED;
    // fTime:the time that v is visited
    fTime(v) = ++clock;
}
template <typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s)
{
    
}
