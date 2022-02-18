#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 20

typedef struct node {
	char sym;
	struct node *left, *right;
} Node;

Node *node(char sym) {
	Node *nd = malloc(sizeof(Node));
	nd->sym = sym;
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

typedef struct stack {
	Node *data[MAX];
	int top;
} Stack;

void preorder(Node *tree) {
	if (!tree) return;
	printf("%c ", tree->sym);
	preorder(tree->left);
	preorder(tree->right);
}

void postorder(Node *tree) {
	if (!tree) return;
	postorder(tree->left);
	postorder(tree->right);
	printf("%c ", tree->sym);
}

void inorder(Node *tree) {
	if (!tree) return;
	inorder(tree->left);
	printf("%c ", tree->sym);
	inorder(tree->right);
}

Node *pop(Stack *s) {
	return (s->top == 0) ? NULL : s->data[--s->top];
}

void push(Stack *s, Node *e) {
	if (s->top == MAX) {
		printf("Overflow\n");
	} else {
		s->data[s->top++] = e;
	}
}

int preced(char sym) {
	switch(sym) {
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	default: return 0;
	}
}

Node *build_expr(char *s) {
	Node *temp, *t = NULL, *l = NULL, *r = NULL;
	char *sp;
	Stack tree, op;
	tree.top = 0; op.top = 0;
	for(sp = s; *sp; sp++) {
		char ch = *sp;
		temp = node(ch);
		if (isalpha(ch)) {
			push(&tree, temp);
		} else {
			while(op.top != 0
					&& preced(ch) <= preced(op.data[op.top-1]->sym)) {
				t = pop(&op);
				r = pop(&tree);
				l = pop(&tree);
				/* if (t) */ t->left = l;
				/* if (t) */ t->right = r;
				push(&tree, t);
			}
			push(&op, temp);
		}
	}
	while(op.top != 0) {
		t = pop(&op);
		r = pop(&tree);
		l = pop(&tree);
		t->left = l;
		t->right = r;
		push(&tree, t);
	}
	return pop(&tree);
}

int main() {
	Node *root = NULL;
	int ch, ele;
	char str[MAX];
	int i = 0;

	printf("Enter expression: ");
	scanf("%[^\n]", str);
	root = build_expr(str);
	printf("Inorder: ");
	inorder(root);
	printf("\nPostorder: ");
	postorder(root);
	printf("\nPreorder: ");
	preorder(root);
	printf("\n");
	return 0;
}
