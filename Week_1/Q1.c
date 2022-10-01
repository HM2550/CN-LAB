#include<stdio.h>

void swap (int *a, int *b)  
{  
    int temp;   
    temp = *a;  
    *a = *b;  
    *b = temp;  
} 

int main()  
{  
    int a, b;
    
    printf("Enter two integers:\n");
    scanf("%d %d",&a, &b); 

    printf("Before swapping the values a = %d, b = %d\n",a,b); 
    swap(&a, &b);  
    printf("After swapping values a = %d, b = %d\n",a,b); 

    return 0;
}  
 