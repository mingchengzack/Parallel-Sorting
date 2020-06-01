// Parallel merge sort
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

// Serial version of merge
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
  
// Serial version of merge sort helper
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

// Parallel version of merge
void openmp_merge(vector<int> &arr, int l, int r, int m, int p) {
  int n1 = m - l + 1;
  int n2 = r - m;
  vector<int> L(n1, 0), R(n2, 0);

  #pragma omp parallel num_threads(p)
  {
    // Copy left array 
    #pragma omp for schedule(static) nowait
    for (int i = 0; i < n1; i++) {
      L[i] = arr[i + l];
    }
  
    // Copy right array
    #pragma omp for
    for (int i = 0; i < n2; i++) {
      R[i] = arr[i + m + 1];
    }

    // Merge two arrays
    #pragma omp for
    for (int k = l, idxL = 0, idxR = 0; k <= r; k++) {
      if (idxL == n1) {
        arr[k] = R[idxR++];
      } else if (idxR == n2) {
        arr[k] = L[idxL++];
      } else {
        if (L[idxL] < R[idxR]) {
          arr[k] = L[idxL++];
        } else {
          arr[k] = R[idxR++];
        }
      }
    }
  }
}

// Parallel version of merge sort helepr
void openmp_mergeSortHelper(vector<int> &arr, int l, int r, int p) {
  // If the size is less than threshold, we use serial version
  if (r - l <= 200) {
    mergeSortHelper(arr, l, r);
    return;
  }
  
  int m = l + (r - l) / 2;

  #pragma omp task
    openmp_mergeSortHelper(arr, l, m, p);
  
  #pragma omp task
    openmp_mergeSortHelper(arr, m + 1, r, p);
  
  #pragma omp taskwait
    openmp_merge(arr, l, r, m, p);
}


// Parallel version of merge sort
void openmp_mergeSort(vector<int> &arr, int p) {
  if (p == 1) {
    cout << "Num of threads: " << omp_get_num_threads() << endl;
    mergeSortHelper(arr, 0, arr.size() - 1);
  } else {
    #pragma omp parallel num_threads(p)
    {
      #pragma omp single
        cout << "Num of threads: " << omp_get_num_threads() << endl;
      #pragma omp single
        openmp_mergeSortHelper(arr, 0, arr.size() - 1, p);
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
  openmp_mergeSort(arr, p);
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
