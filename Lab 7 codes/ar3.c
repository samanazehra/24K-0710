#include <stdio.h>
int main(){
    int size;
    printf("Please enter the size of your array:  ");
    scanf("%d",&size);
    int array[size], min, max;
    printf("Enter your number:  ");
    scanf("%d",&array[0]);
     min=array[0];
     max=array[0];
    for (int i=1;i<size;i++){
        printf("Enter your number:  ");
        scanf("%d",&array[i]);
        if (min>array[i])
        min=array[i];
        if (max<array[i])
        max=array[i];
    }printf("The maximum number in this array is: %d\n",max);
     printf("The minimum number in this array is: %d",min);
     return 0;
}
