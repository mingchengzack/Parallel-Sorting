#include <omp.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &arr, int l, int r, int m) {
  int n1 = m - l + 1;
  int n2 = r - m;
  vector<int> L(n1, 0), R(n2, 0);

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

void mergeSortHelper(vector<int> &arr, int l, int r) {
  // Base case
  if (l == r) {
    return;
  }

  int m = l + (r - l) / 2;
  mergeSortHelper(arr, l, m);
  mergeSortHelper(arr, m + 1, r);
  merge(arr, l, r, m);
}

void mergeSort(vector<int> &arr) { mergeSortHelper(arr, 0, arr.size() - 1); }

int main(int argc, char **argv) {
  vector<int> arr;
  ifstream myfile;
  string filename = "arrays/1000000.txt";
  if (argc >= 2) {
    filename = "arrays/" + string(argv[2]) + ".txt";
  }

  myfile.open(filename);
  int e;
  while (myfile >> e) {
    arr.push_back(e);
  }
  myfile.close();

  double start = omp_get_wtime();
  mergeSort(arr);
  double end = omp_get_wtime();
  double time = end - start;
  cout << "Running on " << filename << endl;
  cout << "Time for execution: " << time * 1000 << " miliseconds." << endl;

  myfile.open(filename);
  vector<int> sorted;

  while (myfile >> e) {
    sorted.push_back(e);
  }
  myfile.close();

  // Sort the arry using std::sort
  // and compare it with my sort for correctness
  sort(sorted.begin(), sorted.end());

  for (unsigned i = 0; i < arr.size(); i++) {
    assert(arr[i] == sorted[i]);
  }

  cout << "Passed test against std::sort" << endl;
}
