#include<stdio.h>
int main(){
    int i,j,k,sum1=0,sum2=0;
    int matrix[3][3][2];
    for (i=0; i<3; i++){
         for (j=0; j<3; j++){
              for (k=0; k<2; k++){
                  printf("Enter element at [%d][%d][%d]= ",i+1,j+1,k+1);
                  scanf("%d",&matrix[i][j][k]);
              }
         }
    }
    for (i=0; i<3; i++){
         for (j=0; j<3; j++){
              sum1+=matrix[i][j][0];
              sum2+=matrix[i][j][1];
         }
    }
    printf("The sum of all the elements of page 1 of matrix is %d\n",sum1);
    printf("The sum of all the elements of page 2 of matrix is %d",sum2);
    return 0;
}