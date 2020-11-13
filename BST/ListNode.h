#pragma once
// different from a normal int
using Rank = int;
// Macro definitions circumvent some syntax rules
#define ListNodePosi(T) ListNode<T> *

template <typename T>
class ListNode
{
    // make it more efficive to use node
public:
    T _data;
    // not null in case of exception visit
    ListNodePosi(T) _pred;
    ListNodePosi(T) _succ;

public:
    // ctor
    ListNode(){};
    // for header and trailer
    // p,s for _header and _trailer to initialize
    ListNode(T const &e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) : _data(e), _pred(p), _succ(s) {}
    // read only
    T data() const { return _data; }
    ListNodePosi(T) pred() const { return _pred; }
    ListNodePosi(T) succ() const { return _succ; }
    // write
    ListNodePosi(T) insertAsPred(const T &e);
    ListNodePosi(T) insertAsSucc(const T &e);
};
// comments first,then code
// when using Macro definitions to define variables,notice it is txt replacement,you would better to define a variable in one row
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e)
{
    ListNodePosi(T) p = new ListNode(e, this, _succ);
    // p->_succ = this->_pred->_succ;
    // this->_pred->_succ = p;
    // p->_pred = this->_pred;
    // this->_pred = p;
    // delete p;
    this->_succ->_pred = p;
    this->_succ = p;
    return p;
}
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const &e)
{
    // dont need template again
    ListNodePosi(T) p = new ListNode(e, _pred, this);
    // directl establishe some connections,in case that point to NULL
    // p->_succ = this->_succ;
    // this->_succ = p;
    // p->_pred = this;
    // p = p->_succ->_pred;
    this->_pred->_succ = p;
    this->_pred = p;
    // no need to delete,directly use
    return p;
}
