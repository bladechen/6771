#include <iostream>
using namespace std;
namespace X
{
    int i;
    int j;
    int k;
};
int k;

// void f(int a, int a)
// {
//     cout << a << endl;
// }
namespace Y
{
    int i;
};

int main()
{
    int i = 0;
    using namespace X;
    using namespace Y;
    i ++;
    using X::k;
    k++;
    // X::oo = 1;
    // f(1, 100);
    // X::fuck;
    // k ++;
    return 0;
}
