#include <iostream>
#include <vector>
#include <string>
struct Timer {
    Timer() {}
};

struct TimeKeeper {
    TimeKeeper(const Timer& t) {}
    TimeKeeper() {}
    TimeKeeper(int a) {}
    TimeKeeper(std::string) {}
    void printTest() { std::cout << "In TimeKeeper" << std::endl; }
};

struct MyClass
{
    MyClass(){};
    void printTest() { std::cout << "In TimeKeeper" << std::endl; }


};
Timer returnTimer()
{
    return Timer();
}
TimeKeeper tp(Timer())
{
    return TimeKeeper(1);
}

int add (int a, int b)
{
    std::cout << a+ b << std::endl;
    return a + b;
}
int print (int (int, int), int a, int b)
{
    add(a, b);
    std::cout << "print" << std::endl;

}

typedef int INT;
typedef int value_type;
class X
{
    public:
        X(const std::string&)
        {
        }

        typedef double value_type;
        value_type foo1(){};
    friend void f();
    // {
    //     std::cout << "f func" << std::endl;
    //     return ;
    // }
    const X& r() const
    {
        return *this;
    }

    const X& r()
    {
        return *this;
    }
    // int func()
    // {
    // }
    // void func()
    // {
    // }
    static int counter;

};
int global = 1;
int X::counter = 0;
void f()
{
    INT a = 0;
    global ++;
    typedef double INT;
    INT b = 10.01;
    std::cout << global << std::endl;
    std::cout << "f out func" << std::endl;
    double global = 10.0010;
    std::cout << global << std::endl;
    std::cout << b << std::endl;
    // float global = 1;;
    return ;

}
void g(X x)
{
}

class MyString {
    public:
        MyString(const char* s) : str{s} {std::cout << "char " << std::endl;}
        MyString& operator = (const MyString &rhs)
        {
            std::cout << "=====" << std::endl;
            this->str = rhs.str;
            return *this;
        }
        // MyString(const MyString &rhs) : str{rhs.str} {std::cout << "MyString" << std::endl;}
        std::string str;
};


class Y {   // OK, but slightly messier solution
public:
    int get_val(int y) const
    {
        x->foo1();
        // auto p = cache->find(x);
        // if (p.first) return p.second;
        // int val = compute(x);
        // cache->set(x, val);
        return y;
    }
    // explicit Y(const char* );
    Y(const std::string& ){};
    Y()
    {
    x= new X("");}
    // ...
    //
private:
    X *x;

    // unique_ptr<Cache> cache;
};

// Y::Y(const char* )
// {}
void y_func(Y y)
{
}

class A
{
    public:
    A(int){}
};
class B
{
    public:
        B(A a){}

explicit         B(const std::string& ){};
};
int main() {
    X::counter ++;
    // TimeKeeper time_keeper(string);
    TimeKeeper time_keeper{Timer()};
    time_keeper.printTest();
    MyClass c{};
    c.printTest();
    TimeKeeper t = tp(returnTimer);
    t.printTest();

    Timer tt();
    std::cout << tt << std::endl;
    print(add, 2, 4);
    // g("123");
    // X x("123");
    f();
    int *a =  new int(11);
    delete a;
    std::cout << *a << std::endl;
    MyString s2 = MyString("abc");
    MyString s3 = s2;
    std::cout << s3.str << std::endl;
    const X* xxx=  new X("");
    // y_func("hello");
    Y y("1");
    // Y yy = "ooo";
    A aa(23);
    B b = aa;
    B bb("hello");
    std::string tmp_str = "hl";
    // B b1 = tmp_str;
    B b2(tmp_str);
    std::vector<int > v(10);
    std::vector<int > v1{10};

    std::cout << v.size() << std::endl;
    std::cout << v1.size() << std::endl;
    std::vector<double> v2(10);
    std::vector<double> v3{10};
    std::cout << v2.size() << std::endl;
    std::cout << v3.size() << std::endl;


    // B b1 = "11";
    // xxx->foo1();
    // x.f();
}
