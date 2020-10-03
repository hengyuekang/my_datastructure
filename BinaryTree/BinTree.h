#ifndef BINTREE_H
#define BINTREE_H
#include "stdafx.h"
template <typename T>
class BinTree
{
protected:
    // member
    int _size = 0;
    BinNodePosi(T) _root = NULL;
    virtual int upgradeHeight(BinNodePosi(T) x);
    // ancestor height
    void upgradeHeightAbove(BinNodePosi(T) x);

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
    BinNodePosi(T) insertAsRoot(T const &e)
    {
        _root->_data = e;
        return _root;
    }
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T> *&T);
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> *&T);
    // return size of x
    int remove(BinNodePosi(T) x);
    // remove x and save it
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
    // bool operator< ( BinTree<T> const& t )
    // { return _root && t._root && lt ( _root, t._root ); }
    bool operator==(BinTree<T> const &t)
    {
        return _root && t._root && (_root == t._root);
    }
};
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
    BinNodePosi(T) p = new BinNode(e, x);
    x->_lc = p;
    return p;
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
    BinNodePosi(T) p = new BinNode(e, x);
    x->_rc = p;
    return p;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> *&T)
{
    x->_lc = T->_root;
    return T->_root;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> *&T)
{
    x->_rc = T->_root;
    return T->_root;
}
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
    int res = x->_height;
    if (IsLChild)
    {
        x->_parent->_lc = NULL;
        delete x;
    }
    if (IsRChild)
    {
        x->_parent->_rc = NULL;
        delete x;
    }
    return res;
}
#endif
