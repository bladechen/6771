
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <iostream>
#include <vector>

struct LessThan7 : std::unary_function<int, bool>
{
    bool operator()(int i) const { return i < 7; }
};

class IsOdd : public std::unary_function<int, bool>
{
    public:
    bool operator () (int x) const
    {
        return x%2;
    }
};

class Book
{
    bool operator == (const Book& b)
    {
        return b.isbn == this->isbn;
    }
    int isbn;
};

typedef int Type;
Type initVal() {
    return 0;
}

class Exercise {
    public:
        typedef double Type;
        Type setVal(Type);
        Type initVal(){return 1000;};
    private:
        Type val;
};

Exercise::Type Exercise::setVal(Type parm) {
    val = parm + Exercise::initVal();
    return val;
}



typedef int my_type;

class X {
    public:
    typedef double my_type;
    my_type a;
};

class Y {
    X::my_type a;
    // typedef double my_type;
};

class MyBook {
public:
    MyBook(const std::string& bkTitle = "") : title(bkTitle) { }
    private:
    std::string title;
};
class Lib
{
public:
    Lib(MyBook book)
    {
        (void ) book;

    }

};


namespace A
{
  void f(int x) {};
}

namespace B
{
  struct S {};

  void f(S) {};

  void f(int, int) {};

  void test1() {
    using namespace A; // using DIRECTIVE
    f(1);       // ERROR  namespace A is not considered because
                // B contains two overloads for 'f'
    f(1,2);     // OK     B::f(int,int)
    f(B::S());  // OK     B::f(S)
  }
  void test2() {
    using A::f; // using DECLARATION
    f(1);       // OK     A::f(int)
    f(1,2);     // ERROR  A::f  hides  B::f(int,int)
    f(B::S());  // OK     B::f(S) due to ADL!
  }
}

namespace C {
  void test3() {
    using namespace A; // using DIRECTIVE
    f(1);       // OK     A::f(int)
    f(B::S());  // OK     B::f(S) due to ADL!
  }

  void test4() {
    using A::f; // using DECLARATION
    f(1);       // OK     A::f(int)
    f(B::S());  // OK     B::f(S) due to ADL!
  }
}
int main()
{
    std::vector<int> v(10);
    std::iota(begin(v), end(v), 0);

    std::cout << std::count_if(begin(v), end(v), std::not1(IsOdd())) << "\n";

    //same as above, but use a lambda function
    std::function<int(int)> less_than_9 = [](int x){ return x < 9; };
    std::cout << std::count_if(begin(v), end(v), std::not1(less_than_9)) << "\n";
    MyBook b( "dd;");
    Lib l(b);
    // Lib ll("fsdfs");
}
