#include <stdio.h>

int main()
{
    const int &i = 1; // int
    auto j = i; // int

    j = 10;
    printf ("%d\n", j);

}
