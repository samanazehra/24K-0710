#include <stdio.h>
int main(){
    int size;
    printf("Please enter the size of array:  ");
    scanf("%d",&size);
    int numbers[size],i,sum=0;
    for (i=0;i<size;i++){
        printf("Enter your number:  ");
        scanf("%d",&numbers[i]);
        sum+=numbers[i];
    }printf("The sum is %d",sum);
    return 0;
}