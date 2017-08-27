#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
double r5to10(int in)
{
    return (in <= 4);
}



template <typename A, A a, A b>
class Range1
{
    public:
        bool operator() (const A& in)
    {
        return (a <= in && in <= b);

    }

};

class Range
{
    public:
        bool operator () (int val)
        {
            return val >= 100;
        }

};

template <typename A>
class Range2
{
    public:
        int a, b;
        Range2(int _a, int _b)
        {
            a = _a;
            b = _b;
        }
        bool operator() (const A& in)
    {
        return (a <= in && in <= b);

    }

};

template <typename T>
bool my_cmp(T a, T b)
{
    return a < b;
}

void f(int a, int b, int c) {
    std::cout << a << " " << b << " " << c << std::endl;
}
class IsOdd : public std::unary_function<int, bool>
{
    public:
    bool operator () (int x) const
    {
        return x%2;
    }
};
class A
{

    public:
        A()
        {
            std::cout << "create A" << std::endl;
        }
        ~A()
        {
            std::cout << "destroy A" << std::endl;
        }
    virtual int o(int x) const
    {
        std::cout << "in A" << std::endl;
        return x;
    }

};
class B: public A
{
    virtual int o(int x) const
    {
        std::cout << "in B" << std::endl;
        return x;
    }

};

int call_with_func(int(*func)(int ), int a)
{
    return func(a);
}

A bbb;
int main()
{
    const A& a = A();
    a.o(100);
    // std::vector<int> vec{ 20, 2, 4, 3, 8, 10, 15, 1};
    // std::vector<int> vec1 = vec;
    // std::cout << (vec.end() != std::find_if(vec.begin(), vec.end(), [] (int a){return  a> 100;})) << std::endl;
    // std::cout << (vec.end() != std::find_if(vec.begin(), vec.end(), r5to10)) << std::endl;
    // std::cout << (vec.end() != std::find_if(vec.begin(), vec.end(), Range())) << std::endl;
    // std::cout << ( std::count_if(vec.begin(), vec.end(), Range1<int, 5 ,10>{})) << std::endl;
    // std::cout << ( std::count_if(vec.begin(), vec.end(), Range2<int>{5, 10})) << std::endl;
    //
    // std::sort(vec1.begin(), vec1.end(), my_cmp<int>);
    // std::cout << vec1[0] << std::endl;
    // std::cout << my_cmp(1, int(1.1)) << std::endl;
    //
    //
    // auto g1 = std::bind(f, 10, 20 , std::placeholders::_1);
    // g1(10000);
    //
    //
    // int values[] = {1,2,3,4,5};
    // int cx = std::count_if (values, values+5, std::not1(IsOdd()));
    // std::cout << cx << " elements with even values." << std::endl;
    //
    // A *a  =  new B();
    // a->o(100);
    //
    // auto presult = std::find_if(vec.begin(), vec.end(),
    //                             [] (int val) { return 5 <= val && val <= 10; }
    //                            );
    // (void) presult;
    // auto temp_func = [](void){std::cout << "hello world\n" << std::endl;};
    // temp_func();
    // auto f = [ ] { return 10; };
    // std::cout << f() << std::endl;
    //
    // int key = 1000;
    // auto my_func =[key](int a) -> int {
    //     if (key > a)
    //     {
    //         return a;
    //     }
    //     else
    //     {
    //         return key;
    //     }
    // };
    // std::cout << my_func(100) << std::endl;
    //
    // // std::cout << call_with_func(my_func, 200) << std::endl;
    //
    // int v1= 1;
    // std::cout << v1 << std::endl;
    // auto f1 = [&v1] { v1 = 1000;return v1; };
    // f1();
    // std::cout << v1 << std::endl;
    // int&& v2 = std::move(v1);
    // std::cout << v1 << std::endl;
    // std::cout << v2 << std::endl;
    // v1 = 1000000;
    //
    // std::cout << v1 << std::endl;
    // std::cout << v2 << std::endl;
    // // using namespace std;
    // //     string &&s2 = string("xyz");
    // //     std::cout << s2 << std::endl;
    // //     const string &s1 = "xyz";
    // //     //string &s2 = string("xyz");
    // //     string &&s3 = string("abc") + string("xyz");
    // //     string s4("abc");
    // //     string &&s5 = std::move(s4);
    // //     string &&s6 = s5;
    // //     string &s7 = s5;
    // //     string * &&p1 = new string("abc");
    // //     string * const &p2 = new string("abc");
    // //     string * &p3 = new string("abc");
    //
    //

    return 0;
}

