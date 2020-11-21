#include "graph.h"

Graph::Graph(int sz)
{
    maxVertices=sz;
    numVertices=0;
    numEdges=0;
    int i=0;
    int j=0;
    VerticesList=new int[maxVertices];
//    directly to matrix
    Edge=(int **)new int *[maxVertices];
    for(i=0;i<maxVertices;i++)
    {
        Edge[i]=new int[maxVertices];
    }
    for(i=0;i<maxVertices;i++)
    {
        for(j=0;j<maxVertices;j++)
        {
            Edge[i][j]=(i==j)? 0: maxWeight;
        }
    }
}
int Graph::getFirstNeighbor(int v)
{
    if(v!=-1)
    {
        for(int col=0;col<numVertices;col++)
        {
            if(Edge[v][col]>0&&Edge[v][col]<maxWeight)
                return col;
        }
    }
    return -1;
}
int Graph::getNextNeighbor(int v, int w)
{
    if(v!=-1&&w!=-1)
    {
        for(int col=w+1;col<numVertices;col++)
        {
            if(Edge[v][col]>0&&Edge[v][col]<maxWeight)
            {
                return  col;
            }
        }
    }
    return  -1;
}
void Graph::DFS(int loc,bool *visited)
{
    visited[loc]=true;
    int w=getFirstNeighbor(loc);
    while(w!=-1)
    {
        if(!visited[w])
        {
            DFS(w,visited);
        }
        w=getNextNeighbor(loc,w);
    }
}
void Graph::BFS(const int &v)
{
    int i=0;
    int w=0;
    int n=numVertices;
    bool *visited=new bool[n];
    for(i=0;i<n;i++)
    {
        visited[i]=false;
    }
    int loc=getVertexPos(v);
    visited[loc]=true;
    QQueue<int> Q;
    Q.enqueue(loc);
    while(!Q.empty())
    {
        Q.dequeue();
        w=getFirstNeighbor(loc);
        while (w!=-1)
        {
            if(!visited[w])
            {
                visited[w]=true;
                Q.enqueue(w);
            }
            w=getNextNeighbor(loc,w);
        }

    }
    delete []visited;
}
