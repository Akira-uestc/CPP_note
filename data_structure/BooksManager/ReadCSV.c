#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include "LinearListDefination.c"
#include "LinkListDefination.c"

wchar_t *remove_quoted(wchar_t *str)
{
    int length = wcslen(str);
    wchar_t *result = malloc((length + 1) * sizeof(wchar_t));
    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] != L'"')
        {
            result[index] = str[i];
            index++;
        }
    }
    result[index] = L'\0';
    return result;
}
wchar_t *get_field(wchar_t *line, int num)
{
    wchar_t *tok;
    wchar_t *saveptr = NULL;
    tok = wcstok(line, L",", &saveptr);
    for (int i = 1; i != num; i++)
    {
        tok = wcstok(NULL, L",", &saveptr);
        if (tok == NULL)
        {
            return NULL;
        }
    }
    wchar_t *result = remove_quoted(tok);
    return result;
}

void WriteToLinearList(const wchar_t *filename, allBooks_Linear *header)
{
    FILE *file = _wfopen(filename, L"r,ccs=UTF-8");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return;
    }

    wchar_t line[1024];
    wchar_t *tmp;
    allBooks_Linear book;

    while (fgetws(line, 1024, file) != NULL)
    {
        tmp = get_field(wcsdup(line), 1);
        book.book_id = wcstol(tmp, NULL, 10);
        free(tmp);

        tmp = get_field(wcsdup(line), 2);
        wcscpy(book.book_name, tmp);
        free(tmp);

        tmp = get_field(wcsdup(line), 3);
        wcscpy(book.author, tmp);
        free(tmp);

        tmp = get_field(wcsdup(line), 4);
        wcscpy(book.press, tmp);
        free(tmp);

        tmp = get_field(wcsdup(line), 5);
        book.publish_time = wcstol(tmp, NULL, 10);
        free(tmp);

        // 使用二分查找法找到插入位置
        unsigned temp_id = book.book_id;
        int i = 0;
        if (header->length == 0)
        {
            i = 0;
        }
        if (header->length != 0)
        {
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
        }

        // 将后面的元素后移一位
        for (int j = header->length; j > i; j--)
        {
            header[j] = header[j - 1];
        }

        header[i] = book;
        header[i].accessibility = 1;
        header[i].log.length = 0;
        header->length += 1;
    }

    fclose(file);
    return;
}

void WriteToLinkList(const wchar_t *filename, allBooks *header)
{
    FILE *file = _wfopen(filename, L"r,ccs=UTF-8");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return;
    }
    wchar_t line[1024];
    wchar_t *tmp;
    allBooks *p, *q, *book;
    while (fgetws(line, 1024, file) != NULL)
    {
        book = (allBooks *)malloc(sizeof(allBooks));
        tmp = get_field(wcsdup(line), 1);
        book->book_id = wcstol(tmp, NULL, 10);
        free(tmp);
        tmp = get_field(wcsdup(line), 2);
        wcscpy(book->book_name, tmp);
        free(tmp);
        tmp = get_field(wcsdup(line), 3);
        wcscpy(book->author, tmp);
        free(tmp);
        tmp = get_field(wcsdup(line), 4);
        wcscpy(book->press, tmp);
        free(tmp);
        tmp = get_field(wcsdup(line), 5);
        book->publish_time = wcstol(tmp, NULL, 10);
        free(tmp);
        book->accessibility = 1;
        book->log = NULL;
        book->next = NULL;
        p = header;
        q = p->next;
        while (q != NULL && q->book_id < book->book_id)
        {
            p = q;
            q = q->next;
        }
        p->next = book;
        book->next = q;
    }
    fclose(file);
    return;
}
