#include "ndgrid.hpp"

#include <iostream>

template <typename T>
void test_grid(T& grid) {
  grid[2][1][2] = 0;
  grid[1][1][1] = 1;
  grid[0][1][2] = 2;

  std::cout << "outputting grid using indexes\n";
  for (auto i = 0U; i < grid.size(); ++i) {
    for (auto j = 0U; j < grid[0].size(); ++j) {
      for (auto k = 0U; k < grid[0][0].size(); ++k) {
        std::cout << grid[i][j][k] << " ";
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
  // This works, but it's pretty ugly. Let's try something better
  
 /* 
  std::cout << "outputting grid using range-for\n";
  for (const auto& box : grid) {
    for (const auto& row : box) {
      for (const auto& col : row) {
        std::cout << col << ' ';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
  */
/*
  std::cout << "resizing grid to 2x2x2\n";
  grid.resize(2);
  std::cout << "outputting 2x2x2 grid using range-for\n";
  for (const auto& box : grid) {
    for (const auto& row : box) {
      for (const auto& col : row) {
        std::cout << col << ' ';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
  */
}

int main() {
  NDGrid<int, 3> my3DGrid(4, 7);
  auto stl3DGrid = std::vector<std::vector<std::vector<int>>>(4, std::vector<std::vector<int>>(4, std::vector<int>(4, 7)));
  std::cout << "Testing STL grid\n";
  test_grid(my3DGrid);
  std::cout << "Testing custom grid\n";
  test_grid(stl3DGrid);

  return 0;
}
