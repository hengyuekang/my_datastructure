#pragma once
#include "List.h"
#include "BinNode.h"
template <typename T>
class Queue : public List<T>
{
public:
    // read only
    // avoid data() (const T not transform to T&)
    T &front() const { return this->first()->_data; }
    // write
    void enqueue(T const &e) { this->insertAsLast(e); }
    T dequeue() { return this->remove(this->first()); }
};
