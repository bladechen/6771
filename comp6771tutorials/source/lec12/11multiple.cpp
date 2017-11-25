#include <iostream>

class Boat {
public:
  void dropAnchor() { anchorDropped = true; }
  virtual void drive() { std::cout << "boat driving\n"; }
private:
  bool anchorDropped = false;
};

class Car {
public:
  void openSunroof() { sunroofOpen = true; }
  virtual void drive() { std::cout << "car driving\n"; }
private:
  bool sunroofOpen = false;
};

class Amphibian: public Boat, public Car {
public:
};

int main() {
  Amphibian a;
  a.openSunroof();
  a.dropAnchor();
  a.Car::drive();
}
