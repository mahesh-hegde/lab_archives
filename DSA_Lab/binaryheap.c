#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAX 32

typedef struct binary_heap {
	int array[MAX];
	int len;
} Heap;

int left(int i) {
	return 2*i + 1;
}

int right(int i) {
	return 2*i + 2;
}

int parent(int i) {
	return i == 0 ? 0 : (i-1)/2;
}

void init_heap(Heap *h) {
	h->len = 0;
}

void bubble_up(Heap *h, int i) {
	int *a = h->array;
	assert(i < MAX);
	int p = parent(i);
	while(i > 0 && a[i] < a[p]) {
		int temp = a[i];
		a[i] = a[p];
		a[p] = temp;
		i = p;
		p = parent(i);
	}
}

void insert(Heap *h, int n) {
	if (h->len == MAX) {
		printf("Overflow!!\n");
	} else {
		h->array[h->len++] = n;
		bubble_up(h, h->len - 1);
	}
}

void bubble_down(Heap *h, int i) {
	int n = h->len;
	int *a = h->array;
	// compare with left child & right child
	// swap with the minimum of childs
	do {
		int j = -1;
		int r = right(i);
		if (r < n && a[r] < a[i]) {
			int l = left(i);
			j = a[l] < a[r] ? l : r;
		} else {
			int l = left(i);
			if (l < n && a[l] < a[i]) j = l;
		}
		if (j >= 0) {
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		i = j;
	} while (i >= 0);
}

int delete_min(Heap *h) {
	if (h->len == 0) {
		printf("Underflow!!\n");
		return -1;
	} else {
		int *a = h->array;
		int r = a[0];
		a[0] = a[--h->len];
		bubble_down(h, 0);
		return r;
	}
}

void print_heap(Heap *h) {
	int i;
	printf("\e[35m[");
	if (h->len == 0) printf("Empty Heap");
	for(i = 0; i < h->len; i++) {
		printf("%d ", h->array[i]);
	}
	printf("]\e[0m\n");
}

int main() {
	int n, choice;
	Heap h;
	init_heap(&h);
	while(1) {
		printf("1. Insert   2. Delete Min  3. Clear  ");
		printf("4. Insert Many  0. Exit\n");
		scanf("%d", &choice);
		switch(choice) {
		case 0: return 0;
		case 1: printf("Enter number: ");
			scanf("%d", &n);
			insert(&h, n);
			break;
		case 2: n = delete_min(&h);
			if (n >= 0) printf("Deleted %d\n", n);
			break;
		case 3: init_heap(&h);
			break;
		case 4: printf("Enter semicolon terminat. list of nums: ");
			while(scanf("%d", &n) == 1) {
				insert(&h, n);
			}
			scanf(";");
			break;
		default: printf("Invalid choice!!\n");
		}
		print_heap(&h);
	}
	return 0;
}
