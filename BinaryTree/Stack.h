#pragma once
#include "Vector.h"
#include "BinNode.h"
template <typename T>
class Stack : public Vector<T>
{
public:
    // ctor from vector
    // same as vector
    // Stack() = default;
    // ~Stack();
    // read only
    // directly use them from vector
    // bool empty() const { return _size <= 0; }
    // Rank size() const { return _size; }
    // use overload
    T &top() const { return (*this)[this->Size() - 1]; }
    // must use this ,if the funciton is from dad class<T> (nomal class dont need)
    void push(T const &e) { this->insert(e); }
    // remove: Conflict with an existing function in cstdio.h
    T pop() { return this->Remove(this->Size() - 1); }
};
