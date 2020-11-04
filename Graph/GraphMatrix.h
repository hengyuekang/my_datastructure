#pragma once
#include "Vector.h"
#include "Graph.h"
template <typename Tv>
struct Vertex
{
    Tv data;
    int inDegree;
    int outDegree;
    int VStatus;
    int status;
    int dTime;
    int fTime;
    int parent;
    int priority;
    Vertex(Tv const &d = (Tv)0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};
template <typename Te>
struct Edge
{
    Te data;
    int weight;
    EType type;
    Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};
template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{
private:
    // all the vertexes
    Vector<Vertex<Tv>> V;
    // graph matrix
    Vector<Vector<Edge<Te> *>> E;

public:
    GraphMatrix() { this->n = this->e = 0; }
    ~GraphMatrix()
    {
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->e; j++)
            {
                delete E[i][j];
            }
            delete V[i];
        }
    }
    // vertex:basical funduction
    virtual Tv &vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    virtual int firstNbr(int i) { return nextNbr(i, this->n); }
    virtual int nextNbr(int i, int j)
    {
        while ((-1 < j) && (!exists(i, --j)))
            ;
        return j;
    }
    virtual VStatus &status(int i) { return V[i].status; }
    virtual int &dTime(int i) { return V[i].dTime; }
    virtual int &fTime(int i) { return V[i].fTime; }
    virtual int &parent(int i) { return V[i].parent; }
    virtual int &priority(int i) { return V[i].priority; }
    // dynamic function
    // insert vertex
    virtual int insert(Tv const &vertex)
    {
        // possible edge
        for (int i = 0; i < this->n; i++)
        {
            E[this->j].insert(NULL);
        }
        (this->n)++;
        // edges
        E.insert(Vector<Edge<Te> *>(this->n, this->n, (Edge<Te> *)NULL));
        return V.insert(Vertex<Tv>(vertex));
    }
    // remove ith vertex
    virtual Tv remove(int i)
    {
        // i point to j
        for (int j = 0; j < this->n; j++)
        {
            if (exists(i, j))
            {
                delete E[i][j];
                V[j].inDegree--;
                (this->e)--;
            }
        }
        E.Remove(i);
        (this->n)--;
        // save as a result
        Tv vBak = vertex(i);
        V.Remove(i);
        // j point to i(Potential edge included)
        for (int j = 0; j < this->n; j++)
        {
            if (Edge<Te> *x = E[j].Remove(i))
            {
                delete x;
                V[j].outDegree--;
                (this->e)--;
            }
        }
        return vBak;
    }
    virtual bool exists(int i, int j)
    {
        return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
    }
    // basical function of edge
    virtual EType &type(int i, int j) { return E[i][j]->type; }
    virtual Te &edge(int i, int j) { return E[i][j]->data; }
    virtual int &weight(int i, int j) { return E[i][j]->weight; } // dynamic function
    virtual void insert(Te const &edge, int w, int i, int j)
    {
        // not exists:E[i][j]==NULL
        // exists:no need to insert
        if (exists(i, j))
        {
            // E[i][j]->data = edge;
            // E[i][j]->weight = w;
            return;
        }
        E[i][j] = new Edge<Te>(edge, w);
        (this->e)++;
        V[i].outDegree++;
        V[j].inDegree++;
    }
    virtual Te remove(int i, int j)
    {
        if (!exists(i, j))
        {
            return;
        }
        Te vBak=edge(i, j);
        delete E[i][j];
        E[i][j] = NULL;
        (this->e)--;
        V[i].outDegree--;
        V[j].inDegree--;
        return vBak;
    }
};
