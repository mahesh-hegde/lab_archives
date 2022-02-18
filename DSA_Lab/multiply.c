#include "stdio.h"
#include<stdlib.h>

typedef struct node {
	int coeff, power;
	struct node *next;
} Node;

Node *node(int coeff, int power, Node *next) {
	Node *nd = (Node *)malloc(sizeof(node));
	nd->coeff = coeff; nd->power = power; nd->next = next;
	return nd;
}

void print_pol(Node *pol) {
	if (!pol) printf("(null)");
	while(pol) {
		if (pol->coeff != 0) printf("%d:%d ", pol->coeff, pol->power);
		pol = pol->next;
	}
	printf("\n");
}

Node *le_find(Node *list, int power) {
	while(list->next) {
		if (list->next->power >= power) return list;
		list = list->next;
	}
	return list;
}

Node *add_term(Node *to, int coeff, int power) {
	Node *reach = le_find(to, power);
	if (reach->next != NULL && reach->next->power == power) {
		reach->next->coeff += coeff;
	} else {
		reach->next = node(coeff,power,reach->next);
	}

	return reach;
}

Node *multiply(Node *a, Node *b) {
	Node *b_cpy = b;
	Node *res = node(-1,-1,NULL); // dummy node
	while(a) {
		b = b_cpy;
		Node *r = res;
		while(b) {
			r = add_term(r,
				b->coeff*a->coeff,
				b->power+a->power
			);
			b = b->next;
		}
		a = a->next;
	}
	return res->next;
}


int main() {
	Node *a = node(-1,-1,NULL), *b = node(-1,-1,NULL), *result;
	// make a copy of dummy nodes
	Node *a_begin = a, *b_begin = b;
	int coeff, power, last_power;
	printf("Enter terms of polynomial in coeff:power format\n");
	printf("In increasing order of power\n");
	printf("After all terms write \'end\'\n");
	printf("Enter terms in polynomial A: ");
	while(scanf(" %d:%d", &coeff, &power) == 2) {
		if (power <= last_power && a != a_begin) {
			printf("Error: needs increasing order of power\n");
			return 1;
		}
		last_power = power;
		a->next = node(coeff,power,NULL);
		a = a->next;
	}

	scanf("end");

	printf("Enter terms in polynomial B: ");
	while(scanf(" %d:%d", &coeff, &power) == 2) {
		if (power <= last_power && b != b_begin) {
			printf("Error: needs increasing order of power\n");
			return 1;
		}
		last_power = power;
		b->next = node(coeff,power,NULL);
		b = b->next;
	}

	result = multiply(a_begin->next,b_begin->next);
	print_pol(result);
	return 0;
}
