#include <iostream>
#include <vector>

void merge(std::vector<int> &arr, int l, int r, int m) {
  int n1 = m - l + 1;
  int n2 = r - m;
  std::vector<int> L(n1, 0), R(n2, 0);

  // Copy left array
  for (int i = 0; i < n1; i++) {
    L[i] = arr[i + l];
  }

  // Copy right array
  for (int i = 0; i < n2; i++) {
    R[i] = arr[i + m + 1];
  }

  // Merge two arrays
  int k = l;
  int idxL = 0, idxR = 0;

  while (idxL < n1 && idxR < n2) {
    if (L[idxL] < R[idxR]) {
      arr[k++] = L[idxL++];
    } else {
      arr[k++] = R[idxR++];
    }
  }

  // Add remaining elements
  while (idxL < n1) {
    arr[k++] = L[idxL++];
  }

  while (idxR < n2) {
    arr[k++] = R[idxR++];
  }
}

void mergeSortHelper(std::vector<int> &arr, int l, int r) {
  // Base case
  if (l == r) {
    return;
  }

  int m = l + (r - l) / 2;
  mergeSortHelper(arr, l, m);
  mergeSortHelper(arr, m + 1, r);
  merge(arr, l, r, m);
}

void mergeSort(std::vector<int> &arr) {
  mergeSortHelper(arr, 0, arr.size() - 1);
}

int main() {
  std::vector<int> arr{4, 2, 1, 100, 3, 9, 1000, 5, 7, -1, -2};
  mergeSort(arr);
  for (unsigned i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << ",";
  }
  std::cout << std::endl;
}