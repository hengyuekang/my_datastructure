#pragma once
#include "BST.h"
// ideal balance state
#define Balanced(x) (stature((x)._lc) == stature((x)._rc))
// balance factor=abs(height(v->lc)-height(v->rc))
#define BalFac(x) (stature((x)._lc) - stature((x)._rc))
// balance condition
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))
// assure adjustment method
// if the same stature,then get the same side as parent
#define tallerChild(x) ( \
    stature((x)->_lc) > stature((x)->_rc) ? (x)->_lc : (stature((x)->_lc) < stature((x)->_rc) ? (x)->_rc : (IsLChild(*(x)) ? (x)->_lc : (x)->_rc)))
template <typename T>
class AVL : public BST<T>
{
public:
    BinNodePosi(T) insert(const T &);
    bool remove(const T &);
};
template <typename T>
BinNodePosi(T) AVL<T>::insert(const T &e)
{
    // x:point to a proper place
    BinNodePosi(T) &x = search(e);
    if (x)
    {
        return x;
    }
    BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);
    (this->_size)++;
    // not balance
    for (BinNodePosi(T) g = _hot; g; g = g->_parent)
    {
        if (!AvlBalanced(*g))
        {
            // adjust,put in original tree
            FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
            break;
        }
        else
        {
            this->upgradeHeight(g);
        }
    }
    // position of new node
    return xx;
}
template <typename T>
bool AVL<T>::remove(const T &e)
{
    BinNodePosi(T) &x = search(e);
    if (!x)
    {
        return false;
    }
    removeAt(x, _hot);
    (this->_size)--;
    for (BinNodePosi(T) g = _hot; g; g = g->_parent)
    {
        if (!AvlBalanced(*g))
        {
            // adjust,put in original tree
            g = FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
        }
        this->upgradeHeight(g);
    }
    return true;
}
