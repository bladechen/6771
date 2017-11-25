#include <algorithm>
#include <iostream>
#include <vector>

// TODO: explain combining of templates and inheritance
template <typename T>
class Stack {
public:
  virtual ~Stack() = default;
  virtual bool push(const T& item) = 0;
  virtual void pop() = 0;
  virtual T& top() = 0;
  virtual const T& top() const = 0;
  virtual bool empty() = 0;
  virtual bool full() = 0;
  virtual void clear() = 0;

  void assign(Stack<T>& other) {
    clear();
    std::vector<T> contents;
    while (!other.empty()) {
      contents.push_back(other.top());
      other.pop();
    }
    for (auto val = contents.rbegin(); val != contents.rend(); ++val) {
      other.push(*val);
      push(*val);
    }
  }
};

template <typename T>
class UBStack: public Stack<T> {
public:
  bool push(const T& item) override {
    s.push_back(item);
    return true;
  }
  void pop() override { s.pop_back(); }
  T& top() override { return s.back(); }
  void clear() override { s.clear(); }
  const T& top() const override { return s.back(); }
  bool empty() override { return s.empty(); }
  bool full() override { return false; }
private:
  std::vector<T> s;
};

template <typename T>
class BStack: public Stack<T> {
public:
  BStack(unsigned bound) {
    s.reserve(bound);
  }

  bool push(const T& item) override {
    if (full())
      return false;
    s.push_back(item);
    return true;
  }
  void pop() override { s.pop_back(); }
  T& top() override { return s.back(); }
  void clear() override { s.clear(); }
  const T& top() const override { return s.back(); }
  bool empty() override { return s.empty(); }
  bool full() override { return s.size() == s.capacity(); }
private:
  std::vector<T> s;
};

int main() {
  std::cout << std::boolalpha;

  const auto setup = [] (auto& s) {
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    std::cout << "top = " << s.top() << "\n";
    std::cout << "full: " << s.full() << '\n';
    s.push(6);
    std::cout << "top = " << s.top() << "\n";
    s.pop();
    std::cout << "top = " << s.top() << "\n";
    std::cout << "full: " << s.full() << '\n';
  };
  std::cout << "setting up bounded stack\n";
  BStack<int> bs(5);
  setup(bs);
  std::cout << "setting up unbounded stack\n";
  UBStack<int> ubs;
  setup(ubs);

  ubs.assign(bs);
}
