#include<stdio.h>
int main() {
    int size,i;
    printf("Array Size = ");
    scanf("%d",&size);
    int arr[size];
    for(i=0;i<size;i++) {
        printf("Element %d = ",i+1);
        scanf("%d",&arr[i]);
    }
    int count[size];
    for(i=0;i<size;i++) {
        count[i]=0;
    }
    for(i=0;i<size;i++) {
        count[arr[i]]++;
    }
    printf("Elements occurring more than once: ");
    int found=0;
    for(i=0;i<size;i++) {
        if(count[i]>1) {
            printf("%d ",i);
            found=1;
        }
    }
    if(!found) {
        printf("None");
    }
    printf("\n");
    return 0;
}