//
// Created by Akira-Amatsume on 2023/10/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

typedef struct borrow_info_Linear
{
    int year;
    int month;
    int day;
    wchar_t borrower[40];
    int length;
} borrow_info_Linear;

typedef struct allBooks_Linear
{
    unsigned int book_id;
    wchar_t book_name[100];
    wchar_t author[40];
    wchar_t press[100];
    int publish_time;
    int accessibility;
    borrow_info_Linear log;
    int length;
} allBooks_Linear;

void InsertInBookIDOrder_Linear(allBooks_Linear *header)
{
    setlocale(LC_CTYPE, "chs");
    unsigned temp_id;
    printf("请输入图书编号:");
    scanf("%u",&temp_id);
    int i = 0;
    // 使用二分查找法找到插入位置
    int low = 0, high = header->length - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (header[mid].book_id == temp_id)
        {
            printf("该书已存在");
            return;
        }
        else if (header[mid].book_id < temp_id)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    i = low; // 插入位置为low
    // 将后面的元素后移一位
    for(int j = header-> length; j > i; j--)
    {
        header[j] = header[j-1];
    }
    // 插入新元素
    header[i].book_id = temp_id;
    printf("请输入图书名称：");
    wscanf(L"%ls", header[i].book_name);
    printf("请输入作者姓名：");
    wscanf(L"%ls", header[i].author);
    printf("请输入出版社名称：");
    wscanf(L"%ls", header[i].press);
    printf("请输入出版年份：");
    scanf("%d",&header[i].publish_time);
    header[i].accessibility = 1;
    header[i].log.length = 0;
    header -> length += 1;
}

void EnterBooksInfo_Linear(allBooks_Linear *header)
{
    int flag = 1;
    while(flag)
    {
        InsertInBookIDOrder_Linear(header);
        printf("是否继续输入?是:1,否:0 ");
        scanf("%d",&flag);
        if(flag!=1) flag =0;
    }
}

void DeleteFromBooks_Linear(allBooks_Linear *header)
{
    unsigned int id;
    int location = 0;
    printf("请输入要删除的图书编号：");
    scanf("%u", &id);

    for(int i = 0; i < header->length; i++)
    {
        if(id!=header[i].book_id)
            location++;
        else break;
    }

    //将id位置后的节点依次前移
    for(int j = location; j < header->length; j++)
    {
        header[j].book_id = header[j+1].book_id;
        wcscpy(header[j].book_name,header[j+1].book_name);
        wcscpy(header[j].author,header[j+1].author);
        wcscpy(header[j].press, header[j+1].press);
        header[j].publish_time = header[j+1].publish_time;
    }
    header->length -= 1;
}

void ShowAllBooks_Linear(allBooks_Linear *header)
{
    printf("编号\t名称\t作者\t出版社\t出版年份\t可借状态\n");
    
    for (int i = 0; i < header->length; i++)
    {
        printf("%u\t", header[i].book_id);
        printf("%ls\t", header[i].book_name);
        printf("%ls\t", header[i].author);
        printf("%ls\t", header[i].press);
        printf("%d\t", header[i].publish_time);
        
        if (header[i].accessibility == 1)
        {
            printf("可借\n");
        }
        else
        {
            printf("不可借\n");
        }
    }
}

void SearchBooks_Linear(allBooks_Linear *header)
{
    wchar_t keyword[20];
    printf("请输入要查找的图书名称或作者姓名：");
    wscanf(L"%ls",&keyword);
    int flag = 0;
    for(int i = 0 ; i < header->length ; i++)
    {
        if(wcscmp(header[i].book_name, keyword) == 0 || wcscmp(header[i].author, keyword) == 0)
        {
            if (flag == 0)
            {
                printf("编号\t名称\t作者\t出版社\t出版年份\t可借状态\n");
                flag = 1;
            }
            printf("%u\t%ls\t%ls\t%ls\t%d\t", header[i].book_id, header[i].book_name,header[i].author, header[i].press, header[i].publish_time);
            if (header[i].accessibility == 1)
            {
                printf("可借\n");
            }
            else
            {
                printf("不可借\n");
            }
        }
    }
    if (flag == 0)
    {
        printf("没有找到与%s相关的图书\n", keyword);
    }
}

void BorrowBooks_Linear(allBooks_Linear *header)
{
    unsigned int id;
    int location = 0;
    int flag = 0;
    printf("请输入要借阅的图书编号：");
    scanf("%u", &id);

    for(int i = 0; i < header->length; i++)
    {
        if(id!=header[i].book_id)
            location++;
        if(id == header[i].book_id)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0) printf("无此书\n");
    if(flag == 1)
    {
        if(header[location].accessibility == 0) printf("不可借\n");
        if(header[location].accessibility == 1)
        {
            header[location].accessibility = 0;
            int k = 0;
            for (int m = 0; m < header[location].log.length; m++) {k++;}
            printf("请输入借阅日期（年-月-日）：");
            scanf("%d - %d - %d", &header[location].log.year + k, &header[location].log.month + k,&header[location].log.day + k);
            printf("请输入借阅者姓名：");
            wscanf(L"%ls",&header[location].log.borrower + k);
            header[location].log.length += 1;
            printf("借阅成功\n");
        }
    }
}

void ReturnBooks_Linear(allBooks_Linear *header)
{
    unsigned int id;
    int location = 0;
    int flag = 0;
    printf("请输入要归还的图书编号：");
    scanf("%u", &id);

    for(int i = 0; i < header->length; i++)
    {
        if(id!=header[i].book_id)
            location++;
        if(id == header[i].book_id)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0) printf("无此书");
    if(flag == 1)
    {
        if(header[location].accessibility == 1) printf("此书未被借阅，无需归还\n");
        if(header[location].accessibility == 0)
        {
            header[location].accessibility = 1;
            printf("归还成功\n");
        }
    }
}

void ShowLogs_Linear(allBooks_Linear *header)
{

    unsigned int id;
    int location = 0;
    int flag = 0;
    printf("请输入要查询日志的图书编号：");
    scanf("%u", &id);

    for(int i = 0; i < header->length; i++)
    {
        if(id!=header[i].book_id)
            location++;
        if(id == header[i].book_id)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0) printf("无此书");
    if(flag == 1)
    {
        if(header[location].log.length == 0) printf("无借阅日志\n");
        if(header[location].log.length)
        {
            printf("\t借阅日期\t借阅人\n");
            for(int j = 0; j < header[location].log.length; j++)
            {
                printf("\t%d - %d - %d\t",header[location].log.year + j,header[location].log.month + j,header[location].log.day + j);
                wprintf(L"%ls\n",header[location].log.borrower + j);
            }
        }
    }
}
