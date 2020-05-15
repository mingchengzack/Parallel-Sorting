// Generate random arrays into files
#include <ctime>
#include <fstream>
#include <iostream>

int main() {
  time_t t;
  srand((unsigned)time(&t));
  int sizes[3] = {1000, 10000, 100000};

  for (int i = 0; i < 3; i++) {
    int n = sizes[i];
    std::ofstream myfile;
    myfile.open("./arrays/" + std::to_string(n) + ".txt");

    for (int i = 0; i < n; i++) {
      myfile << rand() % 500 << " ";
    }
  }
}