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
    // Rank size() const { return _size; }
    T &top() const { return _elem[_size - 1]; }
    bool empty() const { return _size <= 0; }
    void push(T const &e) { insert(e); }
    // remove: Conflict with an existing function in cstdio.h
    T pop() { return Remove(_size - 1); }
};
