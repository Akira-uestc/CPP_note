//
// Created by Akira-Amatsume on 2023/10/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct borrow_info
{
    int year;
    int month;
    int day;
    wchar_t borrower[40];
    int frequency;
    struct borrow_info *next;
} borrow_info;

typedef struct allBooks
{
    unsigned int book_id;
    wchar_t book_name[100];
    wchar_t author[40];
    wchar_t press[100];
    int publish_time;
    int accessibility;
    borrow_info* log;
    struct allBooks *next;
} allBooks;

void InsertInBookIDOrder(allBooks *header);
void EnterBooksInfo(allBooks *header);
void DeleteFromBooks(allBooks *header);
void ShowAllBooks(allBooks *header);
void SearchBooks(allBooks *header);
void BorrowBooks(allBooks *header);
void ReturnBooks(allBooks *header);
void ShowLogs(allBooks *header);

void InsertInBookIDOrder(allBooks *header)
{
    allBooks *newBook = (allBooks *)malloc(sizeof(allBooks));
    if (newBook == NULL)
    {
        printf("内存分配失败\n");
        return;
    }

    printf("请输入图书编号：");
    scanf("%u", &newBook->book_id);
    getchar();
    printf("请输入图书名称：");
    wscanf(L"%ls",newBook->book_name);
    printf("请输入作者姓名：");
    wscanf(L"%ls",newBook->author);
    printf("请输入出版社名称：");
    wscanf(L"%ls",newBook->press);
    printf("请输入出版年份：");
    scanf("%d", &newBook->publish_time);

    newBook->accessibility = 1;
    newBook->log = NULL;
    newBook->next = NULL;
    allBooks *p = header;
    allBooks *q = p->next;
    while (q != NULL && q->book_id < newBook->book_id)
    {
        p = q;
        q = q->next;
    }
    p->next = newBook;
    newBook->next = q;
}

void EnterBooksInfo(allBooks *header)
{
    int flag = 1;
    while(flag)
    {
        InsertInBookIDOrder(header);
        printf("是否继续输入?是:1,否:0 ");
        scanf("%d",&flag);
        if(flag!=1) flag =0;
    }
}

void DeleteFromBooks(allBooks *header)
{
    unsigned int id;
    printf("请输入要删除的图书编号：");
    scanf("%u", &id);
    allBooks *p = header;
    allBooks* q = p->next;
    while (q != NULL && q->book_id != id)
    {
        p = q;
        q = q->next;
    }
    if (q == NULL)
    {
        printf("没有找到编号为%u的图书\n", id);
        return;
    }
    p->next = q->next;
    borrow_info *r = q->log;
    while (r != NULL)
    {
        borrow_info *s = r->next;
        free(r);
        r = s;
    }
    free(q);
    printf("删除成功\n");
}

void ShowAllBooks(allBooks *header)
{
    allBooks *temp = header->next;
    if (temp == NULL)
    {
        printf("没有图书信息\n");
        return;
    }
    printf("编号\t名称\t作者\t出版社\t出版年份\t可借状态\n");
    while (temp != NULL)
    {
        wprintf(L"%u\t%ls\t%ls\t%ls\t%d\t", temp->book_id, temp->book_name, temp->author, temp->press, temp->publish_time);
        if (temp->accessibility == 1)
        {
            printf("可借\n");
        }
        else
        {
            printf("不可借\n");
        }
        temp = temp->next;
    }
}

void SearchBooks(allBooks* header)
{
    wchar_t keyword[20];
    printf("请输入要查找的图书名称或作者姓名：");
    wscanf(L"%ls",&keyword);
    allBooks *p = header->next;
    int flag = 0;
    while (p != NULL)
    {
        if (wcscmp(p->book_name, keyword) == 0 || wcscmp(p->author, keyword) == 0)
        {
            if (flag == 0)
            {
                printf("编号\t名称\t作者\t出版社\t出版年份\t可借状态\n");
                flag = 1;
            }
            wprintf(L"%u\t%ls\t%ls\t%ls\t%d\t", p->book_id, p->book_name, p->author, p->press, p->publish_time);
            if (p->accessibility == 1)
            {
                printf("可借\n");
            }
            else
            {
                printf("不可借\n");
            }
        }
        p = p->next;
    }
    if (flag == 0)
    {
        printf("没有找到相关的图书\n");
    }
}

void BorrowBooks(allBooks *header)
{
    unsigned int id;
    printf("请输入要借阅的图书编号：");
    scanf("%u", &id);
    allBooks *p = header->next;
    while (p != NULL && p->book_id != id)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        printf("没有找到编号为%u的图书\n", id);
        return;
    }
    if (p->accessibility == 0)
    {
        printf("该图书已被借出，不能再次借阅\n");
        return;
    }
    p->accessibility = 0;
    borrow_info *newLog = (borrow_info *)malloc(sizeof(borrow_info));
    if (newLog == NULL)
    {
        printf("内存分配失败\n");
        return;
    }
    borrow_info *temp = p->log;
    int current_frequency = 1;

    printf("请输入借阅日期（年-月-日）：");
    scanf("%d - %d - %d", &newLog->year, &newLog->month, &newLog->day);
    printf("请输入借阅者姓名：");
    wscanf(L"%ls",newLog->borrower);

    //适用于第一次借阅记录
    if(temp == NULL)
    {
        newLog->frequency = 1;
        newLog -> next = NULL;
        p->log = newLog;
    }
    //其后的借阅记录
    if(temp != NULL)
    {
        while (temp -> next != NULL)
        {
            temp = temp->next;
            current_frequency += 1;
        }
        newLog->frequency = current_frequency;
        newLog->next = NULL;
        temp->next = newLog;
    }
    printf("借阅成功\n\n");
}

void ReturnBooks(allBooks *header)
{
    unsigned int id;
    printf("请输入要归还的图书编号：");
    scanf("%u", &id);
    allBooks *p = header->next;
    while (p != NULL && p->book_id != id)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        printf("没有找到编号为%u的图书\n", id);
        return;
    }
    if (p->accessibility == 1)
    {
        printf("该图书没有被借出，无需归还\n");
        return;
    }
    p->accessibility = 1;
    borrow_info *q = p->log;
    if (q == NULL)
    {
        printf("该图书没有借阅记录，无法归还\n");
        return;
    }
    p->log = q->next;
    free(q);
    printf("归还成功\n");
}

void ShowLogs(allBooks *header)
{
    unsigned int id;
    printf("要查询借阅日志的图书编号:");
    scanf("%u",&id);
    allBooks *p = header->next;
    while (p != NULL && p->book_id != id)
    {
        p = p->next;
    }
    borrow_info *q = p->log;
    printf("\t借阅人\t借阅日期\n");
    if(q != NULL && q->next == NULL)
    {
        printf("\t%d-%d-%d\t",q->year,q->month,q->day);
        wprintf(L"%ls",q->borrower);
        printf("\n");
    }
    if(q != NULL && q->next != NULL)
    {
        while (q->next != NULL)
        {
            q = q->next;
            printf("\t%d-%d-%d\t",q->year,q->month,q->day);
            wprintf(L"%ls",q->borrower);
            printf("\n");
        }
    }
}
