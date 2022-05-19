#include <stdio.h>

int main()
{
    int arr[5] = {5, 1, 4, 2, 3}, temp, index = 0;
    int min = arr[0];
    for (int i = 0; i < 5; i++)
    {
        index = i;
        for (int j = i; i < 5; j++)
        {
            if (arr[j] <= min)
            {
                index = j;
            }
        }
        temp = arr[index];
        arr[index] = arr[i];
        arr[i] = temp;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
}