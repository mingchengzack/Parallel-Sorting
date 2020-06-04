#include <omp.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Swap in the given direction
void compSwap(vector<int> &arr, int i, int j, bool dir) {
  bool isGreater = arr[i] > arr[j];
  if (dir == isGreater) {
    swap(arr[i], arr[j]);
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
void bitonicMerge(vector<int> &arr, int l, int cnt, bool dir) {
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

void bitonicSortHelper(vector<int> &arr, int l, int cnt, bool dir) {
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

void bitonicSort(vector<int> &arr) {
  bitonicSortHelper(arr, 0, arr.size(), true);
}

int main(int argc, char **argv) {
  vector<int> arr;
  ifstream myfile;
  string filename = "arrays/1000000.txt";
  if (argc >= 2) {
    filename = "arrays/" + string(argv[1]) + ".txt";
  }

  myfile.open(filename);
  int e;
  while (myfile >> e) {
    arr.push_back(e);
  }
  myfile.close();

  double start = omp_get_wtime();
  bitonicSort(arr);
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
