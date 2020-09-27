#ifndef LISTNODE_H
#define LISTNODE_H
// different from normal int
using Rank = int;
// Macro definitions circumvent some syntax rules
#define ListNodePosi(T) ListNode<T> *

template <typename T>
class ListNode
{
    // make it more efficive to use node
public:
    T _coef;
    int _exp;
    // not null in case of exception visit
    ListNodePosi(T) _pred;
    ListNodePosi(T) _succ;

public:
    // ctor
    ListNode(){};
    // for header and trailer
    // p,s for _header and _trailer to initialize
    ListNode(T const &e, int &x = 0, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) : _coef(e), _exp(x), _pred(p), _succ(s) {}
    // read only
    T coef() const { return _coef; }
    int exp() const { return _exp; }
    ListNodePosi(T) pred() const { return _pred; }
    ListNodePosi(T) succ() const { return _succ; }
    // write
    ListNodePosi(T) insertAsPred(T const &e, int &x);
    ListNodePosi(T) insertAsSucc(T const &e, int &x);
};
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e, int &x)
{
    ListNodePosi(T) p = new ListNode(e, x, this, _succ);
    this->_succ->_pred = p;
    this->_succ = p;
    return p;
}
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const &e, int &x)
{
    ListNodePosi(T) p = new ListNode(e, x, _pred, this);
    this->_pred->_succ = p;
    this->_pred = p;
    return p;
}
#endif