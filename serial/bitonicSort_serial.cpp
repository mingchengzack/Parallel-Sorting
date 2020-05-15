#include <iostream>
#include <vector>

// Swap in the given direction
void compSwap(std::vector<int> &arr, int i, int j, bool dir) {
  bool isGreater = arr[i] > arr[j];
  if (dir == isGreater) {
    std::swap(arr[i], arr[j]);
  }
}

int greatestPowerOfTwoLessThan(int cnt) {
  int k = 1;
  while (k > 0 && k < cnt) {
    k <<= 1;
  }
  return k >> 1;
}

// Merge two sequences
void bitonicMerge(std::vector<int> &arr, int l, int cnt, bool dir) {
  if (cnt <= 1) {
    return;
  }

  int k = greatestPowerOfTwoLessThan(cnt);
  for (int i = l; i < l + cnt - k; i++) {
    compSwap(arr, i, i + k, dir);
  }

  bitonicMerge(arr, l, k, dir);
  bitonicMerge(arr, l + k, cnt - k, dir);
}

void bitonicSortHelper(std::vector<int> &arr, int l, int cnt, bool dir) {
  // Base case
  if (cnt <= 1) {
    return;
  }

  int k = cnt / 2;

  // Sort in ascending order
  bitonicSortHelper(arr, l, k, !dir);

  // Sort in descending order
  bitonicSortHelper(arr, l + k, cnt - k, dir);

  // Merge sequence in ascending order
  bitonicMerge(arr, l, cnt, dir);
}

void bitonicSort(std::vector<int> &arr) {
  bitonicSortHelper(arr, 0, arr.size(), true);
}

int main() {
  std::vector<int> arr{4, 2, 1, 100, 3, 9, 1000, 5, 7, -1, -2};
  bitonicSort(arr);
  for (unsigned i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << ",";
  }
  std::cout << std::endl;
}