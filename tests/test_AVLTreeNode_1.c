#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "avltree.h"
#include "list_AVLTreeNode.h"

// inserting 100 nodes into tree, verifying they're being returned
// in a right order
int test_AVLTreeNode_1(void)
{
    char testName[] = "test_AVLTreeNode_1";
    PRINT("------------ %s ---------------\n", testName);
    listAVLTreeNode_Allocate();
    AVLTreeNode root;
    root = NULL;
    int i;
    int r;
    int res;
    res = 1;
    AVLTreeNode t;
    r = rand();
    root = AVLTreeNode_Init(r, (void*) "root");
    listAVLTreeNode_Add(root);
    for (i = 1; i < 100; ++i)
    {
        r = rand();
        PRINT("New key = %d\n", r);
        t = AVLTreeNode_Init(r, (void*) "");
        root = AVLTreeNode_Insert(root, t);
        listAVLTreeNode_Add(t);
    }
    qsort(listAVLTreeNode, listAVLTreeNode_size, sizeof(AVLTreeNode), &listAVLTreeNode_cmp);

    for (i = 0, t = AVLTreeNode_LeftDescendant(root); i < 100; ++i, t = AVLTreeNode_Next(t))
    {
        PRINT_DBG("%d: %d %d\n", i, t->key, listAVLTreeNode[i]->key);
        if (listAVLTreeNode[i]->key != t->key)
        {
            PRINT("ERROR: node # %d: key val is %d, expected %d\n", 
                i, t->key, listAVLTreeNode[i]->key);
            res = 0;
            break;
        }
    }
    free(listAVLTreeNode);
    AVLTreeNode_DestroyGracefully(root);
    if (!res)
        PRINT("------------ %s --------------- FAILED\n", testName);
    else
        PRINT("------------ %s --------------- PASS\n", testName);
    return res;
}

// inserting 100 nodes into tree, deleting leaf
// verifying they're being returned
// in a right order
int test_AVLTreeNode_2(void)
{
    char testName[] = "test_AVLTreeNode_2";
    PRINT("------------ %s ---------------\n", testName);
    listAVLTreeNode_Allocate();
    AVLTreeNode root;
    root = NULL;
    int i;
    int r;
    int res;
    res = 1;
    AVLTreeNode t;
    r = rand();
    root = AVLTreeNode_Init(r, (void*) "root");
    listAVLTreeNode_Add(root);
    for (i = 1; i < 100; ++i)
    {
        r = rand();
        PRINT_DBG("New key = %d\n", r);
        t = AVLTreeNode_Init(r, (void*) "");
        root = AVLTreeNode_Insert(root, t);
        listAVLTreeNode_Add(t);
    }
    for (t = root; (t->left_child || t->right_child);)
    {
        if (t->left_child)
            t = t->left_child;
        else
            t = t->right_child;
    }
    r = t->key;
    PRINT("key to delete is %d\n", r);
    AVLTreeNode_Remove(t);
    listAVLTreeNode_Remove(r);
    qsort(listAVLTreeNode, listAVLTreeNode_size, sizeof(AVLTreeNode), &listAVLTreeNode_cmp);

    for (i = 0, t = AVLTreeNode_LeftDescendant(root); i < 99; ++i, t = AVLTreeNode_Next(t))
    {
        PRINT_DBG("%d: %d %d\n", i, t->key, listAVLTreeNode[i]->key);
        if (listAVLTreeNode[i]->key != t->key)
        {
            PRINT_DBG("ERROR: node # %d: key val is %d, expected %d\n", 
                i, t->key, listAVLTreeNode[i]->key);
            res = 0;
            break;
        }
    }
    free(listAVLTreeNode);
    AVLTreeNode_DestroyGracefully(root);
    if (!res)
        PRINT("------------ %s --------------- FAILED\n", testName);
    else
        PRINT("------------ %s --------------- PASS\n", testName);
    return res;
}

// inserting 100 nodes into tree, deleting root
// verifying they're being returned
// in a right order
int test_AVLTreeNode_3(void)
{
    char testName[] = "test_AVLTreeNode_3";
    PRINT("------------ %s ---------------\n", testName);
    listAVLTreeNode_Allocate();
    AVLTreeNode root;
    root = NULL;
    int i;
    int r;
    int res;
    res = 1;
    AVLTreeNode t;
    r = rand();
    root = AVLTreeNode_Init(r, (void*) "root");
    listAVLTreeNode_Add(root);
    for (i = 1; i < 100; ++i)
    {
        r = rand();
        PRINT_DBG("New key = %d\n", r);
        t = AVLTreeNode_Init(r, (void*) "");
        root = AVLTreeNode_Insert(root, t);
        listAVLTreeNode_Add(t);
    }
    r = root->key;
    PRINT_DBG("key to delete is %d\n", r);
    root = AVLTreeNode_Remove(root);
    listAVLTreeNode_Remove(r);
    qsort(listAVLTreeNode, listAVLTreeNode_size, sizeof(AVLTreeNode), &listAVLTreeNode_cmp);

    for (i = 0, t = AVLTreeNode_LeftDescendant(root); i < 99; ++i, t = AVLTreeNode_Next(t))
    {
        PRINT_DBG("%d: %d %d\n", i, t->key, listAVLTreeNode[i]->key);
        if (listAVLTreeNode[i]->key != t->key)
        {
            PRINT("ERROR: node # %d: key val is %d, expected %d\n", 
                i, t->key, listAVLTreeNode[i]->key);
            res = 0;
            break;
        }
    }
    free(listAVLTreeNode);
    AVLTreeNode_DestroyGracefully(root);
    if (!res)
        PRINT("------------ %s --------------- FAILED\n", testName);
    else
        PRINT("------------ %s --------------- PASS\n", testName);
    return res;
}


// inserting 100 nodes into tree, some node with both left and right childs
// verifying they're being returned
// in a right order
int test_AVLTreeNode_4(void)
{
    char testName[] = "test_AVLTreeNode_4";
    PRINT("------------ %s ---------------\n", testName);
    listAVLTreeNode_Allocate();
    AVLTreeNode root;
    root = NULL;
    int i;
    int r;
    int res;
    res = 1;
    AVLTreeNode t, p;
    r = rand();
    root = AVLTreeNode_Init(r, (void*) "root");
    listAVLTreeNode_Add(root);
    for (i = 1; i < 100; ++i)
    {
        r = rand();
        PRINT_DBG("New key = %d\n", r);
        t = AVLTreeNode_Init(r, (void*) "");
        root = AVLTreeNode_Insert(root, t);
        listAVLTreeNode_Add(t);
    }
    for (p = AVLTreeNode_LeftDescendant(root), t = AVLTreeNode_Next(p); 
        (p != t) && !(t->left_child && t->right_child); 
        p = t, t = AVLTreeNode_Next(t))
        ;
    if (!(t->left_child && t->right_child))
        PRINT("ERROR: it looks like there was no node with both left and right childs\n");
    r = t->key;
    PRINT_DBG("key to delete is %d\n", r);
    AVLTreeNode_Remove(t);
    listAVLTreeNode_Remove(r);
    qsort(listAVLTreeNode, listAVLTreeNode_size, sizeof(AVLTreeNode), &listAVLTreeNode_cmp);

    for (i = 0, t = AVLTreeNode_LeftDescendant(root); i < 99; ++i, t = AVLTreeNode_Next(t))
    {
        PRINT_DBG("%d: %d %d\n", i, t->key, listAVLTreeNode[i]->key);
        if (listAVLTreeNode[i]->key != t->key)
        {
            PRINT_DBG("ERROR: node # %d: key val is %d, expected %d\n", 
                i, t->key, listAVLTreeNode[i]->key);
            res = 0;
            break;
        }
    }
    free(listAVLTreeNode);
    AVLTreeNode_DestroyGracefully(root);
    if (!res)
        PRINT("------------ %s --------------- FAILED\n", testName);
    else
        PRINT("------------ %s --------------- PASS\n", testName);
    return res;
}


int main(void)
{
    init_log(DS_VERBOSITY_STD);
    test_AVLTreeNode_1();
    test_AVLTreeNode_2();
    test_AVLTreeNode_3();
    test_AVLTreeNode_4();
}