#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"
#include "list_BinTreeNode.h"

// inserting 100 nodes into tree, verifying they're being returned
// in a right order
int test_BinTreeNode_1(void)
{
    char testName[] = "test_BinTreeNode_1";
    PRINT("------------ %s ---------------\n", testName);
    listBinTreeNode_Allocate();
    BinTreeNode root;
    root = NULL;
    int i;
    int r;
    int res;
    res = 1;
    BinTreeNode t;
    r = rand();
    root = BinTreeNode_Init(r, (void*) "root", NULL);
    listBinTreeNode_Add(root);
    for (i = 1; i < 100; ++i)
    {
        r = rand();
        PRINT_DBG("New key = %d\n", r);
        t = BinTreeNode_Init(r, (void*) "", NULL);
        BinTreeNode_Insert(root, t);
        listBinTreeNode_Add(t);
    }
    qsort(listBinTreeNode, listBinTreeNode_size, sizeof(BinTreeNode), &listBinTreeNode_cmp);

    for (i = 0, t = BinTreeNode_LeftDescendant(root); i < 100; ++i, t = BinTreeNode_Next(t))
    {
        PRINT_DBG("%d: %d %d\n", i, t->key, listBinTreeNode[i]->key);
        if (listBinTreeNode[i]->key != t->key)
        {
            PRINT_DBG("ERROR: node # %d: key val is %d, expected %d\n", 
                i, t->key, listBinTreeNode[i]->key);
            res = 0;
            break;
        }
    }
    free(listBinTreeNode);
    BinTreeNode_DestroyGracefully(root);
    if (!res)
        PRINT("------------ %s --------------- FAILED\n", testName);
    else
        PRINT("------------ %s --------------- PASS\n", testName);
    return res;
}

// inserting 100 nodes into tree, deleting leaf
// verifying they're being returned
// in a right order
int test_BinTreeNode_2(void)
{
    char testName[] = "test_BinTreeNode_2";
    PRINT("------------ %s ---------------\n", testName);
    listBinTreeNode_Allocate();
    BinTreeNode root;
    root = NULL;
    int i;
    int r;
    int res;
    res = 1;
    BinTreeNode t;
    r = rand();
    root = BinTreeNode_Init(r, (void*) "root", NULL);
    listBinTreeNode_Add(root);
    for (i = 1; i < 100; ++i)
    {
        r = rand();
        PRINT_DBG("New key = %d\n", r);
        t = BinTreeNode_Init(r, (void*) "", NULL);
        BinTreeNode_Insert(root, t);
        listBinTreeNode_Add(t);
    }
    for (t = root; (t->left_child || t->right_child);)
    {
        if (t->left_child)
            t = t->left_child;
        else
            t = t->right_child;
    }
    r = t->key;
    PRINT_DBG("key to delete is %d\n", r);
    BinTreeNode_Remove(t);
    listBinTreeNode_Remove(r);
    qsort(listBinTreeNode, listBinTreeNode_size, sizeof(BinTreeNode), &listBinTreeNode_cmp);

    for (i = 0, t = BinTreeNode_LeftDescendant(root); i < 99; ++i, t = BinTreeNode_Next(t))
    {
        PRINT_DBG("%d: %d %d\n", i, t->key, listBinTreeNode[i]->key);
        if (listBinTreeNode[i]->key != t->key)
        {
            PRINT_DBG("ERROR: node # %d: key val is %d, expected %d\n", 
                i, t->key, listBinTreeNode[i]->key);
            res = 0;
            break;
        }
    }
    free(listBinTreeNode);
    BinTreeNode_DestroyGracefully(root);
    if (!res)
        PRINT("------------ %s --------------- FAILED\n", testName);
    else
        PRINT("------------ %s --------------- PASS\n", testName);
    return res;
}

// inserting 100 nodes into tree, deleting root
// verifying they're being returned
// in a right order
int test_BinTreeNode_3(void)
{
    char testName[] = "test_BinTreeNode_3";
    PRINT("------------ %s ---------------\n", testName);
    listBinTreeNode_Allocate();
    BinTreeNode root;
    root = NULL;
    int i;
    int r;
    int res;
    res = 1;
    BinTreeNode t;
    r = rand();
    root = BinTreeNode_Init(r, (void*) "root", NULL);
    listBinTreeNode_Add(root);
    for (i = 1; i < 100; ++i)
    {
        r = rand();
        PRINT_DBG("New key = %d\n", r);
        t = BinTreeNode_Init(r, (void*) "", NULL);
        BinTreeNode_Insert(root, t);
        listBinTreeNode_Add(t);
    }
    r = root->key;
    PRINT_DBG("key to delete is %d\n", r);
    root = BinTreeNode_Remove(root);
    listBinTreeNode_Remove(r);
    qsort(listBinTreeNode, listBinTreeNode_size, sizeof(BinTreeNode), &listBinTreeNode_cmp);

    for (i = 0, t = BinTreeNode_LeftDescendant(root); i < 99; ++i, t = BinTreeNode_Next(t))
    {
        PRINT_DBG("%d: %d %d\n", i, t->key, listBinTreeNode[i]->key);
        if (listBinTreeNode[i]->key != t->key)
        {
            PRINT("ERROR: node # %d: key val is %d, expected %d\n", 
                i, t->key, listBinTreeNode[i]->key);
            res = 0;
            break;
        }
    }
    free(listBinTreeNode);
    BinTreeNode_DestroyGracefully(root);
    if (!res)
        PRINT("------------ %s --------------- FAILED\n", testName);
    else
        PRINT("------------ %s --------------- PASS\n", testName);
    return res;
}


// inserting 100 nodes into tree, some node with both left and right childs
// verifying they're being returned
// in a right order
int test_BinTreeNode_4(void)
{
    char testName[] = "test_BinTreeNode_4";
    PRINT("------------ %s ---------------\n", testName);
    listBinTreeNode_Allocate();
    BinTreeNode root;
    root = NULL;
    int i;
    int r;
    int res;
    res = 1;
    BinTreeNode t, p;
    r = rand();
    root = BinTreeNode_Init(r, (void*) "root", NULL);
    listBinTreeNode_Add(root);
    for (i = 1; i < 100; ++i)
    {
        r = rand();
        PRINT_DBG("New key = %d\n", r);
        t = BinTreeNode_Init(r, (void*) "", NULL);
        BinTreeNode_Insert(root, t);
        listBinTreeNode_Add(t);
    }
    for (p = BinTreeNode_LeftDescendant(root), t = BinTreeNode_Next(p); 
        (p != t) && !(t->left_child && t->right_child); 
        p = t, t = BinTreeNode_Next(t))
        ;
    if (!(t->left_child && t->right_child))
        PRINT("ERROR: it looks like there was no node with both left and right childs\n");
    r = t->key;
    PRINT_DBG("key to delete is %d\n", r);
    BinTreeNode_Remove(t);
    listBinTreeNode_Remove(r);
    qsort(listBinTreeNode, listBinTreeNode_size, sizeof(BinTreeNode), &listBinTreeNode_cmp);

    for (i = 0, t = BinTreeNode_LeftDescendant(root); i < 99; ++i, t = BinTreeNode_Next(t))
    {
        PRINT_DBG("%d: %d %d\n", i, t->key, listBinTreeNode[i]->key);
        if (listBinTreeNode[i]->key != t->key)
        {
            PRINT_DBG("ERROR: node # %d: key val is %d, expected %d\n", 
                i, t->key, listBinTreeNode[i]->key);
            res = 0;
            break;
        }
    }
    free(listBinTreeNode);
    BinTreeNode_DestroyGracefully(root);
    if (!res)
        PRINT("------------ %s --------------- FAILED\n", testName);
    else
        PRINT("------------ %s --------------- PASS\n", testName);
    return res;
}


int main(void)
{
    init_log(DS_VERBOSITY_STD);
    test_BinTreeNode_1();
    test_BinTreeNode_2();
    test_BinTreeNode_3();
    test_BinTreeNode_4();
}