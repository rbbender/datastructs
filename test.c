#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"
#include "avltree.h"

int test_BinTree(void)
{
    void* val;
    int res;
    BinTreeNode temp;
    BinTree tree = BinTree_Init();
    BinTree_Insert(tree, 2, (void*) "node2");
    BinTree_Insert(tree, 3, (void*) "node3");
    BinTree_Insert(tree, 1, (void*) "node1");
    BinTree_PrintInOrder(tree);
    val = BinTree_Find(tree, 4);
    PRINT("\tFind 4 result = %s\n", (char*) val);
    val = BinTree_Find(tree, 3);
    PRINT("\tFind 3 result = %s\n", (char*) val);
    val = BinTree_Find(tree, 2);
    PRINT("\tFind 2 result = %s\n", (char*) val);
    val = BinTree_Find(tree, 1);
    PRINT("\tFind 1 result = %s\n", (char*) val);
    res = BinTree_Remove(tree, 4);
    BinTree_PrintInOrder(tree);
    res = BinTree_Remove(tree, 3);
    BinTree_PrintInOrder(tree);
    res = BinTree_Remove(tree, 2);
    BinTree_PrintInOrder(tree);
    res = BinTree_Remove(tree, 1);
    BinTree_PrintInOrder(tree);
    res = BinTree_Remove(tree, 4);
    BinTree_PrintInOrder(tree);
    BinTree_Insert(tree, 2, (void*) "node2-1");
    BinTree_Insert(tree, 1, (void*) "node1-1");
    BinTree_Insert(tree, 1, (void*) "node1-2");
    BinTree_Insert(tree, 4, (void*) "node4-1");
    BinTree_Insert(tree, 3, (void*) "node3-1");
    BinTree_Insert(tree, 5, (void*) "node5-1");
    BinTree_PrintSubTree(tree, 2, 3);
    temp = BinTreeNode_Find(tree->root, 4);
    BinTreeNode_RotateLeft(temp);
    BinTree_PrintSubTree(tree, 2, 3);
    temp = BinTreeNode_Find(tree->root, 5);
    BinTreeNode_RotateRight(temp);
    BinTree_PrintSubTree(tree, 2, 3);
    BinTree_PrintInOrder(tree);
    BinTree_Remove(tree, 2);
    BinTree_PrintInOrder(tree);
    BinTreeNode_PrintSubTree(tree->root, 3);
    BinTree_Destroy(tree);
    return 0;
}

int test_AVLTree(void)
{
    AVLTree tree = AVLTree_Init();
    AVLTree_Insert(tree, 1, (void*) "node1");
    AVLTree_Insert(tree, 2, (void*) "node2");
    AVLTree_Insert(tree, 3, (void*) "node3");
    AVLTree_Insert(tree, 4, (void*) "node4");
    AVLTree_PrintSubTree(tree, 3, 3);
    AVLTree_Destroy(tree);
}
int main(void)
{
    init_log(DS_VERBOSITY_DBG);
    fopen_log("debug.log");
    test_BinTree();
    test_AVLTree();
    fclose_log();
}