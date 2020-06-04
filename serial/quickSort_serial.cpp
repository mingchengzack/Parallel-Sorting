#include <omp.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

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
  quickSort(arr);
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
