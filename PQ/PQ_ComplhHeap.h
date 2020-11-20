#pragma once
#include "Vector.h"
#include "PQ.h"
// proper index
#define InHeap(n, i) (((-1) < (i)) && ((i) < (n)))
// [(i-1)/2]
#define Parent(i) ((i - 1) >> 1)
// the last internal node
#define LastInternal(n) Parent(n - 1)
#define LChild(i) (((i) << 1) + 1)
#define RChild(i) (((i) + 1) << 1)
#define ParentValid(i) (0 < i)
#define LChildValid(n, i) InHeap(n, LChild(i))
#define RChildValid(n, i) InHeap(n, RChild(i))
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i)
// the max among parent,rc,lc
#define ProperParent(PQ, n, i) \
    (RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))
template <typename T>
class PQ_ComplhHeap : public PQ<T>, public Vector<T>
{
protected:
    Rank percolateDown(Rank n, Rank i);
    Rank percolateUp(Rank i);
    // construct heap
    void heapify(Rank n);

public:
    PQ_ComplhHeap() {}
    // construct using a Vector
    PQ_ComplhHeap(T *A, Rank n)
    {
        this->copyFrom(A, 0, n);
        heapify(n);
    }
    void insert(T);
    T getMax() const { return this->_elem[0]; }
    T delMax();
};
template <typename T>
void PQ_ComplhHeap<T>::insert(T e)
{
    this->insert(e);
    percolateUp(this->_size - 1);
}
template <typename T>
Rank PQ_ComplhHeap<T>::percolateUp(Rank i)
{
    while (ParentValid(i))
    {
        Rank j = Parent(i);
        if (lt(this->_elem[i] < this->_elem[j]))
        {
            break;
        }
        std::swap(this->_elem[i], this->_elem[j]);
        i = j;
    }
    return i;
}
template <typename T>
T PQ_ComplhHeap<T>::delMax()
{
    T maxElem = this->_elem[0];
    this->_elem[0] = this->_elem[--(this->_size)];
    percolateDown(_size, 0);
    return maxElem;
}
template <typename T>
Rank PQ_ComplhHeap<T>::percolateDown(Rank n, Rank i)
{
    Rank j = 0;
    while (i != (j = ProperParent(this->_elem, n, i)))
    {
        std::swap(this->_elem[i], this->_elem[j]);
        i = j;
    }
    return i;
}
template <typename T>
void PQ_ComplhHeap<T>::heapify(Rank n)
{
    for (size_t i = LastInternal(n); InHeap(n, i); i--)
    {
        percolateDown(n, i);
    }
}
