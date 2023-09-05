#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree
{
    char Data;
    BinaryTree* left_child;
    BinaryTree* right_child;
} BinaryTree;

typedef struct BinaryTree BiTree;

//三种遍历方法
void PreOrderTraverse(BiTree* T);   //前序遍历
void InOrderTraverse(BiTree* T);   //中序遍历
void PostOrderTraverse(BiTree* T);   //后序遍历

int main()
{
    return 0;
}

//遍历
void PreOrderTraverse(BiTree* T)
{
    if(T == NULL)
    return;
    printf("%c\n",T -> Data);
    PreOrderTraverse(T -> left_child);
    PreOrderTraverse(T -> right_child);
}

void InOrderTraverse(BiTree* T)
{
    if(T == NULL)
    return;
    InOrderTraverse(T -> left_child);
    printf("%c\n",T -> Data);
    InOrderTraverse(T -> right_child);
}

void PostOrderTraverse(BiTree* T)
{
    if(T == NULL)
    return;
    PostOrderTraverse(T -> left_child);
    PostOrderTraverse(T -> right_child);
    printf("%c\n",T -> Data);
}