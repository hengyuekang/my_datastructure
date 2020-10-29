#ifndef BINNODE_H
#define BINNODE_H
// similar to list
#define BinNodePosi(T) BinNode<T> *
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

public:
    // ctor
    BinNode() : _parent(NULL), _lc(NULL), _rc(NULL) {}
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL) : _data(e), _parent(p), _lc(lc), _rc(rc) {}
    //function
    template <typename VST>
    void travPre(VST &);
    template <typename VST>
    void travIn(VST &);
    template <typename VST>
    void travPost(VST &);
};
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
    // regression
    travPre_R(this, visit);
}
template <typename T>
template <typename VST>
void BinNode<T>::travPost(VST &visit)
{
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
