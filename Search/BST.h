#pragma once
#include "BinTree.h"
template <typename T>
class BST : public BinTree<T>
{
protected:
    // _hot point to the _parent of result
    BinNodePosi(T) _hot;
    // connect 3 nodes,4 subtrees
    BinNodePosi(T) connect34(
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
    // adjust x,_parent,grand_parent
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);

public:
    // many kinds of variations
    virtual BinNodePosi(T) & search(const T &);
    virtual BinNodePosi(T) insert(const T &);
    virtual bool remove(const T &);
};
template <typename T>
    BinNodePosi(T) & BST<T>::search(const T &e)
{
    return searchIn((this->_root), e, _hot = NULL);
}
template <typename T>
    static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T &e, BinNodePosi(T) & hot)
{
    if (!v || (e == v->_data))
    {
        return v;
    }
    // hot save the _parent of v
    hot = v;
    return searchIn(((e < v->_data) ? v->_lc : v->_rc), e, hot);
}
template <typename T>
BinNodePosi(T) BST<T>::insert(const T &e)
{
    // not only prevent from inserting the repeat node,but also chage the insertion position
    // return &:x can be directly inserted into BST
    BinNodePosi(T) &x = search(e);
    // have no the same node,x points to NULL
    if (!x)
    {
        x = new BinNode<T>(e, _hot);
        (this->_size)++;
        this->updateHeightAbove(x);
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
    (this->_size)--;
    this->updateHeightAbove(_hot);
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
        std::swap(x->_data, w->_data);
        BinNodePosi(T) u = w->_parent;
        // new w,isolate original w
        ((u == x) ? u->_rc : u->_lc) = succ = w->_rc;
    }
    hot = w->_parent;
    // succ==NULL,no need to know his _parent
    if (succ)
    {
        succ->_parent = hot;
    }
    // delete w in memory
    delete w;
    return succ;
}
// include all the situations!!!!!!!!!!!!
// nb!!!!!!!!
template <typename T>
BinNodePosi(T) BST<T>::connect34(
    BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
    BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
    // both-way connection
    a->_lc = T0;
    if (T0)
        T0->_parent = a;
    a->_rc = T1;
    if (T1)
        T1->_parent = a;
    BinTree<T>::updateHeight(a);
    c->_lc = T2;
    if (T2)
        T2->_parent = c;
    c->_rc = T3;
    if (T3)
        T3->_parent = c;
    BinTree<T>::updateHeight(c);
    b->_lc = a;
    a->_parent = b;
    b->_rc = c;
    c->_parent = b;
    BinTree<T>::updateHeight(b);
    return b;
}
template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)
{
    // v:grandson
    BinNodePosi(T) p = v->_parent;
    BinNodePosi(T) g = p->_parent;
    if (IsLChild(*p))
    {
        // zig
        if (IsLChild(*v))
        {
            // directly be the new subtree
            p->_parent = g->_parent;
            return connect34(v, p, g, v->_lc, v->_rc, p->_rc, g->_rc);
        }
        // zig,zag
        else
        {
            v->_parent = g->_parent;
            return connect34(p, v, g, p->_lc, v->_lc, v->_rc, g->_rc);
        }
    }
    else
    {
        if (IsRChild(*v))
        { /* zag-zag */
            p->_parent = g->_parent;
            return connect34(g, p, v, g->_lc, p->_lc, v->_lc, v->_rc);
        }
        else
        { /* zag-zig */
            v->_parent = g->_parent;
            return connect34(g, v, p, g->_lc, v->_lc, v->_rc, p->_rc);
        }
    }
}