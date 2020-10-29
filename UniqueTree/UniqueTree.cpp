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
    system("pause");
    return 0;
}
BinNode<char> *consTheUniTree(char *Pre, char *In, int surNodes)
{
    // surNodes and posOfIn assure section
    if (surNodes == 0)
    {
        return NULL;
    }
    // position of current root in "In"
    int posOfIn = 0;
    while (Pre[0] != In[posOfIn])
    {
        posOfIn++;
    }
    // previous roots are abandoned
    BinNode<char> *temp = new BinNode<char>(Pre[0]);
    // left subtree
    temp->_lc = consTheUniTree(Pre + 1, In, posOfIn);
    // right subtree
    temp->_rc = consTheUniTree(Pre + posOfIn + 1, In + posOfIn + 1, surNodes - posOfIn - 1);
    return temp;
}
void concave(BinNode<char> *p, BinNode<char> *root, int depth)
{
    // end
    if (p == NULL)
    {
        return;
    }
    else
    {
        // output right subtree first
        concave(p->_rc, root, depth + 1);
        // show different depths
        for (int i = 0; i < depth; i++)
        {
            std::cout << "\t";
        }
        std::cout << p->_data << std::endl;
        // left tree
        concave(p->_lc, root, depth + 1);
    }
}
void output(char &node)
{
    std::cout << node << "\t";
}