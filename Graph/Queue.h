#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"
template <typename T>
class Queue : public List<T>
{
public:
    // read only
    // avoid data() (const T not transform to T&)
    T &front() const { return this->first()->_data; }
    // write
    void enqueue(T const &e) { this->insertAsLast(e); }
    void dequeue() { this->remove(this->first()); }
};
#endif
