#include <iostream>
struct AA{
    AA()
    {
        std::cout << "create" << std::endl;
    }
    ~AA()
    {
        std::cout << "destory" <<std::endl;
    }
    AA(const AA& )
    {
        std::cout << "copy construct" << std::endl;
    }
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
    AA&& a2 = AA{};

    std::cout << "out" <<std::endl;
}

int main() {
    A::X x;
    X xx;
    f(xx);
    f(x);// SAME as A::f(x)
    int i = 100;
    ++ i = 99;
    int j = ++ i;
    // i ++ = 100;
    std::string  str1 = "aa";
    std::string  str2 = std::move(str1);
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
    std::cout << i << std::endl;
    int aaa = static_cast<int>{5.3};
}
