// possible questions
// 1) Write move and copy constructors / assignment implementing value semantics, where a moved from vector contains no elements
// alternative) Write move and copy constructors / assignment implementing reference semantics using reference counting (2 marks for each assignment / constructor)

//  Remember: STL is not cheating --> use shared pointers
// 2) Fix this code so that it executes moves, not copies when reallocating (2 marks)

// 3) This code is not exception-safe
//     Remember: STL is not cheating --> Replace data with unique pointer to array
//  a) Write a test case where what it should output differs from what it does output (2 marks)
//  b) Fix the bug (2 marks)

// 4) Ensure that a vector<T> can only be instantiated if the T is copy-assignable and default-constructible. Hint: static_assert + type traits (3 marks)

#include <algorithm>
#include <iostream>
#include <memory>
#include <type_traits>

template <typename T>
class Vector {
  static_assert(std::is_default_constructible<T>(), "T must be default constructable");
  static_assert(std::is_copy_assignable<T>(), "T must be copy-assignable");
public:
  Vector(): data{} {}

  ~Vector () {
    delete[] data;
  }

  void push_back(const T& item) {
    if (sz == capacity) {
      auto new_capacity = (capacity == 0) ? 1 : (capacity * 2);

      auto next = new T[new_capacity];
      std::move(data, data + capacity, next);

      delete[] data;
      data = next;
      capacity = new_capacity;
    }
    data[sz++] = item;
  }

  unsigned size() const {
    return sz;
  }

  T& operator[](unsigned n) {
    return data[n];
  }

  const T& operator[](unsigned n) const {
    return data[n];
  }

  Vector(const Vector& other): data{new T[other.sz]{}}, sz{other.sz}, capacity{other.sz} {
    std::copy(other.data, other.data + sz, data);
  }

  Vector(Vector&& other): data{other.data}, sz{other.sz}, capacity{other.capacity} {
    other.data = nullptr;
    other.sz = 0;
    other.capacity = 0;
  }

private:
  T* data = nullptr;
  unsigned sz = 0;
  unsigned capacity = 0;
};


int main() {
  Vector<int> vec;
  for (auto i = 0; i < 20; ++i) {
    vec.push_back(i);
  }
  for (auto i = 0; i < 20; ++i) {
    std::cout << vec[i] << '\n';
  }

  // this compiles, but when I call push_back it fails
  /* Vector<std::unique_ptr<int>> upvec; */
  // upvec.push_back(std::unique_ptr<int>{});

  auto v2 = vec;
}
