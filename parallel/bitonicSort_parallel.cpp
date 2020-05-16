// Parallel bitonic sort
#include <omp.h>

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Swap in the given direction
void compSwap(vector<int> &arr, int i, int j, bool dir) {
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
void bitonicMerge(vector<int> &arr, int l, int cnt, bool dir, int p) {
  if (cnt <= 1) {
    return;
  }

  int k = greatestPowerOfTwoLessThan(cnt);
  int i;

  #pragma omp parallel num_threads(p)
  {
    #pragma omp for schedule(static) nowait
    for (i = l; i < l + cnt - k; i++) {
      compSwap(arr, i, i + k, dir);
    }

    #pragma omp single
    {
      #pragma omp task if(cnt > 1024)
        bitonicMerge(arr, l, k, dir, p);

      #pragma omp task if(cnt > 1024)
        bitonicMerge(arr, l + k, cnt - k, dir, p);
    }
  }
}

void bitonicSortHelper(vector<int> &arr, int l, int cnt, bool dir, int p) {
  // Base case
  if (cnt <= 1) {
    return;
  }

  int k = cnt / 2;

  // Sort in ascending order
  #pragma omp task if(cnt > 1024)
    bitonicSortHelper(arr, l, k, !dir, p);

  // Sort in descending order
  #pragma omp task if(cnt > 1024)
    bitonicSortHelper(arr, l + k, cnt - k, dir, p);

  // Merge sequence in ascending order
  #pragma omp taskwait
  bitonicMerge(arr, l, cnt, dir, p);
}

void bitonicSort(vector<int> &arr, int p) {
  #pragma omp parallel num_threads(p)
  {
    #pragma omp single
      cout << "Num of threads: " << omp_get_num_threads() << endl;
    #pragma omp single
      bitonicSortHelper(arr, 0, arr.size(), true, p);
  }
}

int main(int argc, char **argv) {
  std::vector<int> arr;
  ifstream myfile ("arrays/100000.txt");
  
  int e;
  while (myfile >> e) {
    arr.push_back(e);
  }

  int p = 4;
  if (argc >= 2) {
    p = min(stoi(argv[1]), 24);
  }
  
  double start = omp_get_wtime();
  bitonicSort(arr, p);
  double end = omp_get_wtime();
  double time = end - start;
  cout << "Time for execution: " << time * 1000 << " miliseconds." << endl;
  
  //for (unsigned i = 0; i < arr.size(); i++) {
    //std::cout << arr[i] << ",";
  //}
  //std::cout << std::endl;
}
