#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gd.h>

#include <omp.h>

void check(int condition, const char *error) {
	if (!condition) {
		fprintf(stderr, "Error: %s\n", error);
		exit(1);
	}
}
// gdImagePtr (type), gdImageCreateFromPng, gdImageS{X,Y}, gdImageGetPixel,
// gdImage{RGB}, gdImageColorAllocate, gdImagePng, gdImageSetPixel, gdImageDestroy

int main(int argc, char **argv) {
	FILE *fp = NULL;
	gdImagePtr img;
	char *iname, *oname;
	if (argc != 3) {
		printf("usage: %s input output\n", argv[0]);
		return 1;
	}
	iname = argv[1];
	oname = argv[2];
	int w, h, i = 0;
	fp = fopen(iname, "r");
	check(fp != NULL, "cannot open input file");
	img = gdImageCreateFromPng(fp);
	w = gdImageSX(img);
	h = gdImageSY(img);
	double begin = omp_get_wtime();
	#pragma omp parallel for
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int color = gdImageGetPixel(img, x, y);
			int avgColor = 255 - (gdImageRed(img, color) + gdImageGreen(img, color) 
				+ gdImageBlue(img, color)) / 3;
			int allocColor = gdImageColorAllocate(img, avgColor, avgColor, avgColor);
			#pragma omp critical
			gdImageSetPixel(img, x, y, allocColor);
		}
	}
	double end = omp_get_wtime();
	FILE *out = fopen(oname, "w");
	check(out != NULL, "cannot open output file");
	gdImagePng(img, out);
	fclose(fp);
	fclose(out);
	gdImageDestroy(img);
	printf("%.4lg ms\n", (end - begin)/3);
	return 0;
}
