#pragma once
#include "stdafx.h"
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
    T &top() const { return (*this)[size() - 1]; }
    void push(T const &e) { insert(e); }
    // remove: Conflict with an existing function in cstdio.h
    T pop() { return Remove(size() - 1); }
};
