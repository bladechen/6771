#include <iostream>
using namespace std;
int main()
{
    char16_t a = 1;
    wchar_t b = 2;
    cout << sizeof (a) <<   " "  << sizeof (b) << endl;
    return 0;
}
