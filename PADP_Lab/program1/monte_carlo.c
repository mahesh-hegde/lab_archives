#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

const int minIter = 100000;

const int maxIter = minIter * 1000;

int counts[4] = {0, 0, 0, 0};

double compute(int nIter) {
	double x, y, z, pi;
	int count = 0;
	// for n random points in unit square (area 1)
	// check how many points are inside 1/4th a circle (area pi/4)
	// (pi/4)/1 = count / niter (proportionality, assuming good randomness)
	// pi = 4 * (count / niter)
	#pragma omp parallel
	{
	int localCount = 0;
	// This is the seed value for rand_r function.
	// (should actually use something better here than clock)
	unsigned int randomState = clock();
	#pragma omp for
	for (int i = 0; i < nIter; i++) {
		x = (double)rand_r(&randomState) / RAND_MAX;
		y = (double)rand_r(&randomState) / RAND_MAX;
		if ((x*x + y*y) <= 1) localCount++;
	}
	#pragma omp critical
	count += localCount;
	}
	return 4 * (double)count/nIter;
}

int main(int argc, char **argv) {
	srandom(clock());
	int k = 0; // number of iterations
	printf("%-20s%-20d%-20d%-20d%-20d\n", "iterations", 1, 2, 4, 8);
	for (int nIter = minIter; nIter <= maxIter; nIter *= 10) {
		printf("%-20d", nIter);
		for (int i = 1; i <= 8; i*=2) {
			omp_set_num_threads(i);
			double pi;
			double begin = omp_get_wtime();
			pi = compute(nIter);
			double end = omp_get_wtime();
			printf("%-8.4lg \e[31;1m%-6.4lg\e[0m|\t", (end - begin) * 1000, pi);
		}
		printf("\n");
	}
}
