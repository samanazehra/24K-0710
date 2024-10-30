#include<stdio.h>
int main(){
    int rows, columns;
    printf("Please enter the number of rows in your matrix:  ");
    scanf("%d",&rows);
    printf("Please enter the number of columns in your matrix:  ");
    scanf("%d",&columns);
    int matrix[rows][columns];
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
         printf("Enter element at [%d][%d]: ",i+1,j+1);
         scanf("%d",&matrix[i][j]);
        }
    }printf("Original Matrix= \n");
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            printf("[%d]",matrix[i][j]);
        }printf("\n");
    }printf("\nTranspose of Matrix= \n");   
    for (int i=0; i<columns; i++){
        for (int j=0; j<rows; j++){
            printf("[%d]",matrix[j][i]);
        }printf("\n");
    }return 0;
}