#include <iostream>
#include <memory>
#include <string>

class Base {
public:
  const std::string& getI() const { return i; }
private:
  std::string i;
};

class Derived : public Base {
public:
  void foo(Derived &o) {
    j = o.getI() + ' ' + o.j;
  }
private:
  std::string j;
};

class Field {
  Field() { std::cout << "Constructed field\n"; }
  ~Field() { std::cout << "destructed field\n"; }
};

class A {
public:
  virtual void f(int) {}
  virtual int g() { return 1; }
  void a() {}
  virtual ~A() {}
};

class B : public A {
public:
  virtual void f(int) {}
  virtual int h() { return 1; }
};

class C : public B {
public:
  virtual void f(int, int) {}
  virtual void x() {}
  static void b() {}
};

int main() {
  A* a = new C{};
  delete a;
}
