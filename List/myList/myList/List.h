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
    // make _header and _trailer doesn't' point to NULL
    void init();
    // delete every node
    int clear();
    // copy n nodes from p
    void copyNodes(ListNodePosi(T) p, int n);
    // merge two sections of two sorted lists
    void merge(ListNodePosi(T) &, int, List<T> &, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T) &, int);
    void selectSort(ListNodePosi(T), int);
    void insertSort(ListNodePosi(T), int);

public:
    // ctor
    List() { init(); }
    // copy constructor
    List(List<T> const &L) { copyNodes(L.first(), _size); }
    // copy n nodes from L.r
    List(List<T> const &L, Rank r, int n);
    List(ListNodePosi(T) p, int n) { copyNodes(p, n); }
    // delete all the nodes(include header and trailer)
    // ~List();
    // read only
    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }
    // visit like an array
    T &operator[](Rank r) const;
    ListNodePosi(T) first() const { return _header->_succ; }
    ListNodePosi(T) last() const { return _trailer->_pred; }
    // Determine if there is data in node of p
    bool valid(ListNodePosi(T) p) const { return p && (p != _header) && (p != _trailer); }
    bool disordered() const;
    ListNodePosi(T) find(T const &e) const { return find(e, _size, _trailer); }
    // find from a section,General to special
    ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;
    // find tne one closest to e and the most rank in a sorted list
    ListNodePosi(T) search(T const &e) const { return search(e, _size, _trailer); }
    ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;
    // find the max after p
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n) const;
    ListNodePosi(T) selectMax() const { return selectMax(_header->_succ, _size); }

    // write
    ListNodePosi(T) insertAsFirst(T const &e);
    ListNodePosi(T) insertAsLast(T const &e);
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const &e);
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const &e);
    T remove(ListNodePosi(T) p);
    // merge the whole two lists
    void merge(List<T> &L) { merge(first(), size(), L, L.first(), L.size()); }
    void sort(ListNodePosi(T) p, int n);
    void sort() { sort(first(), _size); }
    // delete duplicate nodes
    void deduplicate();
    // delete duplicate nodes in a sorted list
    void uniquify();

    void reverse();
    // traverse all the nodes and do some works
    // pointer to function
    void traverse(void (*)(T &));
    template <typename VST>
    void traverse(VST &);
};
template <typename T>
// in cast when inserting a node and _header ,_trailer points to NULL
void List<T>::init()
{
    // default:_header,_trailer points to NULL
    // cant find _succ,_pred
    _header = new ListNode<T>;
    _trailer = new ListNode<T>;
    // have something to point to
    _header->_succ = _trailer;
    _trailer->_pred = _header;
    _trailer->_succ = NULL;
    _header->_pred = NULL;
    _size = 0;
}
template <typename T>
// present Posi with Rank
T &List<T>::operator[](Rank r) const
{
    ListNodePosi(T) p = first();
    for (int i = 0; i < r; i++)
    {
        p = p->_succ;
    }
    // while (0 < r--)
    // {
    //     p = p->_succ;
    // }
    return p->_data;
}
template <typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T) p) const
{
    // find after p
    // int cnt = 0;
    // while (cnt != n)
    // {
    //     if (p->_data == e)
    //     {
    //         return p;
    //     }
    //     p = p->_succ;
    //     cnt++;
    // }
    // find before p
    while ((n--) > 0)
    {
        if (e == (p = p->_pred->_data))
        {
            return p;
        }
    }
    return NULL;
}
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const &e)
{
    // once ues function about insertion,_size++
    return insertAfter(_header, e);
}
template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const &e)
{
    return insertBefore(_trailer, e);
}
template <typename T>
bool List<T>::disordered() const
{
    ListNodePosi(T) p = _trailer->_pred;
    while (p != _header->_succ)
    {
        if ((p->_data) < (p->_pred->_data))
        {
            return false;
        }
        p = p->_pred;
    }
    return true;
}
// template <typename T>
// ListNodePosi(T) List<T>::insertAsFirst(T const &e)
// {
//     ListNodePosi(T) nNode = new ListNode<T>(e);
//     _header->_succ = nNode;
//     nNode->_pred = _header;
//     delete nNode;
//     return _header->_succ;
// }
// template <typename T>
// ListNodePosi(T) List<T>::insertAsLast(T const &e)
// {
//     ListNodePosi(T) nNode = new ListNode<T>(e);
//     _trailer->_pred = nNode;
//     nNode->_succ = _trailer;
//     delete nNode;
//     return _trailer->_pred;
// }
// template <typename T>
// ListNodePosi(T) List<T>::find(T const &e) const
// {
//     ListNodePosi(T) p = _header->_succ;
//     while (p != _trailer)
//     {
//         if (p->_data == e)
//         {
//             return p;
//         }
//         p = p->_succ;
//     }
//     return NULL;
// }
// find out which function first to test others
template <typename T>
// a direction a time,from back to front
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const &e)
{
    // ListNodePosi(T) nNode = new ListNode<T>(e);
    // nNode->_succ = p->_succ;
    // p->_succ = nNode;
    // nNode->_pred = (nNode->_succ)->_pred;
    // (nNode->_succ)->_pred = nNode;
    // _size++;
    // delete nNode;
    _size++;

    return p->insertAsSucc(e);
}
template <typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const &e)
{
    _size++;
    return p->insertAsPred(e);
}
template <typename T>
T List<T>::remove(ListNodePosi(T) p)
{
    T res = p->_data;
    (p->_pred)->_succ = p->_succ;
    (p->_succ)->_pred = p->_pred;
    delete p;
    _size--;
    return res;
}
template <typename T>
void List<T>::uniquify()
{
    if (disordered())
    {
        ListNodePosi(T) p = _header->_succ;
        while (p != _trailer)
        {
            if ((p->_data) == (p->_succ->_data))
            {
                int res = remove(p->_succ);
            }
            p = p->_succ;
        }
    }
    else
    {
        std::cout << "order first!" << std::endl;
    }
}
// template <typename T>
// void List<T>::traverse()
// {
//     ListNodePosi(T) p = _header->_succ;
//     while (p != _trailer)
//     {
//         p = p->_succ;
//     }
// }
// template <typename T>
// void List<T>::sort()
// {
//     ListNodePosi(T) hBound = _trailer->_pred;
//     ListNodePosi(T) p = _header->_succ;
//     while (hBound != _header)
//     {
//         while (p != hBound)
//         {
//             if ((p->_data) >= (p->_succ->_data))
//             {
//                 auto nNode = insertBefore(*p, (p->_succ->_data));
//                 int res = remove(p->_succ);
//             }
//             p = p->_succ;
//         }
//         hBound = hBound->_pred;
//     }
// }
// template <typename T>
// ListNodePosi(T) List<T>::search(T const &e) const
// {
//     if (disordered())
//     {
//         ListNodePosi(T) maxPosi;
//         ListNodePosi(T) p = _header->_succ;
//         while (p != _trailer)
//         {
//             if ((p->_data) <= e)
//             {
//                 maxPosi = p;
//             }
//             p = p->_succ;
//         }
//     }
//     else
//     {
//         return NULL;
//     }
//     return maxPosi;
// }
template <typename T>
void List<T>::deduplicate()
{
    ListNodePosi(T) hBound = _trailer->_pred;
    ListNodePosi(T) curr = _header->_succ;
    while (hBound != _header)
    {
        while (curr != hBound)
        {
            if ((curr->_data) == (hBound->_data))
            {
                int res = remove(curr);
            }
            curr = curr->_succ;
        }
        hBound = hBound->_pred;
    }
}
template <typename T>
void List<T>::copyNodes(ListNode<T> *p, int n)
{
    List();
    while ((n--) > 0)
    {
        // dont use it,no need to store it
        insertAfter(_header, p->_data);
        p = p->_succ;
    }
}
template <typename T>
List<T>::List(List<T> const &L, Rank r, int n)
{
    ListNodePosi(T) p = _header->_succ;
    while (r--)
    {
        p = p->_succ;
    }
    copyNodes(p, n);
}
template <typename T>
int List<T>::clear()
{
    ListNodePosi(T) p = _header;
    while (p != _trailer)
    {
        p = p->_succ;
        delete p->_pred;
    }
    delete p;
    return empty();
}
#endif