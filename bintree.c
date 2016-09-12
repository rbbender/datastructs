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

char* BinTreeNode_Repr(BinTreeNode n)
{
    if (!n)
        return "";
    return n->repr;
}

int BinTreeNode_PrintLink(BinTreeNode n1, BinTreeNode n2)
{
    BinTreeNode_Print(n1);
    PRINT_DBG(" -> ");
    BinTreeNode_Print(n2);
    return 0;
}

BinTreeNode BinTreeNode_Init(int key, void* val_p, BinTreeNode obj)
{
    PRINT_DBG("BinTreeNode_Init: START: key = %d, val_p = %p, obj = %p\n", key, val_p, obj);
    BinTreeNode res;
    res = obj;
    if (!res)
        res = (BinTreeNode) malloc(sizeof(struct bintree_node));
    else
        PRINT_DBG("BinTreeNode_Init: re-using existing object\n");
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
    if (node)
        node->left_child = lchild;
    else
        PRINT_DBG("BinTreeNode_SetLeftChild: node is NULL. Just setting it as parent\n");
    BinTreeNode_SetParent(node, lchild);
    return 0;
}

int BinTreeNode_SetRightChild(BinTreeNode node, BinTreeNode rchild)
{
    PRINT_DBG("BinTreeNode_SetRightChild: ");
    BinTreeNode_PrintLink(node, rchild);
    PRINT_DBG("\n");
    if (node)
        node->right_child = rchild;
    else
        PRINT_DBG("BinTreeNode_SetRightChild: node is NULL. Just setting it as parent\n");
    BinTreeNode_SetParent(node, rchild);
    return 0;
}

BinTreeNode BinTreeNode_Find(BinTreeNode node, int key)
{
    PRINT_DBG("BinTreeNode_Find: key = %d, node = %s\n", key, BinTreeNode_Repr(node));
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
        PRINT_DBG("BinTreeNode_Find: NOT FOUND. p = %s\n", BinTreeNode_Repr(p));
        return p;
    }
    PRINT_DBG("BinTreeNode_Find: FOUND. t = %s\n", BinTreeNode_Repr(t));
    return t;
}

BinTreeNode BinTreeNode_Insert(BinTreeNode root, BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_Insert: root = %s, node = %s\n", BinTreeNode_Repr(root), BinTreeNode_Repr(node));
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
        PRINT_DBG("BinTreeNode_Insert: New left child of %s\n", BinTreeNode_Repr(n));
        BinTreeNode_SetLeftChild(n, node);
        return node;
    }
    else
    {
        PRINT_DBG("BinTreeNode_Insert: New right child of %s\n", BinTreeNode_Repr(n));
        BinTreeNode_SetRightChild(n, node);
        return node;
    }
}

int BinTreeNode_IsLeftChild(BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_IsLeftChild: node = %s\n", BinTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("BinTreeNode_IsLeftChild: node is NULL. Return 0\n");
        return 0;
    }
    if (!node->parent)
    {
        PRINT_DBG("BinTreeNode_IsLeftChild: node->parent is NULL. Return 0\n");
        return 0;
    }
    if (node->parent->left_child == node)
    {
        PRINT_DBG("BinTreeNode_IsLeftChild: TRUE: ");
        BinTreeNode_PrintLink(node->parent, node);
        PRINT_DBG("\n");
        return 1;
    }
    else
    {
        PRINT_DBG("BinTreeNode_IsLeftChild: FALSE: ");
        BinTreeNode_PrintLink(node->parent, node);
        PRINT_DBG("\n");
        return 0;
    }
}

int BinTreeNode_IsRightChild(BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_IsRightChild: node = %s\n", BinTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("BinTreeNode_IsRightChild: node is NULL. Return 0\n");
        return 0;
    }
    if (!node->parent)
    {
        PRINT_DBG("BinTreeNode_IsRightChild: node->parent is NULL. Return 0\n");
        return 0;
    }
    if (node->parent->right_child == node)
    {
        PRINT_DBG("BinTreeNode_IsRightChild: TRUE: ");
        BinTreeNode_PrintLink(node->parent, node);
        PRINT_DBG("\n");
        return 1;
    }
    else
    {
        PRINT_DBG("BinTreeNode_IsRightChild: FALSE: ");
        BinTreeNode_PrintLink(node->parent, node);
        PRINT_DBG("\n");
        return 0;
    }
}

BinTreeNode BinTreeNode_Remove(BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_Remove: node = %s\n", BinTreeNode_Repr(node));
    BinTreeNode next = node;
    if (!node)
    {
        PRINT_DBG("BinTreeNode_Remove: node is NULL\n");
        return NULL;
    }
    if (!node->left_child && !node->right_child)
    {
        PRINT_DBG("BinTreeNode_Remove: node is leaf\n");
        if(BinTreeNode_IsLeftChild(node))
            BinTreeNode_SetLeftChild(node->parent, NULL);
        else if (BinTreeNode_IsRightChild(node))
            BinTreeNode_SetRightChild(node->parent, NULL);
        next = NULL;
    }
    else if (node->left_child && !node->right_child)
    {
        PRINT_DBG("BinTreeNode_Remove: node has only left child\n");
        if (BinTreeNode_IsLeftChild(node))
            BinTreeNode_SetLeftChild(node->parent, node->left_child);
        else
            BinTreeNode_SetRightChild(node->parent, node->left_child);
        next = node->left_child;
    }
    else if (!node->left_child && node->right_child)
    {
        PRINT_DBG("BinTreeNode_Remove: node has only right child\n");
        if (BinTreeNode_IsLeftChild(node))
            BinTreeNode_SetLeftChild(node->parent, node->right_child);
        else
            BinTreeNode_SetRightChild(node->parent, node->right_child);
        next = node->right_child;
    }
    else
    {
        PRINT_DBG("BinTreeNode_Remove: Node has both childs, promoting next\n");
        BinTreeNode n = BinTreeNode_Next(node);
        BinTreeNode_Remove(n);
        BinTreeNode_SetLeftChild(n, node->left_child);
        BinTreeNode_SetRightChild(n, node->right_child);
        if (BinTreeNode_IsLeftChild(node))
            BinTreeNode_SetLeftChild(node->parent, n);
        else
            BinTreeNode_SetRightChild(node->parent, n);
        next = n;
    }
    BinTreeNode_SetParent(NULL, node);
    BinTreeNode_SetLeftChild(node, NULL);
    BinTreeNode_SetRightChild(node, NULL);
    return next;
}

BinTreeNode BinTreeNode_Next(BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_Next: node = %s\n", BinTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("BinTreeNode_Next: node is NULL\n");
        return NULL;
    }

    BinTreeNode next = node;
    if (node->right_child)
    {
        PRINT_DBG("BinTreeNode_Next: node->right_child not NULL\n");
        next = node->right_child;
        while(next->left_child)
            next = next->left_child;
    }
    else if (BinTreeNode_IsLeftChild(node))
    {
        PRINT_DBG("BinTreeNode_Next: node is left child\n");
        next = node->parent;
    }
    PRINT_DBG("BinTreeNode_Next: FOUND next = %s\n", BinTreeNode_Repr(next));
    return next;
}

BinTreeNode BinTreeNode_Prev(BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_Prev: node = %s\n", BinTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("BinTreeNode_Prev: node is NULL\n");
        return NULL;
    }

    BinTreeNode prev = node;
    if (node->left_child)
    {
        PRINT_DBG("BinTreeNode_Prev: node->left_child not NULL\n");
        prev = node->left_child;
        while(prev->right_child)
            prev = prev->right_child;
    }
    else if (BinTreeNode_IsRightChild(node))
    {
        PRINT_DBG("BinTreeNode_Prev: node is right child\n");
        prev = node->parent;
    }
    PRINT_DBG("BinTreeNode_Prev: FOUND prev = %s\n", BinTreeNode_Repr(prev));
    return prev;
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

void BinTreeNode_PrintInOrder(BinTreeNode node)
{
    if (!node)
        return;
    BinTreeNode_PrintInOrder(node->left_child);
    PRINT("%s ", BinTreeNode_Repr(node));
    BinTreeNode_PrintInOrder(node->right_child);
}

int BinTreeNode_PrintSubTree(BinTreeNode node, int level_limit)
{
    int nodes = 1;
    int cur_level_limit;
    int next_level_position;
    int i;
    BinTreeNode temp;
    if (!node) {
        PRINT_DBG("BinTreeNode_PrintSubTree: node is NULL\n");
        return -1;
    }
    for (i=1; i < level_limit; ++i) {
        nodes += 1 << i;
    }

    BinTreeNode* nodeQueue = (BinTreeNode*) malloc (nodes * sizeof(BinTreeNode));
    nodeQueue[0] = node;
    next_level_position = 1;
    i = 0;
    while(i < next_level_position)
    {
        cur_level_limit = next_level_position;
        for (; i < cur_level_limit; ++i) {
            temp = nodeQueue[i];
            BinTreeNode_Print(temp);
            if (temp->left_child)
                nodeQueue[next_level_position++] = temp->left_child;
            if (temp->right_child)
                nodeQueue[next_level_position++] = temp->right_child;
        }
        PRINT_DBG("\n");
    }
    free(nodeQueue);
}

int BinTreeNode_RotateLeft(BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_RotateLeft: %s\n", BinTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("BinTreeNode_RotateLeft: node is NULL\n", BinTreeNode_Repr(node));
        return -1;
    }
    BinTreeNode parent = node->parent;
    BinTreeNode lc, rc;
    lc = rc = NULL;
    rc = node->right_child;
    if (rc)
        lc = rc->left_child;
    BinTreeNode_SetRightChild(node, lc);
    if (BinTreeNode_IsLeftChild(node))
        BinTreeNode_SetLeftChild(parent, rc);
    else
        BinTreeNode_SetRightChild(parent, rc);
    BinTreeNode_SetLeftChild(rc, node);
    return 0;
}

int BinTreeNode_RotateRight(BinTreeNode node)
{
    PRINT_DBG("BinTreeNode_RotateRight: %s\n", BinTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("BinTreeNode_RotateRight: node is NULL\n", BinTreeNode_Repr(node));
        return -1;
    }
    BinTreeNode parent = node->parent;
    BinTreeNode lc, rc;
    lc = rc = NULL;
    lc = node->left_child;
    if (lc)
        rc = lc->right_child;
    BinTreeNode_SetLeftChild(node, rc);
    if (BinTreeNode_IsLeftChild(node))
        BinTreeNode_SetLeftChild(parent, lc);
    else
        BinTreeNode_SetRightChild(parent, lc);
    BinTreeNode_SetRightChild(lc, node);
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

int BinTree_Insert(BinTree tree, int key, void* value)
{
    BinTreeNode newNode;
    newNode = BinTreeNode_Init(key, value, NULL);
    BinTreeNode_Insert(tree->root, newNode);
    if (!tree->root)
        tree->root = newNode;
    ++(tree->size);
    return 0;
}

int BinTree_Remove(BinTree tree, int key)
{
    BinTreeNode node, next;
    node = BinTreeNode_Find(tree->root, key);
    if (!node || node->key != key)
    {
        PRINT_DBG("BinTree_Remove: node not found\n");
        return -1;
    }
    PRINT_DBG("BinTree_Remove: node = %s\n", BinTreeNode_Repr(node));
    next = BinTreeNode_Remove(node);
    if (node == tree->root)
        tree->root = next;
    --(tree->size);
    if (!tree->size)
        tree->root = NULL;
    BinTreeNode_Destroy(node);
    return 0;
}

int BinTree_PrintInOrder(BinTree tree)
{
    BinTreeNode_PrintInOrder(tree->root);
    PRINT("\n");
}

int BinTree_PrintSubTree(BinTree tree, int key, int levels)
{
    PRINT_DBG("BinTree_PrintSubTree: tree at %p, key = %d, levels = %d\n", tree, key, levels);
    BinTreeNode node = BinTreeNode_Find(tree->root, key);
    if (!node || node->key != key)
        return -1;
    BinTreeNode_PrintSubTree(node, levels);
}
