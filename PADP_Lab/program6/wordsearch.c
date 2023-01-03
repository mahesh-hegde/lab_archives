#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h> // for clock

#define file "words.txt"
#define MAX_WORD_SIZE 256

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

int getCount(const char *word) {
	char buf[MAX_WORD_SIZE];
	FILE *fp = fopen(file, "r");
	int count = 0;
	while(fscanf(fp, "%255s", buf) != EOF) {
		if (strncmp(buf, word, strlen(word)) == 0) {
			count++;
		}
	}
	fclose(fp);
	return count;
}

const char *words[] = {"tomato", "potato", "watermelon", "apple"};

const char *allwords[] = {
	"tomato", "potato", "watermelon", "apple", "pineapple", "mango", "banana",
	"lettuce", "radish", "strawberry", "powerpoint",
};

int wordCounts[ARRAYSIZE(allwords)] = {0};

const int minN = 10000;
const int maxN = minN * 1000;

void writeRandom(int n) {
	memset(wordCounts, 0, sizeof(wordCounts));
	FILE *fp = fopen(file, "w");
	for (int i = 0; i < n-1; i++) {
		int index = rand() % ARRAYSIZE(allwords);
		fprintf(fp, "%s ", allwords[index]);
	}
	fprintf(fp, "%s", allwords[rand() % ARRAYSIZE(allwords)]);
	fflush(fp);
	fclose(fp);
}

void compute(double *time) {
	double begin = omp_get_wtime();
	#pragma omp parallel for
	for (int i = 0; i < ARRAYSIZE(words); i++) {
		int count = getCount(words[i]);
		printf("\e[32m%-8s: %-8d, \e[0m ", words[i], count);
	}
	printf("\n");
	double end = omp_get_wtime();
	*time = end - begin;
}

int main(int argc, char **argv) {
	srand(clock());
	printf("%-20s%-20d%-20d%-20d%-20d\n", "Total Words", 1, 2, 4, 8);
	for (int n = minN; n <= maxN; n *= 10) {
		writeRandom(n);
		double times[4];
		for (int i = 0; i <= 3; i++) {
			double time;
			omp_set_num_threads(1 << i);
			compute(&time);
			times[i] = time;
		}
		printf("%-20d | ", n);
		for (int i = 0; i < 4; i++) {
			printf("%-20lg | ", times[i]);
		}
		printf("\n");
	}
	remove(file);
}
