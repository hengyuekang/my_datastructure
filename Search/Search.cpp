#include "stdafx.h"
#define MAXSIZE 5000
bool gene_random(int *, int);
bool sequence_search(std::fstream &, int);
bool BST_search(std::fstream &, int);
int main()
{
    int data[MAXSIZE];
    int number = 0;
    // generate 5000 random int to data.txt
    // distribution:0-9999
    bool res = gene_random(data, MAXSIZE);
    std::fstream in("data.txt");
    if (res && (in.is_open()))
    {
        std::cout << "input the number you want to search(0-9999): ";
        std::cin >> number;
        // sequence search
        // bool res1 = sequence_search(in, number);
        // BST search
        bool res2 = BST_search(in, number);
    }
    else
    {
        std::cerr << "wrong generation or can't open the file." << std::endl;
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
bool sequence_search(std::fstream &in, int goal)
{
    int data[MAXSIZE];
    for (size_t i = 0; i < MAXSIZE; i++)
    {
        in >> data[i];
        if (goal == data[i])
        {
            std::cout << "find it,the index is " << i << "." << std::endl;
            return true;
        }
    }
    std::cerr << "can't find it." << std::endl;
    return false;
}
bool BST_search(std::fstream &in, int goal)
{
    BST<int> iBST;
    int node = 0;
    in >> node;
    iBST.insertAsRoot(node);
    while (in >> node)
    {
        iBST.insert(node);
    }
    BinNode<int> *res = iBST.search(goal);
    if (res)
    {
        std::cout << "find it." << std::endl;
        return true;
    }
    else
    {
        std::cerr << "can't find it." << std::endl;
        return false;
    }
}
