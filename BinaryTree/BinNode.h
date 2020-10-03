#ifndef BINNODE_H
#define BINNODE_H
// similar to list
#define BinNodePosi(T) BinNode<T> *
// height of empty tree is -1
#define stature(p)               \
    do                           \
    {                            \
        (p) ? (p)->_height : -1; \
    } while (0);
/****************************************************************************
statement x:BinNode
*****************************************************************************/
#define IsRoot(x)    \
    do               \
    {                \
        !(x)._parent \
    } while (0);
#define IsLChild(x)                            \
    do                                         \
    {                                          \
        !IsRoot(x) && (x) == (x)._parent->_lc; \
    } while (0);
#define IsRChild(x)                              \
    do                                           \
    {                                            \
        ` !IsRoot(x) && (x) == (x)._parent->_rc; \
    } while (0);
#define HasParent(x) \
    do               \
    {                \
        !IsRoot(x);  \
    } while (0);
#define HasLChild(x) \
    do               \
    {                \
        (x)._lc;     \
    } while (0);
#define HasRChild(x) \
    do               \
    {                \
        (x)._rc;     \
    } while (0);
#define HasChild(x)                   \
    do                                \
    {                                 \
        HasLChild(x) || HasRChild(x); \
    } while (0);
#define HasBothChild(x)               \
    do                                \
    {                                 \
        HasLChild(x) || HasRChild(x); \
    } while (0);
#define IsLeaf(x)     \
    do                \
    {                 \
        !HasChild(x); \
    } while (0);
/*****************************************************
related pointers
******************************************************/
// brother
#define sibling(p)                                            \
    do                                                        \
    {                                                         \
        IsLChild(*p) ? (p)->_parent->_rc : (p)->_parent->_lc; \
    } while (0);
#define uncle(p)                                                                         \
    do                                                                                   \
    {                                                                                    \
        IsLChild(*(p->_parent)) ? (p)->_parent->_parent->_rc : p->_parent->_parent->_lc; \
    } while (0);
#define FromParentTo(x)                                                          \
    do                                                                           \
    {                                                                            \
        IsRoot(x) ? _root : (IsLChild(x) ? (x)._parent->_lc : (x)._parent->_rc); \
    } while (0);
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
    // traverse
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
        travIn_R(this, visit);
        break;
    }
}

#endif
