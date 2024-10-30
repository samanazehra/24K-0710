#include<stdio.h>
int main(){
    int a[3][3], b[3][3], multiple[3][3];
    printf("Matrix A: \n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("Enter element[%d][%d]= ",i+1,j+1);
            scanf("%d",&a[i][j]);
        }
    }printf("\nMatrix B: \n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("Enter element[%d][%d]= ",i+1,j+1);
            scanf("%d",&b[i][j]);
        }
    }for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            multiple[i][j]=0;
        }
    }for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            for (int k=0; k<3; k++){
                multiple[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    printf("\nMatrix A is:\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("\nMatrix B is:\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    printf("\nMatrix A*B is:\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",multiple[i][j]);
        }
        printf("\n");
    }
    return 0;
}