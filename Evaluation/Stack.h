#ifndef STACK_H
#define STACK_H
#include "Vector.h"
template <typename T>
class Stack : public Vector<T>
{
public:
    // ctor from vector
    T &top() const { return (*this)[this->Size() - 1]; }
    // must use this ,if the funciton is from dad class<T> (nomal class dont need)
    void push(T const &e) { this->insert(e); }
    // remove: Conflict with an existing function in cstdio.h
    T pop() { return this->Remove(this->Size() - 1); }
};
#endif