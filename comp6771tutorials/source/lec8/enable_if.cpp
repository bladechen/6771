#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <vector>

struct EuclideanVector {
  template <typename RandomIt>
  EuclideanVector(RandomIt begin, RandomIt end) {
    // requires is_arithmetic on the value_type of the iterator
    // this version will be optimised for a random access iterator
    // let's use static_assert
    std::cout << "Calling EuclideanVector(RandomIt, RandomIt) on " << (end - begin) << " elements\n";
  }

  /*
  template <typename It>
  EuclideanVector(It begin, It end) {
    auto dist = 0U;
    while (begin != end) {
      ++dist;
      ++begin;
    }
    std::cout << "Calling EuclideanVector(It, It) on " << dist << " elements\n";
  }
  */

  EuclideanVector(unsigned, double) {
    std::cout << "Calling EuclideanVector(unsigned, double)\n";
  }
};

template<typename T1, typename T2>
std::enable_if_t<std::is_same<T1, T2>::value, bool> check_type(const T1& t1, const T2& t2) {
  std::cout << "'" << t1 << "' and '" << t2 << "' ";
  std::cout << "are the same types." << std::endl;
  return true;
}

template<typename T1, typename T2>
std::enable_if_t<!std::is_same<T1, T2>::value, bool> check_type(const T1& t1, const T2& t2) {
  std::cout << "'" << t1 << "' and '" << t2 << "' ";
  std::cout << "are different types." << std::endl;
  return false;
}

int main() {
  check_type(1, 32);
  check_type(1, 3.01);
  check_type(3.01, std::string("Test"));

  std::vector<int> ivec;
  std::vector<double> dvec;
  std::vector<std::string> svec;

  std::list<int> ilist;
  std::list<double> dlist;
  std::list<std::string> slist;

  std::cout << "Should be unsigned, double\n";
  EuclideanVector(1, 3.0);
  EuclideanVector(1, 1);

  std::cout << "Should be RandomIt, RandomIt\n";
  EuclideanVector(ivec.begin(), ivec.end());
  EuclideanVector(dvec.begin(), dvec.end());
  EuclideanVector(svec.begin(), svec.end());

  /*
  std::cout << "Should be It, It\n";
  EuclideanVector(ilist.begin(), ilist.end());
  EuclideanVector(dlist.begin(), dlist.end());
  EuclideanVector(slist.begin(), slist.end());
  */

  return 0;
}
