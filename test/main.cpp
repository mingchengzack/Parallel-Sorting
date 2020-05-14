#include <iostream>
#include <vector>

#include "mergeSort.hpp"

int main() {
  std::vector<int> arr{4, 2, 1, 100, 3, 9};
  mergeSort(arr);
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << ",";
  }
  std::cout << std::endl;
}