#include<stdio.h>
int Product(int a, int b);
int main()
{
    int number1, number2;
    printf("Enter your first number: ");
    scanf("%d",&number1);
    printf("Enter your second number: ");
    scanf("%d",&number2);
    printf("The product of %d and %d is: %d",number1,number2,Product(number1,number2));
    return 0;
}
int Product(int a, int b)
{
    return a*b;
}