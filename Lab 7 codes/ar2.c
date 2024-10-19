#include <stdio.h>
int main(){
    int size;
    printf("Please enter the size of your array:  ");
    scanf("%d",&size);
    int numbers[size],i;
    for (i=0;i<size;i++){
        printf("Enter your number:  ");
        scanf("%d",&numbers[i]);
    }for(i=size-1;i>=0;i--){
    printf("%d\n",numbers[i]);
    }
    return 0;
}