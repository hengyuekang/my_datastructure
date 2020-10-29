#ifndef BINTREE_H
#define BINTREE_H
#include "BinNode.h"
template <typename T>
class BinTree
{
protected:
    // member
    int _size = 0;
    BinNodePosi(T) _root = NULL;

public:
    // ctor
    BinTree() = default;
    ~BinTree()
    {
        if (_size > 0)
        {
            remove(_root);
        }
    }
    // function
    // return size of x
    int remove(BinNodePosi(T) x);
};
template <typename T>
// return size of tree which root is x
int BinTree<T>::remove(BinNodePosi(T) x)
{
    FromParentTo(*x) = NULL;
    upgradeHeightAbove(x->_parent);
    // delete every node after x
    int n = removeAt(x);
    // size of tree
    _size -= n;
    return n;
}
template <typename T>
// global function
static int removeAt(BinNodePosi(T) x)
{
    if (!x)
    {
        return 0;
    }
    int res = removeAt(x->_lc) + removeAt(x->_rc) + 1;
    // x not deleted
    delete x;
    x = NULL;
    return res;
}
#endif
