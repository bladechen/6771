#include <iostream>
#include <limits>
using namespace std;
int main()
{
    char16_t a = 1;
    wchar_t b = 2;
    cout << sizeof (a) <<   " "  << sizeof (b) << endl;

    long c = 3;
    cout << "long: " <<sizeof(c) << endl;

    long double d = 4;
    cout << "long double: " <<sizeof(d) << endl;

    double e = 4;
    cout << "double: " <<sizeof(e) << endl;


    double f = 5;

    cout << "float: " << sizeof (f) << endl;


    std::cout << "double min: " << std::numeric_limits<long double>::min() << std::endl;
    std::cout << "double max: " << std::numeric_limits<long double>::max() << std::endl;

    return 0;
}
