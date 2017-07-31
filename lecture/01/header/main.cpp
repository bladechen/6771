#include "my_header.h"
#include <stdio.h>
extern void my_func();
int main_global = 0;
int main()
{
    const char* cc = "hello";
    printf ("%d\n", a);
    my_func();
    // cc[0] = 'b';
    cc = NULL;
    printf ("%s\n", cc);

    int i = 5;
    const int* co = & i;
    const int* const co1 = &i;
    printf ("co: %d\n", *co);



    *(int *) co = 100;

    printf ("co: %d\n", *co);

    printf ("co1: %d\n", *co1);


    // char *const cp1 = cc;
    // const char* const cp2 = cc;

    // const int ii = 6;
    // int &i1 = ii;

    const int &it = i;

    int& i2 = i;

    printf ("%p %p %p\n", (void*)&i, (void*)&it, (void*)&i2);

    const int &iii = 1;
    auto j = iii;
    j = 100;
    printf ("%d %d\n", iii, j);

}
