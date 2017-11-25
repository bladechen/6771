#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
  virtual double area() = 0;

  virtual ~Shape() = default;

  char r, g, b;
};

class Square: public Shape {
public:
  Square(double size): size{size} {}

  double area() {
    return size * size;
  }

  ~Square() {
    std::cout << "Destructing square\n";
  }

private:
  double size;
};

class Circle: public Shape {
public:
  Circle(double radius): radius{radius} {}

  virtual double area() override {
    return radius * radius * 3.14159;
  }

  ~Circle() {
    std::cout << "Destructing circle\n";
  };

private:
  double radius;
};

class Rectangle: public Shape {
public:
  Rectangle (double height, double width): height{height}, width{width} {}

  double area() override {
    return height * width;
  }

  ~Rectangle() {
    std::cout << "Destructing rectangle\n";
  }

private:
  double height;
  double width;
};

template <typename Base, typename Derived, typename... Args>
std::unique_ptr<Base> make_unique_base(Args&&... args) {
  return std::unique_ptr<Base>(std::make_unique<Derived>(std::forward<Args>(args)...).release());
}


int main() {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(make_unique_base<Shape, Circle>(10));
  shapes.push_back(make_unique_base<Shape, Square>(9));
  shapes.push_back(make_unique_base<Shape, Rectangle>(5, 7));

  for (const auto& shape : shapes) {
    std::cout << shape->area() << '\n';
  }
}
