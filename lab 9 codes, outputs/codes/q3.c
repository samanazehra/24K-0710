#include<stdio.h>
#include<string.h>
void AppendChar(char *s1, char *s2, int n);
int main()
{
    char destination_string[30];
    char source_string[20];
    int n;
    
    printf("Enter destination string:  ");
    fgets(destination_string,30,stdin);
    destination_string[strcspn(destination_string, "\n")] = 0;
    
    printf("Enter source string:  ");
    fgets(source_string,20,stdin);
    source_string[strcspn(source_string, "\n")] = 0;
    
    printf("Enter the number of characters you want to append. Make sure that they are equal to or lesser than the length of source string: ");
    scanf("%d",&n);
    AppendChar(destination_string, source_string, n);
    return 0;
}

void AppendChar(char *s1, char *s2, int n)
{
  int length=  strlen(s2);
  if (n<=length){
    printf("Your concatenated string is: '%s'",strncat(s1, s2, n));
  }
  else printf("Invalid n. n must be less than length of source string.");
  
}