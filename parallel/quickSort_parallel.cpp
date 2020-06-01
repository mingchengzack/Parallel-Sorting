// Parallel quick sort
#include <omp.h>

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int partition(vector<int> &arr, int l, int r, int pivot) {
  int partitionIdx = l - 1;
  int pivotElement = arr[pivot];

  // Swap pivot to the right
  swap(arr[r], arr[pivot]);

  // Move elements that are smaller than pivot to left
  for (int i = l; i < r; i++) {
    if (arr[i] <= pivotElement) {
      swap(arr[i], arr[++partitionIdx]);
    }
  }

  // Swap pivot back
  swap(arr[r], arr[++partitionIdx]);

  return partitionIdx;
}

// Serial version of quick sort helper 
void quickSortHelper(vector<int> &arr, int l, int r) {
  // Base case
  if (l >= r) {
    return;
  }

  int pivot = l;
  int partitionIdx = partition(arr, l, r, pivot);

  quickSortHelper(arr, l, partitionIdx - 1);
  quickSortHelper(arr, partitionIdx + 1, r);
}

// Parallel version of quick sort helper
void openmp_quickSortHelper(vector<int> &arr, int l, int r, int p) {
  // If the size is less than threshold, we use serial version
  if (r - l <= 200) {
    quickSortHelper(arr, l, r);
    return;
  }

  int pivot = l;
  int partitionIdx = partition(arr, l, r, pivot);

  #pragma omp task
    openmp_quickSortHelper(arr, l, partitionIdx - 1, p);
  
  #pragma omp task
    openmp_quickSortHelper(arr, partitionIdx + 1, r, p);
}

// Parallel version of quick sort
void openmp_quickSort(vector<int> &arr, int p) {
  if (p == 1) {
    cout << "Num of threads: " << omp_get_num_threads() << endl;
    quickSortHelper(arr, 0, arr.size() - 1);
  } else {
    #pragma omp parallel num_threads(p)
    {
      #pragma omp single
        cout << "Num of threads: " << omp_get_num_threads() << endl;
      #pragma omp single
        openmp_quickSortHelper(arr, 0, arr.size() - 1, p);
    }
  }
}

int main(int argc, char **argv) {
  vector<int> arr;
  ifstream myfile;
  char filename[] = "arrays/1000000.txt";
  myfile.open(filename);
  
  int e;
  while (myfile >> e) {
    arr.push_back(e);
  }
  myfile.close();

  int p = 4;
  if (argc >= 2) {
    p = min(stoi(argv[1]), 24);
  }
  
  double start = omp_get_wtime();
  openmp_quickSort(arr, p);
  double end = omp_get_wtime();
  double time = end - start;
  cout << "Time for execution: " << time * 1000 << " miliseconds." << endl;
  
  myfile.open(filename);
  vector<int> sorted;

  while (myfile >> e) {
    sorted.push_back(e);
  }
  myfile.close();

  // Sort the arry using std::sort
  // and compare it with my bitonic sort for correctness
  sort(sorted.begin(), sorted.end());             
  
  for (unsigned i = 0; i < arr.size(); i++) {
    assert(arr[i] == sorted[i]);
  }
}
