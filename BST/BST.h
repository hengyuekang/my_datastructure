#pragma once
#include "BinTree.h"
template <typename T>
class BST : public BinTree<T>
{
protected:
    // _hot point to the parent of result
    BinNodePosi(T) _hot;
    BinNodePosi(T) connect34(
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);

public:
    // many kinds of variations
    virtual BinNodePosi(T) search(const T &);
    virtual BinNodePosi(T) insert(const T &);
    virtual bool remove(const T &);
};
template <typename T>
BinNodePosi(T) BST<T>::search(const T &e)
{
    return searchIn(_root, e, _hot = NULL);
}
template <typename T>
static BinNodePosi(T) searchIn(BinNodePosi(T) & v, const T &e, BinNodePosi(T) & hot)
{
    if (!v || (e == v->_data))
    {
        return v;
    }
    hot = v;
    return searchIn(((e < v->_data) ? v->_lc : v->_rc), e, hot);
}
template <typename T>
BinNodePosi(T) BST<T>::insert(const T &e)
{
    BinNodePosi(T) &x = search(e);
    // have no the same node,x points to NULL
    // &:we know exactly which child is x for _hot
    if (!x)
    {
        x = new BinNode<T>(e, _hot);
        _size++;
        upgradeHeightAbove(x);
    }
    return x;
}
template <typename T>
bool BST<T>::remove(const T &e)
{
    BinNodePosi(T) &x = search(e);
    if (!x)
    {
        return false;
    }
    // different situations
    removeAt(x, _hot);
    _size--;
    upgradeHeightAbove(_hot);
    return true;
}
template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot)
{
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;
    // single child or no child
    if (!HasLChild(*x))
    {
        succ = x = x->_rc;
    }
    else if (!HasRChild(*x))
    {
        succ = x = x->_lc;
    }
    else
    {
        // temporary strage
        w = w->succ();
        swap(x->_data, w->_data);
        BinNodePosi(T) u = w->_parent;
        // new w,isolate original w
        ((u == x) ? u->_rc : u->_lc) = succ = w->_rc;
    }
    hot = w->_parent;
    // succ==NULL,no need to know his parent
    if (succ)
    {
        succ->_parent = hot;
    }
    // delete w in memory
    delete w;
    return succ;
}