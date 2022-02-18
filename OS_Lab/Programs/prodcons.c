#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<assert.h>

#define MAX 5

sem_t empty, full, mutex;

int pt, ct;

typedef struct queue {
	int items[MAX];
	int size, begin;
} Queue;

Queue *q;

int dequeue(Queue *q) {
	int r;
	if (q->size == 0) return -1;

	r = q->items[q->begin];
	q->size--;
	q->begin++;
	if(q->begin == MAX) q->begin = 0;
	return r;
}

int enqueue(Queue *q, int i) {
	if (q->size == MAX) {
		// Queue Full
		return -1;
	}
	q->items[(q->begin+q->size) % MAX] = i;
	q->size++;
	return 0;
}

void *prod(void *arg) {
	int pn = (int) arg;
	int i;
	for(i = 0; i < ct; i++) {
		sem_wait(&empty);
		sem_wait(&mutex);
		printf("Prod %d produced %d\n", pn, pn*10+i);
		enqueue(q, pn*10+i);
		sem_post(&mutex);
		sem_post(&full);
	}
	return NULL;
}

void *cons(void *arg) {
	int cn = (int) arg;
	int i, n;
	for (i = 0; i < pt; i++) {
		sem_wait(&full);
		sem_wait(&mutex);
		printf(" Cons %d consumed %d\n", cn, dequeue(q));
		sem_post(&mutex);
		sem_post(&empty);
	}
	return NULL;
}

int main() {
	Queue qm;
	int i;
	pthread_t prods[10], conss[10];
	qm.size = 0;
	q = &qm;
	sem_init(&full,0,0);
	sem_init(&mutex,0,1);
	sem_init(&empty,0,MAX);
	printf("Number of producers & consumers: ");
	scanf("%d %d", &pt, &ct);
	assert(pt <= 10 && ct <= 10);

	for(i = 0; i < pt; i++) {
		pthread_create(&prods[i], NULL, prod, (void *)i);
	}

	for(i = 0; i < ct; i++) {
		pthread_create(&conss[i], NULL, cons, (void *)i);
	}

	for(i = 0; i < pt; i++) {
		pthread_join(prods[i], NULL);
		pthread_join(conss[i], NULL);
	}

	return 0;
}
