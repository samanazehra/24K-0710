#include<stdio.h>
float Calculator(float a, float b, char o);
int main()
{
  float number1, number2;
  char operator1;
  printf("This calculator can perform four basic arithmetic operations such as addition, subtraction, multiplication and division.\n\n");
  printf("Enter your first number: ");
  scanf("%f",&number1);
  printf("Choosing from +, -, * or /, enter your operator: ");
  scanf(" %c",&operator1);
  printf("Enter your second number: ");
  scanf("%f",&number2);
  Calculator(number1, number2, operator1);
  return 0;
}
float Calculator(float a, float b, char o)
{
    switch (o)
    {
    case '+':
    printf("%.2f %c %.2f = %.2f",a, o, b, a+b);
    return a+b;
    break;
    case '-':
    printf("%.2f %c %.2f = %.2f",a, o, b, a-b);
    return a-b;
    break;
    case '*':
    printf("%.2f %c %.2f = %.2f",a, o, b, a*b);
    return a*b;
    break;
    case '/':
    printf("%.2f %c %.2f = %.2f",a, o, b, a/b);
    return a/b;
    break;
    default:
    printf("Invalid operator. Please choose a valid operator from '+', '-', '*', or '/'");
    return 1;
    }
}