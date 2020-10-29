#pragma once
#include "Stack.h"
#include "Queue.h"
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
    BinNodePosi(T) succ();
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
    //random choice
    // 5 kinds of situations
    switch (rand() % 5)
    {
    case 1:
        travIn_I1(this, visit);
        break;
    case 2:
        travIn_I2(this, visit);
        break;
    case 3:
        travIn_I3(this, visit);
        break;
    case 4:
        travIn_I4(this, visit);
        break;
    default:
        // regression
        travIn_R(this, visit);
        break;
    }
}
template <typename T>
template <typename VST>
void BinNode<T>::travPre(VST &visit)
{
    //random choice
    // 5 kinds of situations
    switch (rand() % 5)
    {
    case 1:
        travPre_I1(this, visit);
        break;
    case 2:
        travPre_I2(this, visit);
        break;
    case 3:
        travPre_I3(this, visit);
        break;
    case 4:
        travPre_I4(this, visit);
        break;
    default:
        // regression
        travPre_R(this, visit);
        break;
    }
}
template <typename T>
template <typename VST>
void BinNode<T>::travPost(VST &visit)
{
    //random choice
    // 5 kinds of situations
    switch (rand() % 5)
    {
        // iteration
    case 1:
        travPost_I1(this, visit);
        break;
    case 2:
        travPost_I2(this, visit);
        break;
    case 3:
        travPost_I3(this, visit);
        break;
    case 4:
        travPost_I4(this, visit);
        break;
    default:
        // regression
        travPost_R(this, visit);
        break;
    }
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
template <typename T, typename VST>
void travPre_I1(BinNodePosi(T) x, VST &visit)
{
    // put rc fist because stack is "first in,last out"
    Stack<BinNodePosi(T)> S;
    if (x)
    {
        S.push(x);
    }
    while (!S.empty())
    {
        x = S.pop();
        visit(x->_data);
        if (HasRChild(*x))
        {
            S.push(x->_rc);
        }
        if (HasLChild(*x))
        {
            S.push(x->_lc);
        }
    }
}
template <typename T, typename VST>
void visitalongleftbrench(BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S)
{
    while (x)
    {
        visit(x->_data);
        S.push(x->_rc);
        x = x->_lc;
    }
}
template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST &visit)
{
    Stack<BinNodePosi(T)> S;
    while (1)
    {
        // push NULL even have no rc
        visitalongleftbrench(x, visit, S);
        if (S.empty())
        {
            break;
        }
        x = S.pop();
    }
}
template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit)
{
    Stack<BinNodePosi(T)> S;
    while (1)
    {
        goAlongLeftBranch(x, S);
        if (S.empty())
        {
            break;
        }
        x = S.pop();
        // only once
        visit(x->_data);
        x = x->_rc;
    }
}
template <typename T>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)> &S)
{
    while (x)
    {
        S.push(x);
        x = x->_lc;
    }
}
template <typename T>
BinNodePosi(T) BinNode<T>::succ()
{
    BinNodePosi(T) S = this;
    if (_rc)
    {
        S = _rc;
        while (HasLChild(*S))
        {
            S = S->_lc;
        }
    }
    else
    {
        // include the last one
        while (IsRChild(*S))
        {
            S = S->_parent;
        }
        S = S->_parent;
    }
    return S;
}
template <typename T, typename VST>
void travIn_I2(BinNodePosi(T) x, VST &visit)
{
    Stack<BinNodePosi(T)> S;
    while (1)
    {
        if (x)
        {
            S.push(x);
            x = x->_lc;
        }
        else if (!S.empty())
        {
            x = S.pop();
            visit(x->_data);
            x = x->_rc;
        }
        else
        {
            break;
        }
    }
}
template <typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST &visit)
{
    x = firstNode(x);
    while (x)
    {
        visit(x->_data);
        x = x->succ();
    }
}
template <typename T>
BinNodePosi(T) firstNode(BinNodePosi(T) x)
{
    if (HasLChild(*x))
    {
        x = x->_lc;
    }
    return x;
}
template <typename T, typename VST>
void travPost_I1(BinNodePosi(T) x, VST &visit)
{
    Stack<BinNodePosi(T)> S;
    gotoHLVFL(x, S);
    x = S.pop();
    while (1)
    {
        visit(x->_data);
        if (IsLChild(*x) && HasRChild(*(x->_parent)))
        {
            x = x->_parent->_rc;
            gotoHLVFL(x, S);
        }
        if (S.empty())
        {
            break;
        }
        x = S.pop();
    }
}
// wont change the value of pointer!!!
template <typename T>
static void gotoHLVFL(BinNodePosi(T) x, Stack<BinNodePosi(T)> &S)
{
    while (1)
    {
        S.push(x);
        if (HasLChild(*x))
        {
            x = x->_lc;
            continue;
        }
        if (!HasLChild(*x) && HasRChild(*x))
        {
            x = x->_rc;
            continue;
        }
        if (!HasChild(*x))
        {
            break;
        }
    }
}
template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST &visit)
{
    Queue<BinNodePosi(T)> Q;
    Q.enqueue(this);
    while (!Q.empty())
    {
        BinNodePosi(T) x = Q.dequeue();
        visit(x->_data);
        if (HasLChild(*x))
        {
            Q.enqueue(x->_lc);
        }
        if (HasRChild(*x))
        {
            Q.enqueue(x->_rc);
        }
    }
}

