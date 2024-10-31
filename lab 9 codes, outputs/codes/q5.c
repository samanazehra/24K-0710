#include <stdio.h>
#include<string.h>
int main() 
{
    char s[5][20];
    char r[5][20];
    for (int i=0; i<5; i++){
        printf("Enter word %d: ",i+1);
        scanf("%s",s[i]);
        strcpy(r[i],s[i]);
    }
        for (int i=0; i<5; i++){
        int length= strlen(r[i]);
        int middle= length/2;
            for (int j=0; j<middle; j++){
            char temp= r[i][j];
            r[i][j]=r[i][length-j-1];
            r[i][length-j-1]=temp;
        }
        printf("Reversed word %d:\n%s\n",i+1,r[i]);
    }
        for (int i=0; i<5; i++){
            int palindrome = 0;
            if ((strcmp(r[i],s[i])==0))
            palindrome = 1;
            if(palindrome) printf("%s is a palindrome\n",s[i]);
            else printf("%s is not a palindrome\n",s[i]);
        }
        
    return 0;
}