#include <stdio.h>
#include<string.h>
void SearchWord (char a[6][15], char *s);
int main() {
    char array[6][15]={"camera","fan","apple","phone","kitten","discord"};
    char word[15];
    printf("Enter your word: ");
    fgets(word,15,stdin);
    word[strcspn(word, "\n")] = 0;
    SearchWord (array, word);
    return 0;
}
void SearchWord (char a[6][15], char *s)
{
    int found= 0;
    for (int i=0; i<6; i++){
        if (strcmp(a[i],s)==0){
            printf("Found");
            found= 1;
            break;
        }
    }if (!found) printf("Not found");
}