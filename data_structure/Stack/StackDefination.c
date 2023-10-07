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
void InStack(Index* index);
void OutStack(Index* index);
void PrintStack(Index* index);

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
    header->stack_length = 0;
    header->Data = 0;
    header->prev = NULL;
    header->next = NULL;
    index[index->count].stack_num = header;
    printf("栈标号为：%d\n",index->count);
    index->count += 1;
}

void InStack(Index* index)
{
    int num;
    double value;
    printf("输入栈标号与要插入的值: ");
    scanf("%d %lf", &num, &value);
    
    if (index[num].stack_num->stack_length == 0)
    {
        index[num].stack_num->stack_length += 1;
        index[num].stack_num->Data = value;
    }
    else
    {
        Stack* current = index[num].stack_num;
        while (current->next != NULL)
        {
            current = current->next;
        }
        
        Stack* new = (Stack*)malloc(sizeof(Stack));
        new->Data = value;
        new->prev = current;
        current->next = new;
        index[num].stack_num->stack_length += 1;
    }
}

void OutStack(Index* index)
{
    int num;
    printf("输入要出栈的栈标号: ");
    scanf("%d", &num);

    if (index[num].stack_num->stack_length == 0)
    {
        printf("栈为空，无法出栈。\n");
        return;
    }
    
    Stack* top = index[num].stack_num;
    
    if (top->stack_length == 1)
    {
        free(top);
        index[num].stack_num = NULL;
    }
    else
    {
        Stack* newTop = top->prev;
        newTop->next = NULL;
        free(top);
        index[num].stack_num = newTop;
    }
    
    index[num].stack_num->stack_length -= 1;
    printf("出栈成功。\n");
}

void PrintStack(Index* index)
{
    int num;
    printf("输入要打印的栈标号: ");
    scanf("%d", &num);

    Stack* current = index[num].stack_num;

    if (current == NULL)
    {
        printf("栈为空，无法打印。\n");
        return;
    }

    printf("栈%d的元素:", num);
    
    while (current != NULL)
    {
        printf("%.2lf ", current->Data);
        current = current->next;
    }

    printf("\n");
}