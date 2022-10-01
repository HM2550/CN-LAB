#include<stdio.h>
#include<stdlib.h>

struct employee
{
    int empid;
    int base_salary;
    float da;
    float hra;
    float gross_salary;
};

void input(struct employee *e)
{
    printf("\nEnter Employee ID : ");
    scanf("%d",&e->empid);

    printf("\nEnter basic salary : ");
    scanf("%d",&e->base_salary);
    
    e->da=0.05*(e->base_salary);
    e->hra=0.05*(e->base_salary);
    e->gross_salary=e->hra+e->da+e->base_salary;
}

void display(struct employee *e)
{
    printf("Employee ID : %d\n",e->empid);
    printf("Basic Salary : %d\n",e->base_salary);
    printf("HRA : %.2f \nDA : %.2f\n",e->hra,e->da);
    printf("Gross Salary : %.2f\n",e->gross_salary);
}

int main()
{
    int n=3;

    struct employee *e=(struct employee*)(malloc(sizeof(struct employee)*n));
    
    for(int i=0;i<n;i++)
    {
        printf("\nEnter details of Employee %d :\n",i+1);
        input(&e[i]);
    }

    printf("\n********Employee Details*********\n\n");
    for(int i=0;i<n;i++)
    {
        display(&e[i]);
        printf("\n");
    }
}