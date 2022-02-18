#include<stdio.h>
#include<stdlib.h>

#define MAX 32

const int DELETED = -1;
const int UNUSED = -2;

// A Hash Set of positive integers
typedef struct hash_set {
	int array[MAX];
	int count;
} HashSet;


int hash(int num) {
	return num % MAX;
}

void init_hashset(HashSet *h) {
	int i;
	h->count = 0;
	for (i=0;i<MAX;i++) h->array[i] = UNUSED;
}

int find(HashSet *h, int val) {
	int hs = hash(val), i;
	for(i = 0; i < MAX; i++) {
		int hindex = (hs+i)%MAX;
		if (h->array[hindex] == UNUSED) {
			return -1;
		} else if (h->array[hindex] == val) {
			return hindex;
		}
	}
	return -1; // Searched entire array, not found
}


void insert(HashSet *h, int val) {
	int hs = hash(val); // hash is already modulo array size
	int i;
	if (h->count == MAX) {
		printf("HashSet is full!!\n");
		return;
	}

	if (find(h, val) != -1) return;

	for (i=0;i<MAX;i++) {
		int hindex = (hs+i)%MAX;
		if(h->array[hindex] == UNUSED 
				|| h->array[hindex] == DELETED) {
			h->array[hindex] = val;
			h->count++;
			return;
		}
	}
	return;
}

int delete(HashSet *h, int val) {
	int pos = find(h, val);
	if (pos == -1) return 0;
	h->array[pos] = DELETED;
	h->count--;
	return 1;
}

void print_hashset(HashSet *h) {
	int i;
	if (h->count == 0) printf("Empty");
	for(i = 0; i < MAX; i++) {
		if (h->array[i] != UNUSED && h->array[i] != DELETED) {
			printf("[%d @ %d] ", h->array[i], i);
		}
	}
	printf("\n");
}

int main() {
	HashSet h;
	init_hashset(&h);
	while(1) {
		int n, ch, pos;
		printf("0. Exit  1. Insert  2. Delete  3. Find");
		printf("  4. Insert Many  5. Clear\n");
		scanf("%d", &ch);
		switch(ch) {
		case 0: return 0;
		case 1: printf("Number to insert: ");
			scanf("%d", &n);
			insert(&h, n);
			break;
		case 2: printf("Number to delete: ");
			scanf("%d", &n);
			printf(delete(&h, n) ? "Successfully deleted\n" : "Not Found\n");
			break;
		case 3: printf("Number to search for: ");
			scanf("%d", &n);
			pos = find(&h, n);
			if (pos != -1) {
				printf("Found at bucket %d\n", pos);
			} else {
				printf("Not found\n");
			}
			break;
		case 4: printf("Numbers to insert, (terminate by \';\'): ");
			while(scanf("%d", &n) == 1) {
				insert(&h, n);
			}
			scanf(";");
			break;
		case 5: init_hashset(&h);
			break;
		default: printf("Invalid Choice\n");
		}
		printf("\e[32mHashSet = ");
		print_hashset(&h);
		printf("\e[0m");
	}
}
