#pragma once
#include "BinNode.h"
template <typename T>
class BinTree
{
protected:
    // member
    int _size = 0;
    BinNodePosi(T) _root = NULL;
    virtual int updateHeight(BinNodePosi(T) x);
    // ancestor height
    void updateHeightAbove(BinNodePosi(T) x);

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
    // read only
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodePosi(T) root() const { return _root; }
    // write
    BinNodePosi(T) insertAsRoot(T const &e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T> *&S);
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> *&S);
    // return size of x
    int remove(BinNodePosi(T) x);
    // remove x and from this,and save it as a tree
    BinTree<T> *secede(BinNodePosi(T) x);
    // traverse
    template <typename VST>
    void travLevel(VST &visit)
    {
        if (_root)
            _root->travLevel(visit);
    }
    template <typename VST>
    void travPre(VST &visit)
    {
        if (_root)
            _root->travPre(visit);
    }
    template <typename VST>
    void travIn(VST &visit)
    {
        if (_root)
            _root->travIn(visit);
    }
    template <typename VST>
    void travPost(VST &visit)
    {
        if (_root)
            _root->travPost(visit);
    }
    // compare
    bool operator<(BinTree<T> const &t)
    // lt:a standard comparison
    {
        return _root && t._root && lt(_root, t._root);
    }
    bool operator==(BinTree<T> const &t)
    {
        return _root && t._root && (_root == t._root);
    }
};
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
    // using max to compare
    int h1 = stature(x->_lc);
    int h2 = stature(x->_rc);
    int h = h1 >= h2 ? h1 : h2;
    x->_height = h + 1;
    return x->_height;
}
template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
    while (x)
    {
        updateHeight(x);
        x = x->_parent;
    }
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e)
{
    // generally,dont move root ,just add it for a empty tree
    _size = 1;
    return _root = new BinNode<T>(e);
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->_lc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->_rc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> *&S)
{
    x->_lc = S->_root;
    S->_root->_parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    // make T game over
    // delete:an object created by new
    S->_root = NULL;
    S->_size = 0;
    // a standard function
    delete S;
    S = NULL;
    return x;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> *&S)
{
    x->_rc = S->_root;
    S->_root->_parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    delete S;
    S = NULL;
    return x;
}
template <typename T>
// return size of tree which root is x
int BinTree<T>::remove(BinNodePosi(T) x)
{
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->_parent);
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
template <typename T>
BinTree<T> *BinTree<T>::secede(BinNodePosi(T) x)
{
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->_parent);
    BinTree<T> *p = new BinTree<T>;
    p->_root = x;
    x->_parent = NULL;
    p->_size = x->size();
    _size -= p->_size;
    return p;
}

