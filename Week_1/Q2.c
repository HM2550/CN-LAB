#include<stdio.h>
#include<stdlib.h>

void main(int argc, char * argv[]) 
{
    int j, sum = 0;
   
    if (argc != 3) 
    {
        printf("Input .");
        exit(1);
    }

    printf("The sum is : ");
    for (j = 1; j < argc; j++)
        sum = sum + atoi(argv[j]);
    printf("%d", sum);
}
 