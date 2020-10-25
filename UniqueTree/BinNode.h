#ifndef BINNODE_H
#define BINNODE_H
#include "Stack.h"
// similar to list
#define BinNodePosi(T) BinNode<T> *
// height of empty tree is -1
#define stature(p) ((p) ? (p)->_height : -1)
/****************************************************************************
statement x:BinNode
*****************************************************************************/
#define IsRoot(x) (!((x)._parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x)._parent->_lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x)._parent->_rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x)._lc)
#define HasRChild(x) ((x)._rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) || HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
/*****************************************************
related pointers
******************************************************/
// brother
#define sibling(p) \
    (IsLChild(*(p)) ? (p)->_parent->_rc : (p)->_parent->_lc)
#define uncle(p) \
    (IsLChild(*((p)->_parent)) ? (p)->_parent->_parent->_rc : p->_parent->_parent->_lc)
#define FromParentTo(x) \
    (IsRoot(x) ? _root : (IsLChild(x) ? (x)._parent->_lc : (x)._parent->_rc))
// color
typedef enum
{
    RB_RED,
    RB_BLACK
} RBColor;
template <typename T>
class BinNode
{
    // public for simple describtion
public:
    // member
    T _data;
    BinNodePosi(T) _parent;
    BinNodePosi(T) _lc;
    BinNodePosi(T) _rc;
    int _height;
    // NULL Path Length
    int _npl;
    RBColor _color;

public:
    // ctor
    BinNode() : _parent(NULL), _lc(NULL), _rc(NULL), _height(0), _npl(1), _color(RB_RED) {}
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) : _data(e), _parent(p), _lc(lc), _rc(rc), _height(h), _npl(l), _color(c) {}
    //function
    // read only
    // size of subtree
    int size() const;
    BinNodePosi(T) succ() const;
    // write
    BinNodePosi(T) insertAsLC(T const &e);
    BinNodePosi(T) insertAsRC(T const &e);
    // traverse using pointer of function
    template <typename VST>
    void travLevel(VST &);
    template <typename VST>
    void travPre(VST &);
    template <typename VST>
    void travIn(VST &);
    template <typename VST>
    void travPost(VST &);
    // compare
    bool operator<(BinNode const &bn) { return _data < bn._data; }
    bool operator==(BinNode const &bn) { return _data == bn._data; }
};
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const &e)
{
    BinNodePosi(T) p = new BinNode(e, this);
    this->_lc = p;
    return p;
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const &e)
{
    // in template class,no need <T>
    BinNodePosi(T) p = new BinNode(e, this);
    this->_rc = p;
    return p;
}
template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST &visit)
{

    // regression
    travIn_R(this, visit);
}
template <typename T>
template <typename VST>
void BinNode<T>::travPre(VST &visit)
{
    //random choice
    // 5 kinds of situations

    // regression
    travPre_R(this, visit);
}
template <typename T>
template <typename VST>
void BinNode<T>::travPost(VST &visit)
{
    //random choice
    // 5 kinds of situations

    travPost_R(this, visit);
}
// must be put together
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST &visit)
{
    if (!x)
    {
        return;
    }
    visit(x->_data);
    travPre_R(x->_lc, visit);
    travPre_R(x->_rc, visit);
}
template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST &visit)
{
    if (!x)
    {
        return;
    }
    travPost_R(x->_lc, visit);
    travPost_R(x->_lc, visit);
    visit(x->_data);
}
template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST &visit)
{
    if (!x)
    {
        return;
    }
    travIn_R(x->_lc, visit);
    visit(x->_data);
    travIn_R(x->_rc, visit);
}
#endif
