#include <iostream>
#include "BinaryTree.h"

int main()
{
    BinaryTree<int> tree;
    /*tree.AddLoop(20);
    tree.AddLoop(15);
    tree.AddLoop(30);
    tree.AddLoop(10);

    tree.AddLoop(18);
    tree.AddLoop(25);
    tree.AddLoop(35);
    tree.AddLoop(19);*/

    tree.AddReq(20);
    tree.AddReq(15);
    tree.AddReq(30);
    tree.AddReq(10);

    tree.AddReq(18);
    tree.AddReq(25);
    tree.AddReq(35);
    tree.AddReq(19);

    tree.List();

    std::cout << "\n";
    auto find = tree.FindLoop(15);
    
    if(find)
        tree.ListBranch(find);
}
