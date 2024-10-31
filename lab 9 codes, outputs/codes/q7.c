#include<stdio.h>
void CheckPrime(int n);
int main()
{
    int number;
    printf("Please enter your number:  ");
    scanf("%d",&number);
    CheckPrime(number);
    return 0;
}
void CheckPrime(int n)
{
    int prime=1;
    if (n<=1){
        prime=0;
    }
    for (int i=2; i<=n/2; i++){
        if (n%i==0){
            prime=0;
            break;
        }
    }if (prime) printf("%d is a prime number",n);
    else printf("%d is not a prime number",n);
}