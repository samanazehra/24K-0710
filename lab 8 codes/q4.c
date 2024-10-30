#include<stdio.h>
int main (){
    int first_number, last_number, prime=1;
    int i, n;
    printf("Enter the number you want to start your sequence with:  ");
    scanf("%d",&first_number);
    printf("Enter the number you want to end your sequence with:  ");
    scanf("%d",&last_number);
    if (first_number>last_number){
        printf("Invalid range. The starting number must be less than or equal to the ending number.\n");
        return 1;
    }for (n=first_number; n<=last_number; n++){
        if (n<=1)
        continue;
        prime=1;
        for (i=2; i<=n/2; i++){
            if (n%i==0){
                prime=0;
                break;
            }
        }if(prime)
         printf("%d, ",n);
    }
    return 0;
}