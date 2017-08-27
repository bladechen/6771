
#include <iostream>
#include <cstddef>

using namespace std;

// private class for use by HasPtr only
class U_Ptr {
    friend class HasPtr;

    int *ip;
    size_t use;

    U_Ptr(int *p) : ip(p), use(1) { }
    ~U_Ptr() { delete ip; }
};


class HasPtr {
    public:
        // p must have been dynamically allocated
        HasPtr(int *p, int i) : ptr(new U_Ptr(p)), val(i) { std::cout << "default" <<std::endl;}

        // copy members and increment the use count
        HasPtr(const HasPtr &orig) : ptr(orig.ptr), val(orig.val) { ++ptr->use; std::cout << "copy" <<std::endl; }

        // assignment operator
        HasPtr& operator=(const HasPtr&);

        // if use count goes to zero, delete the U_Ptr object
        ~HasPtr() { if (--ptr->use == 0) delete ptr; std::cout << "delete" << std::endl; }

    private:
        U_Ptr *ptr;  // points to use-counted U_Ptr object
        int val;
};

// assignment operator
HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    // increment use count on rhs first
    ++rhs.ptr->use;

    // if use count goes to 0 on this object, delete it
    if (--ptr->use == 0)
        delete ptr;

    ptr = rhs.ptr;      // copy the U_Ptr object
    val = rhs.val;      // copy the int member

    return *this;       // return a reference to this
}

class A
{
    public:
    A(int ){}

    friend A operator +(const A& a, const A& b)
    {
        (void )a;
        (void )b;
        std::cout << "2" << std::endl;
        return A(10);
    }
    A operator +(const A& a)
    {
        (void) a;
        std::cout << "1" << std::endl;
        return A(5);
    }

    A& operator++()
    {
        a++;
        return *this;

    }
    int a = 0;

};

void foo(int &&a)
{
    (void) a;
    std::cout << "foo2\n";

}

void foo(int const &a)
{
    (void) a;
    std::cout << "foo1\n";

}
int main()
{
    HasPtr *a =  new HasPtr(new int(), 5);
    a= nullptr;
    std::cout << a << "end of main" <<  std::endl;
    A aa(5);
    A bb(5);

    A cc =  bb + aa;
    (void) cc;

    int dd = 100;
    int &v = dd;
    int v1 = v;
    v1 = 100000;
    std::cout << v1 << std::endl;

    A& ref = ++ aa;
    std::cout << aa.a << std::endl;

    ref.a ++;
    std::cout << aa.a << std::endl;
    std::cout <<ref.a << std::endl;

    foo(5);
    // int j = 0;
    // int&& jj = std::move(j);
    // int * p = &(420);

}
