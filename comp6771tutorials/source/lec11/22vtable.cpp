#include <iostream>

class A {
public:
  virtual void f(unsigned n) { std::cout << "A::f(" << n << "u)\n"; }
  virtual void f(double n) { std::cout << "A::f(" << n << "f)\n"; }
  virtual void g() { std::cout << "A::g()\n"; }
  virtual ~A() { std::cout << "~A\n"; }
};

class B : public A {
public:
  using A::f;
  void f(unsigned n) override { std::cout << "B::f(" << n << "u)\n"; }
  virtual void h() { std::cout << "B::h()\n"; }
  virtual ~B() { std::cout << "~B\n"; }
};

class C : public B {
public:
  virtual void x() {
    std::cout << "C::x()\n";
  }
  ~C() { std::cout << "~C\n"; }
};


int main() {
  A aa;
  B bb;
  C cc;
  A& a = aa;
  A& b = bb;
  A& c = cc;
  aa.f(1U);
  aa.f(1.0);
  bb.f(1U);
  bb.f(1.0);
  cc.f(1U);
  cc.f(1.0);
  std::cout << '\n';
  a.f(1U);
  a.f(1.0);
  b.f(1U);
  b.f(1.0);
  c.f(1U);
  c.f(1.0);
  std::cout << '\n';

  A* aaa = new C;
  delete aaa;
  std::cout << '\n';
}
