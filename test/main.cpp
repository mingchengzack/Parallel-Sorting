#include <iostream>
#include <vector>

#include "bitonicSort.hpp"
#include "mergeSort.hpp"
#include "quickSort.hpp"

int main() {
  std::vector<int> arr{4, 2, 1, 100, 3, 9, 1000, 5, 7, -1, -2};
  mergeSort(arr);
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << ",";
  }
  std::cout << std::endl;
}