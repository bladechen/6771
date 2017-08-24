#include <stdio.h>
#include <iostream>
#include <string.h>
void func(int&& i)
{
    printf ("%d\n", i);
}

void process_value(int& i) {

    std::cout << "LValue processed: " << i << std::endl;
    i = 100000;
}

void process_value(int&& i) {
    std::cout << "RValue processed: " << i << std::endl;
}

void forward_value(int&& i) {
    process_value(i);
    std::cout << i << std::endl;
}

int main() {
    int a = 0;
    process_value(a);
    process_value(1);
    forward_value(2);
}
// int main()
// {
//     int&& a = 10;
//     int b = 100;
//     func(std::move(a));
//     func(100);
//     func(b);
// }
