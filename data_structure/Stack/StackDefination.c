#include <stdio.h>
#include <stdlib.h>

typedef struct StackDefination
{
    double Data;
    struct StackDefination* prev;
    struct StackDefination* next;
    int stack_length;
} Stack;

typedef struct Index
{
    int count;
    Stack* stack_num;
} Index;

void InitStack(Index* index);
void InStack();
void OutStack();
void PrintStack();

int main()
{
    Index* index = (Index*)malloc(sizeof(Index));
    index->count = 0;
    index->stack_num = NULL;
    InitStack(index);
    return 0;
}

void InitStack(Index* index)
{
    Stack* header = (Stack*)malloc(sizeof(Stack));
    index[index->count].stack_num = header;
    index->count += 1;
}