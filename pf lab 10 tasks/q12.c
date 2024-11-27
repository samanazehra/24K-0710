#include <stdio.h>

int linearSearch(int arr[], int size, int target, int index) {
    if (index == size) return -1; 
    if (arr[index] == target) return index; 
    return linearSearch(arr, size, target, index + 1);
}

int main() {
    int n, target;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the target element to search for: ");
    scanf("%d", &target);

    int result = linearSearch(arr, n, target, 0);
    if (result == -1) {
        printf("Element not found.\n");
    } else {
        printf("Element found at index %d.\n", result);
    }

    return 0;
}
