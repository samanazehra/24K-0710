#include<stdio.h>
void swapIntegers(int a, int b);
int main()
{
    int integer1, integer2;
    printf("Enter integer 1= ");\
    scanf("%d",&integer1);
    printf("Enter integer 2= ");
    scanf("%d",&integer2);
    swapIntegers(integer1, integer2);
return 0;
}
void swapIntegers(int a, int b)
{
    printf("Integers before swapping: %d, %d\n",a,b);
    a=a^b;
    b=a^b;
    a=a^b;
    printf("Integers after swapping: %d, %d",a,b);
}