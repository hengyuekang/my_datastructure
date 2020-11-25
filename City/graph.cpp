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
void Graph::Kruskal(MinSpanTree &MST)
{
    MSTEdgeNode ed;
    int u=0;
    int v=0;
    int count=0;
    int n=NumberOfVertices();
    int m=NumberOfEdges();
    MinHeap<MSTEdgeNode> H(m);
    UFSets F(n);
    for(u=0;u<n;u++)
    {
        for(v=u+1;v<n;v++)
        {
//            have edge
            if(getWeight(u,v)!=maxValue)
            {
                ed.tail=u;
                ed.head=v;
                ed.key=getWeight(u,v);
                H.Insert(ed);
            }

        }
    }
    count=1;
    while (count<n)
    {
        H.Remove(ed);
        u=F.Find(ed.tail);
        v=F.Find(ed.head);
        if(u!=v)
        {
            F.Union(u,v);
            MST.Insert(ed);
            count++;
        }
    }
}
void Graph::Prim(const int u0, MinSpanTree &MST)
{
    MSTEdgeNode ed;
    int i=0;
    int u=0;
    int v=0;
    int count=0;
    int n=NumberOfVertices();
    int m=NumberOfEdges();
    u=getVertexPos(u0);
    MinHeap<MSTEdgeNode> H(m);
    bool *Vmst=new bool[n];
    for(i=0;i<n;i++)
    {
        Vmst[i]=false;
    }
    Vmst[u]=true;
    do
    {
        v=getFirstNeighbor(u);
        while(v!=-1)
        {
            if(!Vmst[v])
            {
                ed.tail=u;
                ed.head=v;
                ed.key=getWeight(u,v);
                H.Insert(ed);
            }
            v=getNextNeighbor(u,v);
        }
        while(!H.IsEmpty()&&count<n)
        {
            H.Remove(ed);
            if(!Vmst[ed.head])
            {
                MST.Insert(ed);
                u=ed.head;
                Vmst[u]=true;
                count++;
                break;
            }
        }

    }while (count<n);
}
void Graph::Dijkstra(int v, int *dist, int *path)
{
    int n=NumberOfVertices();
    bool *S=new bool[n];
    int i=0;
    int j=0;
    int k=0;
    int w=0;
    int min=0;
    for(i=0;i<n;i++)
    {
        dist[i]=getWeight(v,i);
        S[i]=false;
        if(i!=v&&dist[i]<maxValue)
        {
            path[i]=v;
        }
        else
        {
            path[i]=-1;
        }
    }
    S[v]=true;
    dist[v]=0;
    for(i=0;i<n-1;i++)
    {
        min=maxValue;
        int u=v;
        for(j=0;j<n;j++)
        {
            if(!S[i]&&dist[j]<min)
            {
                u=j;
                min=dist[j];
            }
        }
        S[u]=true;
        for(k=0;k<n;k++)
        {
            w=getWeight(u,k);
            if(!S[k]&&w<maxValue&&w+dist[u]<dist[k])
            {
                dist[k]=dist[u]+w;
                path[k]=u;
            }
        }
    }
}
