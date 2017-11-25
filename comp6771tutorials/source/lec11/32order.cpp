#include <iostream>
#include <string>

class Field {
public:
  Field(const std::string& name): name{name} {
    std::cout << "Constructed " << name << '\n';
  }

  ~Field() {
    std::cout << "Destructed " << name << '\n';
  }

private:
  std::string name;
};

struct X {
  X() {
    std::cout << "Constructed x\n";
    f();
  }
  ~X() {
    f();
    std::cout << "Destructed x\n";
  }

  virtual void f() { std::cout << "called x::f\n"; }

  Field a{"x::a"};
  Field b{"x::b"};
};

struct Y: X {
  Y() {
    std::cout << "Constructed y\n";
    f();
  }
  ~Y() {
    f();
    std::cout << "Destructed y\n";
  }

  virtual void f() { std::cout << "called y::f\n"; }

  Field a{"y::a"};
  Field c{"y::c"};
};

int main() {
  Y y;
  X& x = y;
  std::cout << '\n';
  x.f();
  std::cout << '\n';
}
