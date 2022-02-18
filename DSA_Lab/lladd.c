#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


Node *node(int val, Node *next) {
    Node *nd = (Node *)malloc(sizeof(Node));
    nd->val = val;
    nd->next = next;
    return nd;
}

Node *read_list() {
    int n;
    Node *header = node(-1,NULL);
    Node *cur = header;
	// prepending successive digits
	// Essentially our input lists will be in reverse format.
    while(isdigit(n = getchar())) {
        cur = node(n - '0', cur);
    }

    header->next = cur;
    return header;
}

int val(Node *nd, Node *h) {
    return (nd == h) ? 0 : nd->val;
}

Node *add(Node *ah, Node *bh) {
	int carry = 0;
	Node *a = ah->next, *b = bh->next;
	Node *sumh = node(-1,NULL), *sum;
	sumh->next = sumh; // self loop
	sum = sumh;
	while( a != ah || b != bh) {
		int dsum = val(a, ah) + val(b, bh) + carry;
		sum = node(dsum % 10, sum);
		carry = dsum / 10;
		if (a != ah) a = a->next;
		if (b != bh) b = b->next;
	}
	if (carry != 0) sum = node(carry, sum);
	sumh->next = sum;
	return sumh;
}

void print_result(Node *numh) {
    Node *num = numh->next;
    while(num != numh) {
        printf("%d", num->val);
        num = num->next;
    }
    printf("\n");
}

int main () {

	Node *a, *b, *ans;
    printf("Enter an expression: ");
    a = read_list();

	if(scanf("+ ") != 0) {
        fprintf(stderr, "Invalid Input\n");
        return 1;
    }

    b = read_list();
    ans = add(a,b);
    print_result(ans);
    return 0;
}
