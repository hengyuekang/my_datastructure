#ifndef MINSPANTREE_H
#define MINSPANTREE_H
const float maxValue=9999.0;
struct MSTEdgeNode
{
    int tail=0;
    int head=0;
    int key=0;
    MSTEdgeNode():tail(-1),head(-1),key(0) {}
    bool operator<=(MSTEdgeNode& n1)
    {
        if(key<=n1.key)
        {
            return  true;
        }
        else
        {
            return  false;
        }
    }
    bool operator>(MSTEdgeNode& n1)
    {
        if(key>n1.key)
        {
            return  true;
        }
        else
        {
            return  false;
        }
    }
};

class MinSpanTree
{
protected:
    MSTEdgeNode *edgevalue;
    int maxSize=0;
    int n=0;
public:
    MinSpanTree(int sz=10) :maxSize(sz),n(0)
    {
        MSTEdgeNode temp;
        edgevalue=new MSTEdgeNode[sz];
        for(int i=0;i<sz;i++)
        {
            edgevalue[i]=temp;
        }
    }
    int Insert(MSTEdgeNode &item);
};

#endif // MINSPANTREE_H
