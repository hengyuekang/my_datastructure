#include "stdafx.h"
#define MAXSIZE 100000

void gene_random(std::vector<int> &num1, int n1);
void gene_positive(std::vector<int> &num2, int n2);
void gene_negative(std::vector<int> &num2, std::vector<int> &num3, int n3);
void quick_sort(std::vector<int> &num1, int left, int right);
int partition(std::vector<int> &num1, int left, int right);
void shell_sort(std::vector<int> &num1, int n1);
void merge_sort(std::vector<int> &num1, std::vector<int> &num, int left, int right);
void merge(std::vector<int> &num1, std::vector<int> &num, int left, int mid, int right);
void heap_sort(std::vector<int> &num1, int n1);
bool examine(std::vector<int> &num1, int n1);
void kth_num(std::vector<int> &num1, int n1, int k);
int main()
{
    // for meige sort
    std::vector<int> num(MAXSIZE);
    std::vector<int> num1(MAXSIZE);
    std::vector<int> num2(MAXSIZE);
    std::vector<int> num3(MAXSIZE);
    gene_random(num1, MAXSIZE);
    gene_positive(num2, MAXSIZE);
    gene_negative(num2, num3, MAXSIZE);
    auto start = std::chrono::steady_clock::now();
    quick_sort(num1, 0, MAXSIZE - 1);
    shell_sort(num1, MAXSIZE);
    merge_sort(num1, num, 0, MAXSIZE - 1);
    heap_sort(num1, MAXSIZE);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    bool res = examine(num1, MAXSIZE);
    if (res)
    {
        std::cout << "sort success,using " << elapsed.count() << "us" << std::endl;
    }
    int k = 0;
    std::cout << "input k:";
    std::cin >> k;
    kth_num(num1, MAXSIZE, k);
    return 0;
}
void gene_random(std::vector<int> &num1, int n1)
{
    // 0~99999999
    for (int i = 0; i < n1; i++)
    {
        num1[i] = rand() % 100000000;
    }
}
void gene_positive(std::vector<int> &num2, int n2)
{
    for (int i = 0; i < n2; i++)
    {
        if (i == 0)
        {
            num2[i] = rand() % 100000000;
        }
        else
        {
            // make it positive
            num2[i] = num2[i - 1] + rand() % 6;
        }
    }
}
void gene_negative(std::vector<int> &num2, std::vector<int> &num3, int n3)
{
    for (int i = 0; i < n3; i++)
    {
        num3[i] = num2[MAXSIZE - 1 - i];
    }
}
void shell_sort(std::vector<int> &num1, int n1)
{
    int gap = n1;
    int temp = 0;
    int j = 0;
    do
    {
        gap = gap / 3 + 1;
        for (int i = gap; i < n1; i++)
        {
            if (num1[i] < num1[i - gap])
            {
                temp = num1[i];
                j = i - gap;
                // directly insert sort
                do
                {
                    num1[j + gap] = num1[j];
                    j -= gap;
                } while (j >= 0 && temp < num1[j]);
                num1[j + gap] = temp;
            }
        }

    } while (gap > 1);
}
void quick_sort(std::vector<int> &num1, int left, int right)
{
    if (left < right)
    {
        // divide
        int pivot = partition(num1, left, right);
        quick_sort(num1, left, pivot - 1);
        quick_sort(num1, pivot + 1, right);
    }
}
int partition(std::vector<int> &num1, int left, int right)
{
    int pivot = left;
    // baseline
    int Numpivot = num1[left];
    for (int i = left + 1; i <= right; i++)
    {
        if (num1[i] < Numpivot)
        {
            pivot++;
            if (pivot != i)
            {
                std::swap(num1[pivot], num1[i]);
            }
        }
    }
    // right position of baseline
    num1[left] = num1[pivot];
    num1[pivot] = Numpivot;
    return pivot;
}
void merge_sort(std::vector<int> &num1, std::vector<int> &num, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    // sort left subvector
    merge_sort(num1, num, left, mid);
    // right
    merge_sort(num1, num, mid + 1, right);
    merge(num1, num, left, mid, right);
}
void merge(std::vector<int> &num1, std::vector<int> &num, int left, int mid, int right)
{
    // num store original num1
    for (int i = left; i <= right; i++)
    {
        num[i] = num1[i];
    }
    int s1 = left;
    int s2 = mid + 1;
    int t = left;
    // two pointers
    while (s1 <= mid && s2 <= right)
    {
        if (num[s1] < num[s2])
        {
            num1[t++] = num[s1++];
        }
        else
        {
            num1[t++] = num[s2++];
        }
    }
    // merge remain elements
    while (s1 <= mid)
    {
        num1[t++] = num[s1++];
    }
    while (s2 <= right)
    {
        num1[t++] = num[s2++];
    }
}
void heap_sort(std::vector<int> &num1, int n1)
{
    int temp;
    MaxHeap H(num1, n1);
    for (int i = 0; i < n1; i++)
    {
        H.remove(temp);
    }
    for (int i = 0; i < n1; i++)
    {
        num1[i] = H.get_res(i);
    }
}
bool examine(std::vector<int> &num1, int n1)
{
    for (int i = 0; i < n1 - 1; i++)
    {
        if (num1[i] > num1[i + 1])
        {
            return false;
        }
    }
    return true;
}
void kth_num(std::vector<int> &num1, int n1, int k)
{
    for (int i = 0; i < k; i++)
    {
        std::cout << num1[i] << " ";
    }
}