#include <cassert>
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
        int  i ;
        std::unique_ptr<MyType> next;
};

int main() {
    // ptr<A>*p = new ptr<A>(new A());
    // p->counter  = 10;
    my_smart_ptr<A> x(new A());
    my_smart_ptr<A> y = x;

    y = nullptr;
    x = NULL;
    x = NULL;

    auto p = std::make_unique<MyType>();
    p->next = std::move(p);
    int * leak_ptr = new int(1000);
    std::cout << *leak_ptr + 100 << std::endl;
    std::cout << "finish main!!!!\n";
}
