#pragma once

#include <iterator>

template <typename T, typename U>
class Library;

template <typename T, typename U>
class LibraryItemIterator;

template <typename T, typename U>
bool operator==(const LibraryItemIterator<T, U>& lhs, const LibraryItemIterator<T, U>& rhs);

template <typename T, typename U>
class LibraryItemIterator {
  using cont_it = typename std::vector<typename Library<T, U>::ItemContainer>::iterator;
public:
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  reference operator*() const {
    return it->getItem();
  }
  pointer operator->() const { return &(operator*()); }
  LibraryItemIterator& operator++() {
    ++it;
    return *this;
  }

  LibraryItemIterator(const cont_it& it): it{it} {}
private:
  cont_it it;

  friend bool operator==<>(const LibraryItemIterator<T, U>& lhs, const LibraryItemIterator<T, U>& rhs);
};

template <typename T, typename U>
bool operator==(const LibraryItemIterator<T, U>& lhs, const LibraryItemIterator<T, U>& rhs) {
  return lhs.it == rhs.it;
}

template <typename T, typename U>
bool operator!=(const LibraryItemIterator<T, U>& lhs, const LibraryItemIterator<T, U>& rhs) { return !(lhs == rhs); }
