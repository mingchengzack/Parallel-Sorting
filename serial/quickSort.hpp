#include <random>
#include <vector>

int getRandomPivot(int l, int r) {
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr(l, r);
  return distr(generator);
}

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

  int pivot = getRandomPivot(l, r);
  int partitionIdx = partition(arr, l, r, pivot);

  quickSortHelper(arr, l, partitionIdx - 1);
  quickSortHelper(arr, partitionIdx + 1, r);
}

void quickSort(std::vector<int> &arr) {
  quickSortHelper(arr, 0, arr.size() - 1);
}