#include "LinkListDefination.c"
#include "LinearListDefination.c"

int main()
{
    setlocale (LC_ALL,"");
    int division;
    printf("选择使用线性表还是链表:1.线性表 2.链表\n");
    scanf("%d",&division);
    switch (division)
    {
        case 1:
        {
            allBooks_Linear* header = (allBooks_Linear*)malloc(sizeof(allBooks_Linear));
            header->length = 0;
            header->log.length = 0;
            ReadCSV(header, "books.csv");
            int x = -1;
            while (1) 
            {
                printf("选择功能: \n");
                printf("\t\t\t\t1:录入图书信息\t\t\t\t\n");
                printf("\t\t\t\t2:删除指定图书\t\t\t\t\n");
                printf("\t\t\t\t3:输出全部图书信息\t\t\t\t\n");
                printf("\t\t\t\t4:搜索指定书籍\t\t\t\t\n");
                printf("\t\t\t\t5:借书\t\t\t\t\n");
                printf("\t\t\t\t6:还书\t\t\t\t\n");
                printf("\t\t\t\t7:查询借阅日志\t\t\t\t\n");
                scanf("%d",&x);
                switch (x) {
                    case 1:EnterBooksInfo_Linear(header);break;
                    case 2:DeleteFromBooks_Linear(header);break;
                    case 3:ShowAllBooks_Linear(header);break;
                    case 4:SearchBooks_Linear(header);break;
                    case 5:BorrowBooks_Linear(header);break;
                    case 6:ReturnBooks_Linear(header);break;
                    case 7:ShowLogs_Linear(header);break;
                    default:
                        printf("无效选择，请重新输入。\n");
                }
            }

        }
        case 2:
        {
            allBooks* books = (allBooks*)malloc(sizeof(allBooks));
            books->next = NULL;
            books->log = NULL;
            int x = -1;
            while(1)
            {
                printf("选择功能: \n");
                printf("\t\t\t\t1:录入图书信息\t\t\t\t\n");
                printf("\t\t\t\t2:删除指定图书\t\t\t\t\n");
                printf("\t\t\t\t3:输出全部图书信息\t\t\t\t\n");
                printf("\t\t\t\t4:搜索指定书籍\t\t\t\t\n");
                printf("\t\t\t\t5:借书\t\t\t\t\n");
                printf("\t\t\t\t6:还书\t\t\t\t\n");
                printf("\t\t\t\t7:查询借阅日志\t\t\t\t\n");
                scanf("%d",&x);
                switch(x)
                {
                    case 1:EnterBooksInfo(books); break;
                    case 2:DeleteFromBooks(books); break;
                    case 3:ShowAllBooks(books); break;
                    case 4:SearchBooks(books); break;
                    case 5:BorrowBooks(books);break;
                    case 6:ReturnBooks(books); break;
                    case 7:ShowLogs(books); break;
                    default:
                        printf("无效选择，请重新输入。\n");
                }
            }
        }
    }
}
