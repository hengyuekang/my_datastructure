#ifndef BINNODE_H
#define BINNODE_H
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
#endif
