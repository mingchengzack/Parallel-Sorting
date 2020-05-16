#include <omp.h>

#include <fstream>
#include <iostream>
#include <vector>

int partition(std::vector<int> &arr, int l, int r, int pivot) {
  int partitionIdx = l - 1;
  int pivotElement = arr[pivot];

  // Swap pivot to the right
  std::swap(arr[r], arr[pivot]);

  // Move elements that are smaller than pivot to left
  for (int i = l; i < r; i++) {
    if (arr[i] <= pivotElement) {
      std::swap(arr[i], arr[++partitionIdx]);
    }
  }

  // Swap pivot back
  std::swap(arr[r], arr[++partitionIdx]);

  return partitionIdx;
}

void quickSortHelper(std::vector<int> &arr, int l, int r) {
  // Base case
  if (l >= r) {
    return;
  }

  int pivot = l;
  int partitionIdx = partition(arr, l, r, pivot);

  quickSortHelper(arr, l, partitionIdx - 1);
  quickSortHelper(arr, partitionIdx + 1, r);
}

void quickSort(std::vector<int> &arr) {
  quickSortHelper(arr, 0, arr.size() - 1);
}

int main() {
  std::vector<int> arr;
  std::ifstream myfile("arrays/100000.txt");

  int e;
  while (myfile >> e) {
    arr.push_back(e);
  }

  double start = omp_get_wtime();
  quickSort(arr);
  double end = omp_get_wtime();
  double time = end - start;
  std::cout << "Time for execution: " << time * 1000 << " miliseconds."
            << std::endl;
  //for (unsigned i = 0; i < arr.size(); i++) {
    //std::cout << arr[i] << ",";
  //}
  //std::cout << std::endl;
}
