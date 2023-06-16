#include <iostream>
#include <cstdlib>
#include <ctime>

int* randnum();
int* bubble_sort(int *arr);

int main()
{
    clock_t start,end;
    start = clock();
    int NUM[10];
    int* ptr = randnum();
    for(int i = 0; i < 10; i++)
    {
        NUM[i] = *(ptr + i);
    }
    bubble_sort(NUM);
    for(int i = 0; i < 10; i++)
    {
        std::cout << NUM[i] << " ";
    }
    end = clock();
    std::cout<<std::endl;
    std::cout<<"程序运行时间:"<<(double)(end-start)/CLOCKS_PER_SEC<< std::endl;
    return 0;
}

int* randnum()
{
    static int NUM_arr[10];
    srand(static_cast<unsigned int>(time(nullptr)));
    for(int i = 0; i < 10; i++)
    {
        NUM_arr[i] = rand()%100;
    }
    return NUM_arr;
}

int* bubble_sort(int *arr)
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9 - i; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return arr;
}
