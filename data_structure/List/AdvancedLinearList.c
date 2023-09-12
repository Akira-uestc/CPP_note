#include <stdio.h>
#include <stdlib.h>

typedef struct LinearList
{
    double* data;   //管理数组元素
    int size;   //数组中已储存的元素个数
    int max_space;   //需要的最大数组大小
} LinearList;

//通过Index结构管理所有已生成的线性表
typedef struct Index
{
    LinearList* num;
    int count;   //已生成的线性表数
} Index;

void InitList(Index* index);   //初始化一个线性表
int AssignValues(Index* index);   //批量赋值
void PrintList(Index* index);   //打印线性表
double SearchList(Index* index);   //搜索某个位置上的值
void ChangeList(Index* index);   //改变指定位置上的值
void InsertElement(Index* index);   //插值
void DeleteElement(Index* index);   //删除值
LinearList* UnionList(Index* index);   //求并集
LinearList* InterSectionList(Index* index);    //求交集


int main()
{
   Index* AllList = malloc(20*sizeof(Index));
   AllList->count = 0;
   int choose = -1;
   printf("\t1.初始化线性表\t\n\t2.给线性表赋值\t\n\t3.打印线性表\t\n\t4.搜索线性表\t\n\t5.改变指定位置的值\t\n\t6.插值\t\n\t7.删除值\t\n\t8.求交集\t\n\t9.求并集\t\n");
   while(1)
   {
    printf("选择功能:");
    scanf("%d",&choose);
    switch (choose)
    {
        case 1:InitList(AllList);break;
        case 2:AssignValues(AllList);break;
        case 3:PrintList(AllList);break;
        case 4:SearchList(AllList);break;
        case 5:ChangeList(AllList);break;
        case 6:InsertElement(AllList);break;
        case 7:DeleteElement(AllList);break;
        case 8:InterSectionList(AllList);break;
        case 9:UnionSectionList(AllList);
    }
   }
}

void InitList(Index* index)
{   
    printf("开始创建线性表\n");
    int max_space_temp = 0;
    LinearList* new = malloc(sizeof(LinearList));
    index->count += 1; 
    index[index->count].num = new;
    printf("分配给该线性表的最大空间？\n");
    scanf("%d",&max_space_temp);
    index[index->count].num->data = (double*)malloc(max_space_temp * sizeof(double));
    index[index->count].num->size = 0;
    index[index->count].num->max_space = max_space_temp;
    printf("创建成功，线性表标号为%d\n",index->count);
}

int AssignValues(Index* index)
{
    printf("要赋值的数组标号？\n");
    int num_temp = -1;
    scanf("%d",&num_temp);
    int temp = 0;
    char control = 'y';
    while(control == 'y') 
    {
        printf("输入一个数字： \n");
        scanf("%lf",&index[num_temp].num->data[temp]);
        getchar();
        temp++;
        index[num_temp].num->size = temp;
        printf("是否继续赋值? (y/n): ");
        scanf("%c",&control);
        if (temp >= index[num_temp].num->max_space) 
        {
            printf("列表已满，无法继续赋值。\n");
            return -1;
        }    
    }
    return 0;
}

void PrintList(Index* index)
{
    printf("要打印的数组标号？\n");
    int num_temp = -1;
    scanf("%d",&num_temp);
    getchar();    
    for(int i = 0; i < index[num_temp].num->size; i++)
    {
        printf("%lf ",index[num_temp].num->data[i]);
    }
    printf("\n");
}

double SearchList(Index* index)
{
    printf("要打印的数组标号？\n");
    int num_temp = -1;
    scanf("%d",&num_temp);
    int location = -1;
    printf("location?\n");
    scanf("%d",&location);
    if(location>index[num_temp].num->size||location < 0)
    {
        printf("No value there\n");
        return;
    }
    else printf("%lf",index[num_temp].num->data[location]);
}

void ChangeList(Index* index)
{
    printf("要打印的数组标号？\n");
    int num_temp = -1;
    scanf("%d",&num_temp);
    int location = -1;
    double value = -1;
    printf("location?\n");
    scanf("%d",&location);
    printf("赋值为?\n");
    scanf("%lf",&value);
    if(location>index[num_temp].num->size||location < 0)
    {
        printf("Invaid location\n");
        return;
    }
    else index[num_temp].num->data[location]=value;
}

void InsertElement(Index* index)
{
    printf("要插入的数组标号？\n");
    int num_temp = -1;
    scanf("%d",&num_temp);
    int location = -1,value = -1;
    printf("location?\n");
    scanf("%d",&location);
    printf("值为?\n");
    scanf("%d",&value);
    if(location > (index[num_temp].num->size + 1)||location < 0) 
    printf("Invaid location\n");
    if(location == index[num_temp].num->size + 1) 
    {
        index[num_temp].num -> data[location-1] = value;
        index[num_temp].num -> size += 1;
    }
    if(location <= index[num_temp].num->size&&location > 0)
    {
        for(int i = index[num_temp].num->size; i > location - 1; i--)
        {
            index[num_temp].num->data[i] = index[num_temp].num->data[i-1];
        }
        index[num_temp].num->data[location -1] = value;
        index[num_temp].num -> size += 1;
    }
}

void DeleteElement(Index* index)
{
    printf("要删除的数组标号？\n");
    int num_temp = -1;
    scanf("%d",&num_temp);
    int location = -1,value = -1;
    printf("location?\n");
    scanf("%d",&location);
    if(location > (index[num_temp].num->size + 1)||location < 0) 
    printf("Invaid location\n");
    if(location == (index[num_temp].num->size + 1))
    {
        index[num_temp].num->size -=1;
    }
    if(location <= index[num_temp].num->size&&location > 0)
    {
        for(int i = location - 1; i < index[num_temp].num -> size; i++ )
        {
            index[num_temp].num->data[i] = index[num_temp].num->data[i+1];
        }
        index[num_temp].num->size -= 1;
    }
}

LinearList* InterSectionList(Index* index)
{
    printf("输入要求交集的两个线性表标号");
    int la,lb;
    scanf("%d %d",&la,&lb);
    LinearList* list1 = index[la].num;
    LinearList* list2 = index[lb].num;
    LinearList* result = (LinearList*)malloc(sizeof(LinearList));
    index -> count += 1;
    index[index->count].num = result;
    int maxCapacity = (list1->size < list2->size) ? list1->size : list2->size;
    result->max_space = maxCapacity;
    result->data = (double*)malloc(maxCapacity*sizeof(double));
    result->size = 0;
    for (int i = 0; i < list1->size; i++) 
    {
        double element = list1->data[i];
        for (int j = 0; j < list2->size; j++) 
        {
            if (list2->data[j] == element) 
            {
                result->data[result->size] = element;
                result->size++;
                break;
            }
        }
    }
    printf("求交集成功，已分配标号%d\n",index->count);
    printf("请使用功能3查看结果\n");
    return result;
}

void UnionSectionList(Index* index) 
{
    printf("输入要求并集的两个线性表标号(使用空格分割标号):");
    int la,lb;
    scanf("%d %d",&la,&lb);
    LinearList* list1 = index[la].num;
    LinearList* list2 = index[lb].num;
    LinearList* result = (LinearList*)malloc(sizeof(LinearList));
    index -> count += 1;
    index[index->count].num = result;
    int maxCapacity = list1->size + list2->size;
    result->max_space = maxCapacity;
    result->data = (double*)malloc(maxCapacity*sizeof(double));
    result->size = 0;
    for (int i = 0; i < list2->size; i++)
    {
        result->data[result->size++] = list2->data[i];
    }
    for (int i = 0; i < list1->size; i++) 
    {
        double element = list1->data[i];
        int ifSame = 0;
        
        for (int j = 0; j < list2->size; j++) 
        {
            if (list2->data[j] == element) {
                ifSame = 1;
                break;
            }
        }
        if (!ifSame) 
        {
            result->data[result->size++] = element;
        }
    }
    printf("求并集成功，已分配标号%d\n",index->count);
    printf("请使用功能3查看结果\n");
    return result;
}
