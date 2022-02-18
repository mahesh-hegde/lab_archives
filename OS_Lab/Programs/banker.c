#include <stdio.h>

#define MAX 16

int avail[MAX], max[MAX][MAX];
int allot[MAX][MAX];
int completed[MAX] = {0};

int need(int i, int j) {
	return max[i][j] - allot[i][j];
}

void read_matrix(int process, int resource, int matrix[][MAX]) {
	int i, j, instance;
	for (i = 0; i < process; i++) {
		printf("P[%d]: ", i);
		for (j = 0; j < resource; j++) {
			scanf("%d", &instance);
			matrix[i][j] = instance;
		}
	}
}

int main() {
	int process, resource, i, j, instance, k = 0;
	int count1 = 0, count2 = 0;
	printf("Num. of processes & resources: ");
	scanf("%d %d", &process, &resource);

	printf("Num. of available instances: ");
	for (i=0; i < resource; i++) {
		scanf("%d", &instance);
		avail[i] = instance;
	}
	printf("Enter Max. Requirement matrix:\n");
	read_matrix(process, resource, max);
	printf("Enter Allocation Matrix:\n");
	read_matrix(process, resource, allot);

	printf("Safe sequence:\n");
	while (count1 != process) {
		count2 = count1;
		for (i=0; i<process; i++) {
			for (j = 0; j<resource; j++) {
				if(need(i,j) <= avail[j]) {
					k++;
				}
			}
			if (k == resource && completed[i] == 0) {
				printf("Complete: P[%d]\n", i);
				completed[i] = 1;
				for (j = 0; j < resource; j++) {
					avail[j] += allot[i][j];
				}
				count1++;
			}
			k = 0;
		}
	}
}
