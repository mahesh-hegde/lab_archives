// Implement a circular queue

#include<stdio.h>
#include<stdlib.h>

#define MAX 4

enum queue_error {NONE, UNDERFLOW, OVERFLOW};

enum queue_error error = NONE;

typedef struct queue {
	int size, begin;
	char *array[MAX];
} Queue;

void enqueue(Queue *q, char *s) {
	if (q->size == MAX) {
		error = OVERFLOW;
		return;
	}
	q->array[(q->begin + q->size) % MAX] = s;
	q->size++;
}

// Returns null if no messages are left

char *dequeue(Queue *q) {
	char *to_ret = NULL;
	if (q->size == 0) {
		error = UNDERFLOW;
		return NULL;
	}

	to_ret = q->array[q->begin];

	q->begin++;
	q->size--;
	if (q->begin == MAX) { q->begin = 0; }
	return to_ret;
}

void print_queue(Queue *q) {
	int i;
	printf("\e[33;1m[Queue State] ");
	printf("q->size=%d,  ", q->size);
	printf("q->begin=%d, elements: ", q->begin);
	for (i=0;i<q->size;i++) {
		printf("\"%s\" ", q->array[(q->begin + i) % MAX]);
	}
	if(q->size == 0) printf("<None>");
	printf("\e[0m\n");
}

void push_msg(Queue *q) {
	error = NONE;
	char *msg = malloc(32*sizeof(char));
	size_t sz = 0;
	printf("Enter message: ");
	scanf(" %30[^\n]", msg);
	enqueue(q, msg);

	if (error == OVERFLOW) {
		printf("\e[31;1mQueue Overflow!!\e[0m\n\n");
	}
}

void print_msg(Queue *q) {
	char *msg = dequeue(q);
	if (msg) {
		printf("\e[32;1mMessage: %s\e[0m\n\n", msg);
		free(msg);
	} else {
		printf("\e[32;1mNo new messages\e[0m\n\n");
	}
	fflush(stdout);
}

int main() {
	int choice;
	Queue q;
	q.size = 0; q.begin = 0;
	while(1) {
		print_queue(&q);
		printf("0: exit    ");
		printf("1: Insert a Message    ");
		printf("2: Read a message    ");
		printf("3: Print the queue\n");
		scanf("%u", &choice);
		switch(choice) {
		case 0: return 0;
		case 1: push_msg(&q);
			break;
		case 2: print_msg(&q);
			break;
		case 3: print_queue(&q);
			break;
		default: printf("Invalid Choice\n");
			return 10;
		}
	}
	return 0;
}
