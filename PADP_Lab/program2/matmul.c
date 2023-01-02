#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

int inputs[][3] = {
	{1000, 1, 1000},
	{1000, 100, 500},
	{500, 500, 500},
	{1000, 1000, 1000},
	{1500, 1500, 1500},
};

void compute(int dims[3], double *time) {
	int m = dims[0], n = dims[1], p = dims[2];
	int *a = malloc(m * n * sizeof(int));
	int *b = malloc(n * p * sizeof(int));
	int *c = malloc(m * p * sizeof(int));

	double begin = omp_get_wtime();
	#pragma omp parallel for
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < n; k++) {
				c[i*p+j] = a[i*n+k] * b[k*p+j]; 
			}
		}
	}
	double end = omp_get_wtime();
	*time = end - begin;
	free(a);
	free(b);
	free(c);
}

const int firstColumnWidth = 32;

int main() {
	printf("Matrix multiplication speed measurements\n");
	printf("%-34s%-18d%-18d%-18d%-18d\n", "Input", 1, 2, 4, 8);
	for (int i = 0; i < ARRAYSIZE(inputs); i++) {
		// print input spec
		int *dims = inputs[i];
		int pch = printf("[%d x %d] X [%d x %d]", dims[0], dims[1], dims[1], dims[2]);
		printf("%*s", firstColumnWidth-pch, "| ");
		for (int th = 1; th <= 8; th *= 2) {
			omp_set_num_threads(th);
			double time;
			compute(dims, &time);
			printf("%-10.4lg | %6s", time, "");
			fflush(stdout);
		}
		printf ("\n");
	}
}
