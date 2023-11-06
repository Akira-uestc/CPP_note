#include <stdio.h>

#define MAX_LENGTH 128

int queue[MAX_LENGTH];
int front = 0;
int rear = 0;

void EnQueue();
void DeQueue();
int QueueState();

int main()
{
    int x = 0;
    while (1)
    {
        QueueState();
        printf("1.入队, 2.出队\n");
        scanf("%d", &x);
        switch (x)
        {
        case 1:
            EnQueue();
            break;
        case 2:
            DeQueue();
            break;
        default:
            continue;
        }
    }
    return 0;
}
void EnQueue()
{
    int data;
    if ((rear + 1) % MAX_LENGTH == front)
    {
        printf("该循环队列已满\n");
        return;
    }
    printf("请输入要入队的元素: ");
    scanf("%d", &data);
    queue[rear] = data;
    rear = (rear + 1) % MAX_LENGTH;
    printf("入队成功\n");
}

void DeQueue()
{
    if (front == rear)
    {
        printf("该循环队列为空\n");
        return;
    }
    int data = queue[front];
    front = (front + 1) % MAX_LENGTH;
    printf("出队元素为: %d\n", data);
}

int QueueState()
{
    if ((rear + 1) % MAX_LENGTH == front)
    {
        printf("该循环队列已满\n");
        return 1;
    }
    else if (front == rear)
    {
        printf("该循环队列为空\n");
        return -1;
    }
}
