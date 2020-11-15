#include "stdafx.h"
#define MAXSIZE 5000
bool gene_random(int *, int);
bool sequence_search(int);
bool BST_search(int);
bool AVL_search(int);
int main()
{

    int data[MAXSIZE];
    int number = 0;
    // generate 5000 random int to data.txt
    // distribution:0-9999
    bool res = gene_random(data, MAXSIZE);
    if (res)
    {
        std::cout << "input the number you want to search(0-9999): ";
        std::cin >> number;
        // sequence search
        bool res1 = sequence_search(number);
        // BST search
        bool res2 = BST_search(number);
        // AVL research
        bool res3 = AVL_search(number);
    }
    else
    {
        std::cout << "fail to generate random numbers." << std::endl;
    }

    return 0;
}
bool gene_random(int *data, int size)
{
    std::fstream out("data.txt");
    if (!out.is_open())
    {
        std::cerr << "can't open the output file." << std::endl;
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        data[i] = rand() % 10000;
        for (size_t j = 0; j < i;)
        {
            // same:generate again
            if (data[i] == data[j])
            {
                data[i] = rand() % 10000;
                j = 0;
                continue;
            }
            else
            {
                j++;
            }
        }
        out << data[i] << " ";
    }
    return (data != NULL ? true : false);
}
bool sequence_search(int goal)
{
    std::fstream in("data.txt");
    int data[MAXSIZE];
    if (in.is_open())
    {

        for (size_t i = 0; i < MAXSIZE; i++)
        {
            in >> data[i];
            // if (goal == data[i])
            // {
            //     auto end = std::chrono::steady_clock::now();
            //     std::chrono::duration<double, std::micro> elapsed = end - start;
            //     std::cout << "sequence_search find it,the index is " << i << "." << std::endl;
            //     std::cout << "to find it,we use " << elapsed.count() << "us" << std::endl;
            //     return true;
            // }
        }
        auto start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < MAXSIZE; i++)
        {
            if (goal == data[i])
            {
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double, std::micro> elapsed = end - start;
                std::cout << "sequence_search find it,the index is " << i << "." << std::endl;
                std::cout << "to find it,we use " << elapsed.count() << "us" << std::endl;
                return true;
            }
        }

        std::cerr << "sequence_search can't find it." << std::endl;
    }
    else
    {
        std::cerr << "cant open file." << std::endl;
    }

    return false;
}
bool BST_search(int goal)
{
    std::fstream in("data.txt");
    BST<int> iBST;
    int node = 0;
    if (in.is_open())
    {
        in >> node;
        iBST.insertAsRoot(node);
        while (in >> node)
        {
            iBST.insert(node);
        }
        auto start = std::chrono::steady_clock::now();
        BinNode<int> *res = iBST.search(goal);
        if (res)
        {
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::micro> elapsed = end - start;
            std::cout << "BST_search find it." << std::endl;
            std::cout << "to find it,we use " << elapsed.count() << "us" << std::endl;
            return true;
        }
        else
        {
            std::cerr << "BST_search can't find it." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "cant open file" << std::endl;
    }
    return false;
}
bool AVL_search(int goal)
{
    std::fstream in("data.txt");
    AVL<int> iAVL;
    int node = 0;
    if (in.is_open())
    {
        in >> node;
        iAVL.insertAsRoot(node);
        while (in >> node)
        {
            iAVL.insert(node);
        }
        auto start = std::chrono::steady_clock::now();
        BinNode<int> *res = iAVL.search(goal);
        if (res)
        {
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::micro> elapsed = end - start;
            std::cout << "AVL_search find it." << std::endl;
            std::cout << "to find it,we use " << elapsed.count() << "us" << std::endl;
            return true;
        }
        else
        {
            std::cerr << "AVL_search can't find it." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "cant open file" << std::endl;
    }
    return false;
}
