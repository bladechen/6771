#pragma once

#include <cstddef>
#include <utility>
#include <vector>

template <typename T, size_t N>
class NDGrid {
public:
  explicit NDGrid(size_t size, T&&);

  NDGrid<T, N-1>& operator[](size_t x);
  const NDGrid<T, N-1>& operator[](size_t x) const;

  void resize(size_t newSize);
  size_t size() const { return mElems.size(); }

private:
  std::vector<NDGrid<T, N-1>> mElems;
};

template <typename T>
class NDGrid<T, 1> {
public:
  explicit NDGrid(size_t size, T&& value);

  T& operator[](size_t x);
  const T& operator[](size_t x) const;

  void resize(size_t newSize);
  size_t size() const { return mElems.size(); }

private:
  std::vector<T> mElems;
};

// TODO: write this
template <typename T, size_t N>
NDGrid<T, N>::NDGrid(size_t, T&&) {}

template <typename T, size_t N>
NDGrid<T, N-1>& NDGrid<T, N>::operator[](size_t x) {
  return mElems[x];
}

template <typename T, size_t N>
const NDGrid<T, N-1>& NDGrid<T, N>::operator[](size_t x) const {
  return mElems[x];
}

////////////////////////


template <typename T>
T& NDGrid<T, 1>::operator[](size_t x) {
  return mElems[x];
}

template <typename T>
const T& NDGrid<T, 1>::operator[](size_t x) const {
  return mElems[x];
}

