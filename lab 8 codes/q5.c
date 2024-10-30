#include<stdio.h>
int main (){
   int number;
   int i, j;
   printf("Please enter the odd number you want to start your sequence with: ");
   scanf("%d",&number);
   if (number<1){
       printf("\nInvalid input. Make sure your entered number is an odd number greater than 0.\n");
       return 1;
   }if (number%2!=1){
       number--;
   }for (i=0; number-2*i>0; i++){
       for (j=number-2*i; j>0; j-=2){
           printf("%d ",j);
       }printf("\n");
   }
    return 0;
}