#include "ufsets.h"

UFSets::UFSets(int sz)
{
    size=sz;
    parent=new int[size];
    for(int i=0;i<size;i++)
    {
        parent[i]=-1;
    }
}
int UFSets::Find(int x)
{
    if(parent[x]<0)
    {
        return  x;
    }
    else
    {
        return  (Find(parent[x]));
    }
}
void UFSets::Union(int Root1, int Root2)
{
     parent[Root1]+=parent[Root2];
     parent[Root2]=Root1;
}
