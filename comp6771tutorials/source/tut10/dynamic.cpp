#include <iostream>

class B {
public:
  virtual void f() { 
    std::cout << "B "; 
  }
  int b;
};

class D : public B {
public:
  void f() override { 
    std::cout << "D "; 
  }
};

int main() {
  B b_con;
  B* b = &b_con;
  D d;
  b = &d;
  B &pb = *b;
  b->f();
  pb.f();
}
