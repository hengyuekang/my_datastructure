#ifndef VECTOR_H
#define VECTOR_H
using Rank = int;
#define DEFAULT_CAPACITY 3

template <typename T>
class Vector
{
protected:
    Rank _size;
    int _capacity;
    T *_elem;
    void copyFrom(T const *A, Rank lo, Rank hi);
    void expand();
    void shrink();

public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }

    ~Vector() { delete[] _elem; }
    Rank Size() const { return _size; }
    bool empty() const { return !_size; }
    T &operator[](Rank r) const;
    T Remove(Rank r);
    int Remove(Rank lo, Rank hi);
    Rank insert(Rank r, T const &e);
    Rank insert(T const &e) { return insert(_size, e); }
};
template <typename T>
T &Vector<T>::operator[](Rank r) const
{
    return _elem[r];
}
template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity)
    {
        return;
    }
    if (_capacity < DEFAULT_CAPACITY)
    {
        _capacity = DEFAULT_CAPACITY;
    }
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}
template <typename T>
Rank Vector<T>::insert(Rank r, T const &e)
{
    expand();
    for (int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}
template <typename T>
void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1)
    {
        return;
    }
    if (_size << 2 > _capacity)
    {
        return;
    }
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}
template <typename T>
int Vector<T>::Remove(Rank lo, Rank hi)
{
    if (lo == hi)
    {
        return 0;
    }
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}
template <typename T>
T Vector<T>::Remove(Rank r)
{
    T e = _elem[r];
    Remove(r, r + 1);
    return e;
}
#endif