#include<stdio.h>
#include<stdlib.h>

struct employee_info
{
    char emp_name[100];
    int emp_age;
};

struct employee
{
    int empid;
    int base_salary;
    float da;
    float hra;
    float gross_salary;
    struct employee_info info;
};

void input(struct employee *e)
{
    printf("\nEnter Employee name : ");
    fflush(stdin);
    gets(e->info.emp_name);

    printf("\nEnter Employee age : ");
    scanf("%d",&e->info.emp_age);

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
    // printf("Name : %s\nAge : %d\n",e->info.emp_name,e->info.emp_age);
    // printf("Employee ID : %d\n",e->empid);
    // printf("Basic Salary : %d\n",e->base_salary);
    // printf("HRA : %.2f \nDA : %.2f\n",e->hra,e->da);
    // printf("Gross Salary : %.2f\n",e->gross_salary);

    printf("\n\n%s\t%d\t%d\t\t%d\t\t%.2f\t%.2f\t%.2f",e->info.emp_name,e->info.emp_age,e->empid, e->base_salary,e->hra,e->da, e->gross_salary);
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
    printf("Name\tAge\tEmployee ID\tBasic Salary\tHRA\tDA\tGross Pay");
    for(int i=0;i<n;i++)
    {
        display(&e[i]);
        // printf("\n");
    }
}