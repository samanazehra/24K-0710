#include<stdio.h>
#include<string.h>
void ReverseString(char *s);
int main()
{
    char string[50];
    printf("Enter your string: ");
    fgets(string,50,stdin);
    ReverseString(string);
    return 0;
}
void ReverseString(char *s)
{
    s[strcspn(s, "\n")]=0;
    printf("Original string: '%s'\n",s);
    int length = strlen(s);
    printf("Reversed string: '");
    for (int i=length-1; i>=0; i--){
    printf("%c",s[i]);
    }printf("'");
}