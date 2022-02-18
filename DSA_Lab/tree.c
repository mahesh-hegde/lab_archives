#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int val;
	struct node *left, *right;
} Node;

Node *node(int data) {
	Node *nd = malloc(sizeof(Node));
	nd->val = data;
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

Node *insert(Node *tree, Node *data) {
	Node *node = tree, *prev = NULL;
	if (tree == NULL) return data;
	while (node) {
		if (node->val < data->val) {
			if (node->right == NULL) {
				node->right = data;
				return tree;
			} else {
				node = node->right;
				continue;
			}
		} else if (node->val == data->val) {
			return tree;
		} else {
			if (node->left == NULL) {
				node->left = data;
				return tree;
			} else {
				node = node->left;
				continue;
			}
		}
	}
}

Node *next_largest(Node *tree) {
	Node *r;
	if (!tree) return NULL;
	while (tree->left) {
		tree = tree->left;
	}
	return tree;
}

Node *delete(Node *tree, int val) {
	// If a node is deleted
	// the smallest left node is swapped with it
	if (!tree) {
		printf("Not found: %d\n", val);
		return NULL;
	} else if (tree->val == val) {
		if (tree->left == NULL) {
			Node *r = tree->right;
			free(tree);
			return r;
		} else if (tree->right == NULL) {
			Node *r = tree->left;
			free(tree);
			return r;
		} else {
			int v;
			Node *nl = next_largest(tree->right);
			v = nl->val;
			tree->right = delete(tree->right, nl->val);
			tree->val = v;
			return tree;
		}
	} else if (tree->val > val) {
		tree->left = delete(tree->left, val);
		return tree;
	} else {
		tree->right = delete(tree->right, val);
		return tree;
	}
}

void inorder(Node *tree) {
	if (!tree) return;
	inorder(tree->left);
	printf("%d ", tree->val);
	inorder(tree->right);
}

void preorder(Node *tree) {
	if (!tree) return;
	printf("%d ", tree->val);
	preorder(tree->left);
	preorder(tree->right);
}

void postorder(Node *tree) {
	if (!tree) return;
	postorder(tree->left);
	postorder(tree->right);
	printf("%d ", tree->val);
}

int main() {
	int n, choice;
	Node *tree = NULL;
	while(1) {
		printf("0. Exit | 1. Insert | 2. Delete | 3. Insert Many:  ");
		scanf("%d", &choice);
		switch(choice) {
			case 0: return 0;
			case 1: printf("Number to insert: ");
				scanf("%d", &n);
				tree = insert(tree, node(n));
				break;
			case 2: printf("Number to delete: ");
				scanf("%d", &n);
				tree = delete(tree, n);
				break;
			case 3: printf("Semicolon-terminated list of numbers: ");
				while(scanf("%d", &n) == 1) {
					tree = insert(tree, node(n));
				}
				scanf(";");
				break;
			default: printf("Invalid choice!!\n");
		}
		printf("\e[31mINORDER: ");
		inorder(tree);
		printf("\nPREORDER: ");
		preorder(tree);
		printf("\nPOSTORDER: ");
		postorder(tree);
		printf("\e[0m\n");
	}
	return 0;
}
