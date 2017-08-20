#include <iostream>
#include <vector>
struct AA{
    AA()
    {
        point=  new int{10};
        std::cout << "default construct " << this << std::endl;
    }
    ~AA()
    {
        std::cout << "default destruct" <<std::endl;
    }
    AA(const AA& )
    {
        std::cout << "copy construct" << std::endl;
    }
    AA(AA&& a)  //= default;
    {
        this->count  = a.count;
        this->point = a.point;
        std::cout <<"move construct" << std::endl;
    }
    AA& operator=(const AA&)
    {
        std::cout << "copy assign" << std::endl;
        return *this;
    }
    AA& operator=(AA&& ) //= default;
    {
        std::cout << "move assign" << std::endl;
        return *this;
    }
    AA& get_this()
    {
        return *this;
    }
    void dump()
    {
        std::cout << "--------------------" << std::endl;
        std::cout << point << std::endl;
        std::cout <<  str << std::endl;
        std::cout << count << std::endl << std::endl;
    }
    int* point{nullptr};
    std::string str="default";
    int  count = 2;

};
namespace A {
    struct X {};
    void f(const X&) {
        std::cout << "in" <<std::endl;
    }
}


struct X{};
void f(const X&) {

    // AA& a1 = AA{};
    // AA&& a2 = AA{};

    std::cout << "out" <<std::endl;
}

AA& test_AA()
{
    AA one;
    AA two;
    AA three;
    // three = one;
    three = std::move(two);
    AA four = std::move(one);
    one.dump();
    two.dump();
    three.dump();
    four.dump();

    std::string rtmp = "hello";
    std::string ss = "world";
    ss = std::move(rtmp);
    std::cout <<"first right:" << rtmp << std::endl;
    std::string ltmp = std::move(rtmp);
    // rtmp = std::move(ltmp);
    std::cout <<"second right:" << rtmp << std::endl;
    std::cout << "left: "<< ltmp << std::endl;
    std::cout << "ss: "<< ss << std::endl;


    const int&& tmp_int = 6;

    const int& tmp_int1 = 7;
    std::cout << &tmp_int << std::endl;
    std::cout << &tmp_int1 << std::endl;

    AA&& aa = AA{};
    const AA& aaa  = AA{};
    AA aaaa = AA{};

    std::cout << &aa << std::endl;
    std::cout << &aaa << std::endl;
    std::cout << &aaaa << std::endl;
    // tmp_int  = 111;
    std::cout << "one:" <<one.str << std::endl;
    return one.get_this();
}


int main() {
    // AA aa = AA();
    // std::vector<AA> vec;
    // vec.push_back(AA());
    // A::X x;
    // X xx;
    // f(xx);
    // f(x);// SAME as A::f(x)
    // int i = 100;
    // ++ i = 99;
    // int j = ++ i;
    // (void) j;
    // // i ++ = 100;
    // std::string  str1 = "aa";
    // std::string  str2 = std::move(str1);
    // std::cout << str1 << std::endl;
    // std::cout << str2 << std::endl;
    // std::cout << i << std::endl;
    //
    AA& a = test_AA();
    // std::cout << a.str << std::endl;
    int *p = new int();
    int * b  = std::move(p);
    std::cout << p << std::endl;
    std::cout << b << std::endl;

    // int aaa = static_cast<int>{5.3};
}
