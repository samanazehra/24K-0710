#include<stdio.h>
int main(){
    int a[3][3],saddlepoint=-1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("Enter element[%d][%d]= ",i+1,j+1);
            scanf("%d",&a[i][j]);
        }
    }
    printf("\nThe matrix is:\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<3;i++){
        int min=a[i][0],col_index=0;
        for(int j=1;j<3;j++){
            if(a[i][j]<min){
                min=a[i][j];
                col_index=j;
            }
        }
        int is_saddle_point=1;
        for(int k=0;k<3;k++){
            if(a[k][col_index]>min){
                is_saddle_point=0;
                break;
            }
        }
        if(is_saddle_point){
            printf("\nSaddle point found at a[%d][%d]= %d\n",i+1,col_index+1,min);
            saddlepoint=min;
            break;
        }
    }
    if(saddlepoint==-1){
        printf("\nNo saddle point found in the matrix.\n");
    }
    return 0;
}
