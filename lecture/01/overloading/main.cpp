#include <stdio.h>

void func(double a, double b)
{
    (void)a;
    (void)b;
    printf ("two\n");
}
void func(double a, int b)
{
    (void)a;
    (void)b;

    printf ("one double, one int\n");
}
void func(double a)
{
    (void)a;

    printf ("one\n");
}

int main()
{
    func(9.0);
    return 0;
}

