#ifndef HEAP_H
#define HEAP_H
#include <iostream>
template <typename T>
class MinHeap
{
public:
    bool Insert(const T&x);
    bool Remove(T &d);
    MinHeap(int sz=11);
    MinHeap(T arr[],int n);
    ~MinHeap(){delete  []heap;}
    bool IsEmpty() const { return currentSize==0;}
    bool IsFull() const {return  currentSize==maxHeapSize;}
    void MakeEmpty() {currentSize=0;}
private:
    T *heap;
    int currentSize;
    int maxHeapSize;
//    filter down
    void siftDown(int start,int m);
    void siftUp(int start);

};
template <typename T>
MinHeap<T>::MinHeap(int sz)
{
    maxHeapSize =( 11 < sz )? sz : 11;
    heap = new T[ maxHeapSize ];
    if (heap == nullptr)
    {
        std::cerr << "fail to allocate memory!"<< std::endl ;
        exit (1);
    }
    currentSize = 0;
}
template <typename T>
MinHeap<T>::MinHeap (T arr[], int n)
{
    maxHeapSize = (11 < n)? n : 11;
    heap = new T[maxHeapSize ];
    if (heap ==nullptr)
    {
        std::cerr << "fail to allocate memory!"<< std::endl ;
        exit (1);
    }
    for(int i=0;i<n;i++)
    {
        heap[i]=arr[i];
    }
    currentSize = n;
//    parent of the last one
    int currentPos = (currentSize- 2)/2;
    while (currentPos>=0)
    {
        siftDown(currentPos,currentSize-1);
        currentPos--;
    }
}
template <typename T>
void MinHeap<T>::siftDown(int start,int m)
{
    int i = start , j = 2*i+1;
    T temp = heap[ i ];
    while(j<=m)
    {
        if(j<m&&heap[j]>heap[j+1])j++;
        if(temp<=heap[j])break;
        else
        {
            heap[i]=heap[j];
            i=j;
            j=2*j+1;
        }
    }
//    swap
    heap[i]=temp;
}
template <typename T>
bool MinHeap<T>::Insert(const T&x)
{
    if(currentSize==maxHeapSize)
    {
        std::cerr<<"heap full!"<<std::endl;
        return  false;
    }
    heap[currentSize]=x;
    siftUp(currentSize);
    currentSize++;
    return  true;
}
template <typename T>
void MinHeap<T>::siftUp(int start)
{
    int j=start,i=(j-1)/2;
    T temp=heap[j];
    while (j>0)
    {
        if(heap[i]<=temp)break;
        else
        {
            heap[j]=heap[i];
            j=i;
            i=(i-1)/2;
        }

    }
    heap[j]=temp;
}
template <typename T>
bool MinHeap<T>::Remove(T &x)
{
    if(!currentSize)
    {
        std::cout<<"heap empty!"<<std::endl;
        return  false;
    }
    x=heap[0];
    heap[0]=heap[currentSize-1];
    currentSize--;
    siftDown(0,currentSize-1);
    return  true;
}
#endif // HEAP_H
