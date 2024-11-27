#include <stdio.h>

void printArray(int arr[], int size)
{
    if (size == 0)
        return;
    printf("%d ", arr[0]);
    printArray(arr + 1, size - 1);
}

int main()
{
    int size;
    printf("Enter array size: ", size);
    scanf("%d", &size);
    int arr[size];
    for (int i=0; i<size; i++){
        printf("Enter element %d: ", i+1);
        scanf("%d", &arr[i]);
    }
    printArray(arr, size);
    return 0;
}
