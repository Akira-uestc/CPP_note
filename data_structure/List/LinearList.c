#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
说明：
length 创建的线性表长度
location 插入删除或赋值位置
*/

double* InitList(int Length);  //初始化线性表
void PrintList(int* length,double*List_array);  //打印线性表
double SearchList(int number,double*List_array);  //查找线性表中的元素
void ChangeValue(int location,double value,double*List_array);  //改变表中指定元素的值
void InsertToList(int* length,int location,double InsertNumber, double*List_array);  //插入元素
void DeleteFromList(int* length,int location,double*List_array);  //删除元素

int main()
{
    //测试
    double* p;
    int initl = 10;
    int* length = &initl;
    p = InitList(10);
    ChangeValue(5,5.0,p);
    InsertToList(length,3,1.4,p);
    PrintList(length,p);
    double value = SearchList(5,p);
    printf("%lf\n",value);
    getchar();
    return 0;
}

double* InitList(int Length)
{
    double* LinearList = (double*)malloc(Length * sizeof(double));
    return LinearList;
}

void PrintList(int* length,double*List_array)
{
    double* temp = List_array;
    for(int i = 0;i < *length;i++)  //指针后移遍历数组
    {
        printf("%lf ",*temp);
        temp++;
    }
    printf("\n");
}

double SearchList(int number,double*List_array)
{
  double* temp = List_array + number - 1;
  return *temp;
}

void ChangeValue(int location,double value,double*List_array)
{
    *(List_array+location-1) = value;
}


/*
最开始在这里直接使用 endv = 0 或 endv != 0 进行判断。无法得出正确结果
后来查资料得知C语言中浮点数储存为一个极小的值，打断点调试得为-4.8e-23
因此通过fabs()函数取绝对值，判断其是否小于 1e-15
*/
void InsertToList(int* length,int location,double InsertNumber, double*List_array)
{
    
    double endv = *(List_array + *length - 1);
    if(location > *length||location < 0)   //判断插入位置是否在线性表上
    {
        printf("Invaid location\n");
    }
    if(fabs(endv) <= 1e-15)
    {
        for(int i = *length;i > location;i--)
        {
            *(List_array + i - 1) = *(List_array + i - 2);  //从插入点依次把前一个位置的值赋给后一个位置
        }
        *(List_array + location - 1) = InsertNumber;  //插入数值
        *length += 1;
    }
    if(fabs(endv) >= 1e-15)  //表满
    {
        printf("Out of length\n");

    }
}

void DeleteFromList(int* length,int location,double*List_array)
{
    if(location > *length||location < 0) printf("Invaid location\n");
    else for(int i = location;i < *length;i++)
    {
        *(List_array + i - 1) = *(List_array + i);  //从删除点依次把后一个位置的值赋给前一个位置
        *(List_array + *length - 1) = 0;
        *length -= 1;
    }
}
