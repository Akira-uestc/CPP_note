//
// Created by Akira-Amatsume on 2023/10/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReadDataFromCSV(allBooks_Linear *header, const char *filename)
{
    return;
}

void ReadDataFromCSV_Linear(allBooks_Linear *header, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    char line[256]; // 假设每行不超过 256 字符

    // 逐行读取 CSV 文件
    while (fgets(line, sizeof(line), file)) {
        allBooks_Linear book;
        borrow_info_Linear log;

        char *token = strtok(line, ",");
        if (token != NULL) {
            book.book_id = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(book.book_name, token, sizeof(book.book_name));
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(book.author, token, sizeof(book.author));
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(book.press, token, sizeof(book.press));
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            book.publish_time = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            book.accessibility = atoi(token);
        }
    }
    fclose(file);
}
