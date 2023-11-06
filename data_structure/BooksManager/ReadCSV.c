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
    tok = wcstok(line, L",",&saveptr);
    for (int i = 1; i != num; i++)
    {
        tok = wcstok(NULL, L",",&saveptr);
        if (tok == NULL)
        {
            return NULL;
        }
    }
    wchar_t *result = remove_quoted(tok);
    return result;
}

void WriteToLinearList(const wchar_t *filename)
{
    FILE *file = _wfopen(filename, L"r,ccs=UTF-8");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return;
    }
    wchar_t line[128];
    wchar_t *tmp;
    allBooks_Linear book;
    while (fgetws(line, 128, file) != NULL)
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
        wprintf(L"%u,%ls,%ls,%ls,%d\n", book.book_id, book.book_name, book.author, book.press, book.publish_time);
    }
    fclose(file);
    return;
}

int main()
{
    setlocale(LC_CTYPE, "chs");
    WriteToLinearList(L"books.csv");
    getchar();
    return 0;
}