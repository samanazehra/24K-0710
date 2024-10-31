#include<stdio.h>
int EvenOrOdd(int a);
int main()
{
    int number;
    printf("Enter a number greater than or equal to 0:  ");
    scanf("%d",&number);
    EvenOrOdd(number);
    return 0;
    
}
int EvenOrOdd(int a)
{
    if (a>=0)
    {
    (a%2==0)?printf("%d is an even number",a):printf("%d is an odd number",a);
    }
    else printf("Invalid input, number must be a positive integer or zero.");
    return 0;
}