#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

struct timeval startwtime, endwtime;
double seq_time;

int N, M;
int *a;

const int ASCENDING = 1;
const int DESCENDING = 0;

void rng();
void exchange(int x, int y);
int getPowerOfTwo(int n);
void print();

int main(int argc, char *argv[]) {
   if (argc != 3) {
    printf("Failed");
    exit(1);
  }
   int thread_count = strtol(argv[1], NULL, 10);
   N = atoi(argv[2]);
   if (N<=0) {
      printf("N must be positive");
      return 0;
   }
   M = getPowerOfTwo(N);
   a = (int *) malloc(M * sizeof(int));
   rng();

   int i,j,k;

   gettimeofday (&startwtime, NULL);
   for (k = 2; k <= M; k <<= 1) {
      for (j = k >> 1; j > 0; j >>= 1) {
      	 #pragma omp parallel for num_threads(thread_count)
         for (i = 0; i < M; ++i) {
         	int ij = i ^ j;
         	if (ij > i) {
         		if ((i & k) == 0 && a[i] > a[ij]) {
         			exchange(i, ij);
         		} else if ((i & k) != 0 && a[i] < a[ij]) {
         			exchange(i, ij);
         		}
         	}
         }
      }
   }
   gettimeofday (&endwtime, NULL);

   seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		      + endwtime.tv_sec - startwtime.tv_sec);
   printf("Imperative wall clock time = %f\n", seq_time);

   return 0;
}

void rng() {
	int seed = 13515021;
	int maks = 0;
	srand(seed);
	int i;
	for (i = 0; i < N; ++i) {
		a[i] = (int)rand();
		if (a[i] > maks) {
			maks = a[i];
		}
	}
	for (i = N; i < M; ++i) {
		a[i] = maks;
	}
}

void exchange(int x, int y) {
	int temp = a[x];
	a[x] = a[y];
	a[y] = temp;
}

int getPowerOfTwo(int n) {
	int m = 1;
	while (m<n) {
		m <<= 1;
	}
	return m;
}

void print() {
	int i;
	for (i = 0; i < N; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

