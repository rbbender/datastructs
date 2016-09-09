#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"

int BinTreeNode_Print(BinTreeNode n)
{
    if (!n)
    {
        PRINT_DBG("%p ", n);
    }
    else
    {
        PRINT_DBG("%s ", n->repr);
    }
    return 0;
}

int BinTreeNode_PrintLink(BinTreeNode n1, BinTreeNode n2)
{
    BinTreeNode_Print(n1);
    PRINT_DBG(" -> ");
    BinTreeNode_Print(n2);
    return 0;
}

BinTreeNode BinTreeNode_Init(int key, void* val_p)
{
    PRINT_DBG("BinTreeNode_Init: START: key = %d, val_p = %p\n", key, val_p);
    BinTreeNode res = (BinTreeNode) malloc(sizeof(struct bintree_node));
    res->key = key;
    res->value = val_p;
    res->parent = res->left_child = res->right_child = NULL;
    res->repr = (char*) malloc(DS_BINTREE_MAXREPR * sizeof(char));
    sprintf(res->repr, "%d: ", res->key);
    PRINT_DBG("BinTreeNode_Init: END: %s created\n", res->repr);
    return res;
}

int BinTreeNode_SetParent(BinTreeNode parent, BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_SetParent: ");
    BinTreeNode_PrintLink(parent, node);
    PRINT_DBG("\n");
    if (!node)
    {
        PRINT_DBG("BinTreeNode_SetParent: node is NULL. Returning\n");
        return -1;
    }
    node->parent = parent;
    return 0;
}

int BinTreeNode_SetLeftChild(BinTreeNode node, BinTreeNode lchild)
{
    PRINT_DBG("BinTreeNode_SetLeftChild: ");
    BinTreeNode_PrintLink(node, lchild);
    PRINT_DBG("\n");
    if (!node)
    {
        PRINT_DBG("BinTreeNode_SetLeftChild: node is NULL. Returning\n");
        return -1;
    }
    node->left_child = lchild;
    BinTreeNode_SetParent(node, lchild);
    return 0;
}

int BinTreeNode_SetRightChild(BinTreeNode node, BinTreeNode rchild)
{
    PRINT_DBG("BinTreeNode_SetRightChild: ");
    BinTreeNode_PrintLink(node, rchild);
    PRINT_DBG("\n");
    if (!node)
    {
        PRINT_DBG("BinTreeNode_SetRightChild: node is NULL. Returning\n");
        return -1;
    }
    node->right_child = rchild;
    BinTreeNode_SetParent(node, rchild);
    return 0;
}

BinTreeNode BinTreeNode_Find(BinTreeNode node, int key)
{
    PRINT_DBG("BinTreeNode_Find: key = %d, node = ", key);
    BinTreeNode_Print(node);
    PRINT_DBG("\n");
    BinTreeNode t, p;
    if (!node)
    {
        PRINT_DBG("BinTreeNode_Find: node is NULL. Returning NULL.\n");
        return NULL;
    }
    t = node;
    p = node->parent;
    while (t && (t->key != key))
    {
        PRINT_DBG("BinTreeNode_Find: t->key = %d\n", t->key);
        p = t;
        if (key < t->key)
        {
            PRINT_DBG("BinTreeNode_Find: <<<<: key < t->key: %d < %d\n", key, t->key);
            t = t->left_child;
        }
        else
        {
            PRINT_DBG("BinTreeNode_Find: >>>>: key > t->key: %d > %d\n", key, t->key);
            t = t->right_child;
        }
    }
    if (!t)
    {
        PRINT_DBG("BinTreeNode_Find: NOT FOUND. p = ");
        BinTreeNode_Print(p);
        PRINT_DBG("\n");
        return p;
    }
    PRINT_DBG("BinTreeNode_Find: FOUND. t = ");
    BinTreeNode_Print(t);
    PRINT_DBG("\n");
    return t;
}

BinTreeNode BinTreeNode_Insert(BinTreeNode root, BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_Insert: root = ");
    BinTreeNode_Print(root);
    PRINT_DBG(", node = ");
    BinTreeNode_Print(node);
    PRINT_DBG("\n");
    BinTreeNode n;
    if (!root)
    {
        PRINT_DBG("BinTreeNode_Insert: root is NULL\n");
    }
    if (!node)
    {
        PRINT_DBG("BinTreeNode_Insert: node is NULL\n");
        return root;
    }
    n = BinTreeNode_Find(root, node->key);
    if (!n)
    {
        PRINT_DBG("BinTreeNode_Insert: Inserting into NULL tree. Node is new root\n");
        return node;
    }
    if (node->key == n->key)
    {
        PRINT_DBG("BinTreeNode_Insert: Node with this key exist. Doing nothing.\n");
        return root;
    }
    if (node->key < n->key)
    {
        PRINT_DBG("BinTreeNode_Insert: New left child of ");
        BinTreeNode_Print(n);
        PRINT_DBG("\n");
        BinTreeNode_SetLeftChild(n, node);
        return node;
    }
    else
    {
        PRINT_DBG("BinTreeNode_Insert: New right child of ");
        BinTreeNode_Print(n);
        PRINT_DBG("\n");
        BinTreeNode_SetRightChild(n, node);
        return node;
    }
}

int BinTreeNode_Destroy(BinTreeNode n)
{
    if (!n)
    {
        PRINT_DBG("BinTreeNode_Destroy: Called over NULL pointer\n");
        return -1;
    }
    PRINT_DBG("BinTreeNode_Destroy: START: %s\n", n->repr);
    free(n->repr);
    free(n);
    PRINT_DBG("BinTreeNode_Destroy: END: destroyed\n");
    return 0;
}

int BinTreeNode_DestroyGracefully(BinTreeNode n)
{
    if (!n)
        return -1;
    BinTreeNode_DestroyGracefully(n->right_child);
    BinTreeNode_DestroyGracefully(n->left_child);
    if (n->parent && (n == n->parent->left_child))
    {
        BinTreeNode_SetLeftChild(n->parent, NULL);
    }
    else
    {
        BinTreeNode_SetRightChild(n->parent, NULL);
    }
    BinTreeNode_Destroy(n);
    return 0;
}

BinTree BinTree_Init(void)
{
    PRINT_DBG("BinTree_Init: Initializing new BinTree\n");
    BinTree res = (BinTree) malloc(sizeof(BinTree));
    res->size = 0;
    res->root = NULL;
    PRINT_DBG("BinTree_Init: Initialized new BinTree at %p\n", res);
    return res;
}

int BinTree_Destroy(BinTree tree)
{
    PRINT_DBG("BinTree_Destroy: destroying BinTree at %p\n", tree);
    if (!tree)
    {
        PRINT_DBG("BinTree_Destroy: Tree is NULL\n");
        return -1;
    }
    BinTreeNode_DestroyGracefully(tree->root);
    free(tree);
    PRINT_DBG("BinTree_Destroy: Tree destroyed\n");
    return 0;
}

void* BinTree_Find(BinTree tree, int key)
{
    PRINT_DBG("BinTree_Find: %p, key = %d\n", tree, key);
    if (!tree)
    {
        PRINT_DBG("BinTree_Find: tree is NULL\n");
        return NULL;
    }
    BinTreeNode res;
    res = BinTreeNode_Find(tree->root, key);
    if (res && res->key == key)
    {
        PRINT_DBG("BinTree_Find: FOUND\n");
        return res->value;
    }
    PRINT_DBG("BinTree_Find: NOT FOUND\n");
    return NULL;
}
