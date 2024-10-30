#include <stdio.h>
int main() {
    int rows,i,j,k;
    printf("Enter the number of rows for the upper half of the diamond: ");
    scanf("%d",&rows);
    for(i=1;i<=rows;i++){
        for(j=1;j<=rows-i;j++){
            printf(" ");
        }
        for(k=1;k<=(2*i-1);k++) {
            printf("*");
        }
        printf("\n");
    }
    for(i=rows-1;i>=1;i--) {
        for(j=1;j<=rows-i;j++) {
            printf(" ");
        }
        for(k=1;k<=(2*i-1);k++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
