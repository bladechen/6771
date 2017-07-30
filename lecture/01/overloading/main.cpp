#include <stdio.h>

void func(double a, double b)
{
    printf ("two\n");
}
void func(double a, int b)
{
    printf ("one double, one int\n");
}
void func(double a)
{
    printf ("one\n");
}

int main()
{
    func(9.0);
    return 0;
}

