#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int row, col, val;
	struct node *next;
} Node;

Node *node(int row, int col, int val, Node *prev, Node *next) {
	Node *nd = (Node *)malloc(sizeof(Node));
	nd->row = row;
	nd->col = col;
	nd->val = val;
	nd->next = next;
	return nd;
}

void print_sparse(Node *matrix, int m, int n) {
	int i, j;
	for (i=0; i < m; i++) {
		for(j = 0; j < n; j++) {
			if(matrix != NULL &&
					matrix->row == i &&
					matrix->col == j) {
				printf("%4d ", matrix->val);
				matrix = matrix->next;
			} else {
				printf("%4d ", 0);
			}
		}
		printf("\n");
	}
}

int main() {
	int row, col, val, m, n;
	Node *list = node(-1,-1,-1,NULL,NULL); // DUMMY NODE
	Node *lbegin = list;
	printf("Num. of rows & columns: ");
	
	if(scanf("%d %d", &m, &n) != 2) {
		printf("Enter valid dimensions\n");
		return 1;
	}

	printf("Enter elements in <row>,<col>,<val> format, ");
	printf("incr. order by row & column, ");
	printf("separated by spaces, terminated by \'end\':\n");
	while(scanf("%d,%d,%d", &row, &col, &val) == 3) {
		if (row >= m || col >= n) {
			printf("Invalid row/column index\n");
			return 1;
		}
		list->next = node(row,col,val,list,list->next);
		list = list->next;
	}
	print_sparse(lbegin->next, m, n);
	return 0;
}
