#include <stdio.h>
#include <math.h>

double factorial(double num)
{
    if (num == 1 || num == 0)
    {
        return 1;
    }
    else
    {
        return num * factorial(num - 1);
    }
}

// 1
double function1(int power)
{
    power = (double)(power);
    return pow(1.5, power);
}

// 2
double function2(int number)
{
    number = (double)number;
    return pow(number, 3);
}

// 3
double function4(int number)
{
    number = (double)number;
    return log2(factorial(number));
}

// 4
int function21(int n)
{
    return n;
}

// 5
double function12(int n)
{
    n = (double)n;
    return pow(2, log2(n));
}

// 6
double function19(int n)
{
    n = (double)n;
    return log(log(n));
}

// 7
double function18(int n)
{
    n = (double)n;
    return sqrt(log(n));
}

// 8
double function15(double power)
{
    power = (double)(power);
    return exp(power);
}

// 9
double function20(int n)
{
    n = (double)n;
    return pow(2, sqrt(2 * log2(n)));
}

// 10
double function22(int n)
{
    n = (double)n;
    return pow(2, n);
}

// 11
double function10(int n)
{
    n = (double)n;
    return pow(n, (log2(log2(n))));
}

//12
double function24(int n){
    n = (double)n;
    return pow(2,pow(2,n+1));
}

//13
double function5(int n){
    n = (double)n;
    return pow(2,pow(2,n));
}

//14
double function23(int n){
    n = (double)n;
    return n * (log2(n));
}

//15
double function6(int n){
    n = (double)n;
    return pow(n,(1/log2(n)));
}

//16
double function9(int n){
    n = (double)n;
    return n * pow(2,n);
}
int main()
{
    printf("(3/2)^n\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function1(i));
    }
    printf("\n\nn^3\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function2(i));
    }
    printf("\n\nlog(n!)\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function4(i));
    }
    printf("\n\n2^2^(n+1)\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function24(i));
    }
    printf("\n\n2^lg(n)\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function12(i));
    }
    printf("\n\ne^n\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function15(i));
    }
    printf("\n\n2^2^n\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function5(i));
    }
    printf("\n\nn*(2^n)\n");//
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function9(i));
    }
    printf("\n\nn^(1/lgn)\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2lf\n", function6(i));
    }
    printf("\n\nn\n");
    for (int i = 0; i < 101; i++)
    {
        printf("%.2d\n", function21(i));
    }
    printf("\n\nn!\n");
    for(int i=0;i<21;i++){
        printf("%.2lf\n",factorial(i));
    }
    // printf("\n\n2^n\n");
    // for (int i = 0; i < 101; i++)
    // {
    //     printf("%.2lf\n", function22(i));
    // }
    return 0;
}