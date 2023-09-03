#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
    double Data;
    struct Node *Next;
} Node;

typedef struct Node list_node;

list_node* InitChain(double value);   //初始化创建一个空节点
void AddToChain();   //在尾部添加
list_node* TraversalChain(list_node* chian);   //遍历
list_node* SearchChain(list_node* Chain,int locaiton);   //查找元素
void InsertToChain(list_node* Chain,int location,double value);   //链中插入元素
void DeleteFromChain(list_node* Chain,int location);   //链中删除元素
void godbless();

int main()
{
    //测试
    list_node *p;
    p = InitChain(1.0);
    AddToChain(p,1.4);
    list_node* value = SearchChain(p,2);
    printf("%lf\n",value -> Data);
    TraversalChain(p);
    InsertToChain(p,2,2.3);
    InsertToChain(p,2,1.9);
    DeleteFromChain(p,2);
    TraversalChain(p);
    getchar();
    return 0;
}

//初始化链表
list_node* InitChain(double value)
{
    list_node* node = (list_node*)malloc(sizeof(list_node));
    node -> Data = value;
    node -> Next = NULL;
    return node;
}

//遍历及打印
list_node* TraversalChain(list_node* Chain)
{
    list_node* current = Chain;
    while(current -> Next != NULL)
    {
        printf("%lf ",current -> Data);   //这里打印不了最后一个元素
        current = current -> Next;
    }
    printf("%lf\n",current -> Data);   //补上最后一个元素
    return current;
}

//添加到链表尾部
void AddToChain(list_node* Chain, double value)
{
    //current当前值
    list_node* current = Chain;
    while(current -> Next != NULL)
    {
        current = current -> Next;
    }
    current -> Next = (list_node*)malloc(sizeof(list_node));
    //下一个节点
    current -> Next -> Data = value;
    current -> Next -> Next = NULL;
}

//搜寻值
list_node* SearchChain(list_node* Chain,int location)
{
    list_node* temp = Chain;
    for (int i = 0; i < (location - 1); i++)
    {
        if (temp->Next == NULL)
        {
            printf("Nothing there\n");
            return NULL;
        }
        temp = temp->Next;
    }
    //printf("%lf\n",temp -> Data);         //这里修改，避免InsertTOChain和DeleteFromChain调用时重复打印
                                            //请使用printf("%lf\n",value -> Data);打印值（list_ndoe* value = SearchChain()）
    return temp;
}

//插入链表
void InsertToChain(list_node* Chain,int location,double value)
{
    list_node* new_node = InitChain(value);
    list_node* former = SearchChain(Chain,(location - 1));
    if(former == NULL)
    {
        printf("Invaid loction\n");
        free(new_node);
        return;
    }
    new_node -> Next = former -> Next;
    former -> Next = new_node;
}

//从链表中删除
void DeleteFromChain(list_node* Chain,int location)
{
    list_node* former = SearchChain(Chain,(location - 1));
    if(former == NULL)
    {
        printf("Invaid loction\n");
        return;
    }
    list_node* deleted = former -> Next;
    former -> Next = deleted -> Next;
    free(deleted);
}

//佛祖保佑
void godbless()
{
    char *log = "\
                         _oo0oo_\r\n\
                        o8888888o\r\n\
                        88\" . \"88\r\n\
                        (| -_- |)\r\n\
                        0\\  =  /0\r\n\
                      ___/`---'\\___\r\n\
                    .' \\\\|     |// '.\r\n\
                   / \\\\|||  :  |||// \r\n\
                  / _||||| -:- |||||- \r\n\
                 |   | \\\\\\  - /// |   |\r\n\
                 | \\_|  ''\\---/''  |_/ |\r\n\
                 \\  .-\\__  '-'  ___/-. /\r\n\
               ___'. .'  /--.--\\  `. .'___\r\n\
            .\"\" '<  `.___\\_<|>_/___.' >' \"\".\r\n\
           | | :  `- \\`.;`\\ _ /`;.`/ - ` : | |\r\n\
           \\  \\ `_.   \\_ __\\ /__ _/   .-` /  /\r\n\
       =====`-.____`.___ \\_____/___.-`___.-'=====\r\n\
                         `=---='\r\n\
\r\n\
       ~~~~~~~~~~~~~~~~~~~~XCMD~~~~~~~~~~~~~~~~~~~\r\n\
           \xE4\xBD\x9B\xE7\xA5\x96\xE4\xBF\x9D\xE4\xBD\x91      \xE6\xB0\xB8\xE4\xB8\x8D\xE5\xAE\x95\xE6\x9C\xBA      \xE6\xB0\xB8\xE6\x97\xA0\x42\x55\x47\r\n ";
printf("%s",log);
}
