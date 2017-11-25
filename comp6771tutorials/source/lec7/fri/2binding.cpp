#include <iostream>
#include <string>
#include <utility>


void f(std::string& s) {
  std::cout << s << " is a lvalue" << '\n';
}

void f(const std::string& s) {
  std::cout << s << " is a const lvalue" << '\n';
}

void f(std::string&& s) {
  std::cout << s << " is a rvalue" << '\n';
}

void f(const std::string&& s) {
  std::cout << s << " is a const rvalue" << '\n';
}

template <typename T>
void forwarder(T&& val) {
  f(std::forward<T>(val));
}

int main() {
  f("rvalue");
  forwarder("rvalue");
  std::cout << '\n';

  // NOTE: this is almost always a bad idea using a const rvalue reference
  f(static_cast<const std::string&&>("const rvalue"));
  forwarder(static_cast<const std::string&&>("const rvalue"));
  std::cout << '\n';
  
  std::string l{"lvalue"};
  f(l);
  forwarder(l);
  std::cout << '\n';

  const std::string cl{"const lvalue"};
  f(cl);
  forwarder(cl);

 // using str = std::string;
  std::string s1 = "hello";
  const std::string sc = "world";
  std::string s2 = std::move("hello");
  std::string s3 = std::move(static_cast<const std::string&&>("hello"));
  std::string s4 = std::move(sc);
}
/*
auto move((const std::string&) && s) {
  return static_cast<const std::string&&>(s);
}
*/


