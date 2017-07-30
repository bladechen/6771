#include <stdio.h>

int main()
{
    const int &i = 1; // int
    auto j = i; // int

    i= 100;
    j = 10;

}
