#include "minspantree.h"

int MinSpanTree::Insert(MSTEdgeNode &item)
{
    int i=0;
    for(i=0;i<maxSize;i++)
    {
        if(edgevalue[i].head==-1)
        {
            edgevalue[i]=item;
            break;
        }
    }
    return  i;
}
