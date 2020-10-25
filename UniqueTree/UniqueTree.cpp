#include "stdafx.h"
BinNode<char> *consTheUniTree(char *Pre, char *In, int surNodes);
void output(char &node);
void concave(BinNode<char> *p, BinNode<char> *root, int len);
int main(BinTree<char> &tree)
{
    char *pre = new char[1024];
    char *in = new char[1024];
    // input
    std::cout << "input the preorder traversal:";
    std::cin >> pre;
    std::cout << "input the inorder traversal:";
    std::cin >> in;
    // construct
    BinNode<char> *cUniTree;
    int sizeIn = strlen(in);
    cUniTree = consTheUniTree(pre, in, sizeIn);
    // test
    std::cout << "the preorder traversal of the result is: ";
    cUniTree->travPre(output);
    std::cout << "\n";
    std::cout << "the inorder traversal of the result is: ";
    cUniTree->travIn(output);
    std::cout << "\n";
    // print the tree using "concave method"
    auto root = cUniTree;
    concave(cUniTree, root, 1);
    // delete
    delete[] pre;
    delete[] in;
    pre = NULL;
    in = NULL;
    return 0;
}
BinNode<char> *consTheUniTree(char *Pre, char *In, int surNodes)
{
    if (surNodes == 0)
    {
        return NULL;
    }
    int posOfIn = 0;
    while (Pre[0] != In[posOfIn] && (posOfIn < surNodes - 1))
    {
        posOfIn++;
    }
    BinNode<char> *temp = new BinNode<char>(Pre[0]);
    temp->_lc = consTheUniTree(Pre + 1, In, posOfIn);
    temp->_rc = consTheUniTree(Pre + posOfIn + 1, In + posOfIn + 1, surNodes - posOfIn - 1);
    return temp;
}
void output(char &node)
{
    std::cout << node << "\t";
}
void concave(BinNode<char> *p, BinNode<char> *root, int len)
{
    if (p)
    {
        concave(p->_rc, root, len + 1);
        for (int i = 0; i < len; i++)
        {
            std::cout << " ";
        }
        if (p != root)
        {
            std::cout << "----";
        }
        std::cout << p->_data << std::endl;
        concave(p->_lc, root, len + 1);
    }
}