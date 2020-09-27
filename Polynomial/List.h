// The template class does not support split compilation
#ifndef LIST_H
#define LIST_H
#include "stdafx.h"
template <typename T>
class List
{
private:
    ListNodePosi(T) _header = NULL;
    ListNodePosi(T) _trailer = NULL;
    Rank _size = 0;

protected:
    // make _header and _trailer not point to NULL
    void init();
    // delete every node
    void clear();
    // copy n nodes from p
    void copyNodes(ListNodePosi(T) p, int n);

public:
    // ctor
    List() { init(); }
    // copy constructor
    List(List<T> const &L)
    {
        this->init();
        copyNodes(L.first(), L.size());
    }
    // delete all the nodes(include header and trailer)
    ~List() { clear(); }
    // read only
    Rank size() const { return _size; }
    ListNodePosi(T) first() const { return _header->_succ; }
    int getMaxExp() const { return _trailer->_pred->_exp; }

    // write
    ListNodePosi(T) insertAsFirst(T const &e, int &x);
    ListNodePosi(T) insertAsLast(T const &e, int &x);
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const &e, int &x);
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const &e, int &x);
    ListNodePosi(T) remove(ListNodePosi(T) p);
    void Input(std::istream &is);
    void Add(List<T> &L);
    void Output(std::ostream &os);
    void sortExp();
};
template <typename T>
//when inserting a node, _header ,_trailer not points to NULL
void List<T>::init()
{
    // default:_header,_trailer points to NULL
    // cant find _succ,_pred
    _header = new ListNode<T>;
    _trailer = new ListNode<T>;
    // point to something
    _header->_succ = _trailer;
    _trailer->_pred = _header;
    _trailer->_succ = NULL;
    _header->_pred = NULL;
    _size = 0;
}
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const &e, int &x)
{
    // once ues function about insertion,_size++
    return insertAfter(_header, e, x);
}
template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const &e, int &x)
{
    return insertBefore(_trailer, e, x);
}
template <typename T>
// a direction a time,from back to front
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const &e, int &x)
{
    _size++;
    return p->insertAsSucc(e, x);
}
template <typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const &e, int &x)
{
    _size++;
    return p->insertAsPred(e, x);
}
template <typename T>
ListNodePosi(T) List<T>::remove(ListNodePosi(T) p)
{
    ListNodePosi(T) pa = p->_succ;
    (p->_pred)->_succ = p->_succ;
    (p->_succ)->_pred = p->_pred;
    delete p;
    _size--;
    return pa;
}
template <typename T>
// bubble sort
void List<T>::sortExp()
{
    ListNodePosi(T) p1 = _header->_succ;
    ListNodePosi(T) p2 = _trailer->_pred;
    while (p2 != _header)
    {
        while (p1 != p2)
        {
            if ((p1->_exp) > (p1->_succ->_exp))
            {
                ListNodePosi(T) temp = new ListNode<T>(p1->_coef, p1->_exp);
                p1->_exp = p1->_succ->_exp;
                p1->_coef = p1->_succ->_coef;
                p1->_succ->_exp = temp->_exp;
                p1->_succ->_coef = temp->_coef;
                delete temp;
            }
            p1 = p1->_succ;
        }
        p1 = _header->_succ;
        p2 = p2->_pred;
    }
}
template <typename T>
void List<T>::copyNodes(ListNode<T> *p, int n)
{
    List();
    while ((n--) > 0)
    {
        // not use,not store
        insertAfter(_header, p->_coef, p->_exp);
        p = p->_succ;
    }
}
template <typename T>
void List<T>::clear()
{
    // delete all the nodes
    ListNodePosi(T) p = _header;
    while (p != _trailer)
    {
        p = p->_succ;
        delete p->_pred;
    }
    delete p;
}
template <typename T>
void List<T>::Input(std::istream &is)
{
    ListNodePosi(T) p = _header;
    T e;
    int x;
    // end with 0 -1
    while ((is >> e >> x) && ((e != 0) || (x != -1)))
    {
        p = insertAfter(p, e, x);
    }
}
template <typename T>
void List<T>::Add(List<T> &L)
{
    // this store the polynomial has a bigger maxExp
    ListNodePosi(T) p1 = L.first();
    ListNodePosi(T) p2 = first();
    while (p1 != L._trailer)
    {
        // fix p1
        while (p2 != NULL)
        {
            // p2:scan "this"
            if ((p1->_exp) == (p2->_exp))
            {
                if (((p1->_coef) + (p2->_coef) == 0))
                {
                    // res=0,delete it
                    p2 = this->remove(p2);
                }
                else
                {
                    if ((p1->_exp) == 0)
                    {
                        // store constant term in L
                        // not let it go to this->_trailer
                        p2 = this->insertAsFirst(p1->_coef, p1->_exp);
                        break;
                    }
                    // store result
                    p2->_coef += p1->_coef;
                }
                break;
            }
            else if (p2 == _trailer)
            {
                // if havent same exp,p2 to this->last()
                p2 = this->insertBefore(p2, p1->_coef, p1->_exp);
                break;
            }
            p2 = p2->_succ;
        }
        // scan this from first
        p2 = first();
        p1 = p1->_succ;
    }
}
template <typename T>
void List<T>::Output(std::ostream &os)
{
    ListNodePosi(T) p = first();

    while (p != _trailer)
    {
        // the first term
        if (p == first())
        {
            // 1
            if ((p->_coef) == 1)
            {
                // exp==0
                if ((p->_exp) == 0)
                {
                    // no x
                    os << "1";
                }
            }
            else
            {
                // -1
                if ((p->_coef) == -1)
                {
                    os << "-";
                }
                else
                {
                    // other constants term
                    os << p->_coef;
                }
            }
            // exp!=0
            if ((p->_exp) == 1)
            {
                os << "x";
            }
            else
            {
                if ((p->_exp) > 1)
                {
                    os << "x^" << p->_exp;
                }
            }
        }
        else
        {
            // other terms
            // positive coefficient
            if ((p->_coef) > 0)
            {
                os << "+";
                if ((p->_coef) != 1)
                {
                    os << p->_coef;
                }
            }
            else
            // nagative coefficient
            {
                // -1
                if ((p->_coef) == -1)
                {
                    os << "-";
                }
                else
                {
                    os << p->_coef;
                }
            }
            // 1
            if ((p->_exp) == 1)
            {
                os << "x";
            }
            else
            {

                os << "x^" << p->_exp;
            }
        }
        // next
        p = p->_succ;
    }
    os << std::endl;
}
#endif