#include<stdio.h>
#include<string.h>
int Sorting(int *s, int length);
int main()
{
    int size;
    printf("Enter size of array: ");
    scanf("%d",&size);
    int array[size];
    for (int i=0; i<size; i++){
        printf("Enter element %d = ",i+1);
        scanf("%d",&array[i]);
    }
    Sorting(array, size);
    return 0;
}
int Sorting(int *s, int length)
{
    int temp;
    for (int i=1; i<length; i++){
        for (int j=0; j<length-i; j++){
            if(s[j]>s[j+1]){
                temp= s[j];
                s[j]= s[j+1];
                s[j+1]= temp;
            }
        }
    }
    printf("Minimum is %d", s[0]);
    printf("\nMaximum is %d", s[length-1]);
    int e1=s[0];
    int e2=s[length-1];
    int e[]={e1,e2};
    return *e;
    }
        