#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
int sum_arr (int arr[], int size)
{
    int S = 0;
    for (int i = 0; i < size; i++)
    {
        S += arr[i];
    }
    return S;
}
int main(void)
{
    
    int arr[1000];
    for (int i = 0; i<1000; i++)
    {
        arr[i] = i;
    }
    int Sum = sum_arr(arr, 1000);
    printf("Sum = : %d\n", Sum);
    return 0;

}
