#include <cassert>
#include <cstring>
#include <vector>
#include <time.h>
#include <memory>
#include <iostream>
class PointPtr;

class Point {
    public:
        friend class PointPtr;
        static PointPtr create();
        static PointPtr create(int i, int j);
    private:
        Point() : count_(0) { i = j = 0; }
        Point(int i, int j) : count_(0) {
            this->i = i; this->j = j;
        }
        unsigned count_;
        int i, j;
};

class PointPtr { // smart pointer
    public:
        Point* operator-> () { return p_; }
        Point& operator* () { return *p_; }
        PointPtr(Point* p) : p_{p} { ++p_->count_; } // p cannot be NULL
        ~PointPtr() { if (--p_->count_ == 0) delete p_; }
        PointPtr(const PointPtr& p) : p_{p.p_} { ++p_->count_; }
        PointPtr& operator= (const PointPtr& p) {
            ++p.p_->count_;
            if (--p_->count_ == 0) delete p_;
            p_ = p.p_;
            return *this;
        }
    private:
        Point* p_; // p_ is never NULL
};
inline PointPtr Point::create() { return new Point(); }
inline PointPtr Point::create(int i, int j) {
    return new Point(i,j);
}


template <typename T>
class my_smart_ptr;

template <typename T>
class ptr
{
    friend class my_smart_ptr<T>;
    private:
        // ptr() : counter(0) { i = j = 0; }
        ptr(T* t) : counter(1), _obj { t} {
            std::cout << "create ptr" << std::endl;
        }
        ~ptr()
        {
            std::cout << "free ptr" << std::endl;
            assert(counter == 0);
            delete _obj;
        }
        int counter{0};
        T* _obj = nullptr;
    // friend <typename T> class my_smart_ptr;
    // private:

};
template <typename T>
class my_smart_ptr
{
    public:
    T* operator-> () { return p_->_obj; }
    T& operator* () { return *(p_->_obj); }
    my_smart_ptr(T* p)
    {
        std::cout << "create my_smart_ptr" << std::endl;
        p_ = new ptr<T>(p);
    }
    ~my_smart_ptr() {  if (p_!= NULL && --p_->counter == 0) delete p_; std::cout << "destroy my_smart_ptr" << std::endl;}
    my_smart_ptr(const my_smart_ptr& p) : p_{p.p_} { ++p_->counter; std::cout << "create my_smart_ptr" << std::endl;}
    my_smart_ptr& operator= (const my_smart_ptr& p) {
        ++p.p_->counter;
        if (--p_->counter == 0) delete p_;
        p_ = p.p_;
        return *this;
    }

    my_smart_ptr& operator= (my_smart_ptr* p) {
        if (p == NULL)
        {
            std::cout << "equal null , delete p\n" ;
            if (p_ != NULL)
            {
                if (--p_->counter == 0)
                    delete p_;
                p_ = nullptr;
            }
            return * this;
        }

        ++p->p_->counter;
        if (--p_->counter == 0) delete p_;
        p_ = p->p_;
        return *this;
    }
    // TODO nullptr
    private:
    ptr<T>* p_; // p_ is never NULL


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


};


class MyType
{
    public:
        MyType()
        {
            std::cout << "create MyType\n";
        }
        ~MyType()
        {
            std::cout << "free MyType\n";
        }
        int  i {100};
        // std::unique_ptr<MyType> next;
};

void func(std::unique_ptr<MyType> p)
{
    std::cout << "func uniq: " <<  std::endl;
    (void)p;
}



void func(std::shared_ptr<MyType> p)
{
    std::cout << "func share: " <<  std::endl;
    (void)p;
}
// void func1()
// {
//     std::cout << "func1: " <<  std::endl;
//     (void)p;
// }


std::vector<MyType> g_v;
void test_vec()
{
    MyType a;
    std::cout << "test_vec addr: " << &a << std::endl;
    g_v.push_back(a);
    g_v.emplace_back(std::move(a));
}

auto test_lambda()
{
    int b = 10;
    auto foo = [b] (void){
        // b = g_v.size() * 10 + 9;
        std::cout << "i am " << b << std::endl;
    };
    foo();
    return foo;
}





void clear_stack()
{
    char buf[1000];
    memset(buf, 0, sizeof (buf));
    std::cout << buf[10] << std::endl;

}
int main() {
    // ptr<A>*p = new ptr<A>(new A());
    // p->counter  = 10;
    my_smart_ptr<A> x(new A());
    my_smart_ptr<A> y = x;

    y = nullptr;
    x = NULL;
    x = NULL;

    // auto p = std::make_unique<MyType>();
    //
    //
    // p.reset(p.release());
    //
    // auto ui = std::make_unique<MyType>();
    // func(std::move(ui));
    // // p->next = std::move(p);
    // // int * leak_ptr = new int(time(NULL));
    // // std::cout << *leak_ptr + 100 << std::endl;
    // std::shared_ptr<int> xs = std::make_shared<int>(1);
    // std::weak_ptr<int> wp = xs;
    // xs = NULL;
    // // xs.reset();
    // auto xs1 = wp.lock();
    // std::cout << wp.lock() << std::endl;
    // std::cout << xs1 << std::endl;


    {
        std::weak_ptr<MyType> weak ;
        {
            auto p1 = std::make_shared<MyType>();
            // auto p2 = std::make_shared<MyType>();

            std::shared_ptr<MyType> p2(new MyType());
            weak = p1;
            std::cout << "p1 goes out of scope" << std::endl;
        }
        std::cout << "wk goes out of scope" << std::endl;
    }
     // p1 = NULL;
     // p2 = NULL;
     // std::weak_ptr<int> weak =
     //


    std::cout<< " calling func" << std::endl;
    func(std::unique_ptr<MyType>(new MyType()));
    std::cout<< " end func" << std::endl;

    std::shared_ptr<MyType> p = std::make_shared<MyType>();
    func(std::move(p));


    test_vec();
    std::cout << g_v.size() << "\n";
    std::cout << "test_vec addr: " << &(g_v[0]) << std::endl;


    auto fff = test_lambda();
    // clear_stack();
    fff();
    std::cout << "finish main!!!!\n";

}
