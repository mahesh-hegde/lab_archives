#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <gd.h>

char dest[512] = {0};

void check(int condition, const char *error) {
	if (!condition) {
		fprintf(stderr, "Error: %s", error);
		perror("Last reported system error is: ");
		exit(1);
	}
}

void negate(const char *path, double *time, int printDims) {
	FILE *fp = fopen(path, "r");
	check(fp != NULL, "cannot open input file");
	gdImagePtr img = gdImageCreateFromPng(fp);
	double begin = omp_get_wtime();
	int w = gdImageSX(img);
	int h = gdImageSY(img);
	#pragma omp parallel for
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int color = gdImageGetPixel(img, x, y);
			int inv = 255 - ((gdImageRed(img, color) + gdImageGreen(img, color) + gdImageBlue(img, color))/3);
			int alloc = gdImageColorAllocate(img, inv, inv, inv);
			gdImageSetPixel(img, x, y, alloc);
		}
	}
	double end = omp_get_wtime();
	sprintf(dest, "%s.neg.png", path);
	fclose(fp);
	FILE *out = fopen(dest, "w");
	gdImagePng(img, out);
	fclose(out);
	if (printDims) {
		int pch = printf("%d x %d | ", w, h);
		printf("%*s", 20 - pch, "");
	}
	*time = end - begin;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "please provide arguments\n");
		return 1;
	}
	printf ("%-20s%-20s%-20s%-20s%-20s\n", "Dims", "1", "2", "4", "8");
	for (int i = 1; i < argc; i++) {
		for (int th = 1; th <= 8; th *= 2) {
			omp_set_num_threads(th);
			double time;
			negate(argv[i], &time, th == 1);
			printf("%-17.4lg | ", time);
		}
		printf("\n");
	}
}
