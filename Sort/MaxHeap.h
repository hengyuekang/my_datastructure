#pragma once
#include <iostream>
#include <vector>
class MaxHeap
{
private:
    std::vector<int> heap;
    int currSize;
    int maxSize;

public:
    MaxHeap(std::vector<int> arr, int n);
    bool remove(int &x);
    void siftDown(int start, int m);
    int get_res(int i)
    {
        return heap[i];
    }
};
void MaxHeap::siftDown(int start, int end)
{
    int i = start;
    int j = 2 * i + 1;
    int temp = heap[i];
    while (j <= end)
    {
        if ((j < end) && (heap[j] < heap[j + 1]))
        {
            j++;
        }
        if (temp >= heap[j])
        {
            break;
        }
        else
        {
            heap[i] = heap[j];
            i = j;
            j = 2 * i + 1;
        }
    }
    heap[i] = temp;
}
MaxHeap::MaxHeap(std::vector<int> arr, int n)
{
    maxSize = n;
    for (int i = 0; i < n; i++)
    {
        heap.push_back(arr[i]);
    }
    currSize = n;
    for (int i = (currSize - 2) / 2; i >= 0; i--)
    {
        siftDown(i, currSize - 1);
    }
}
bool MaxHeap::remove(int &x)
{
    x = heap[0];
    std::swap(heap[0], heap[currSize - 1]);
    currSize--;
    if (currSize != 0)
    {
        siftDown(0, currSize - 1);
    }
    return true;
}
