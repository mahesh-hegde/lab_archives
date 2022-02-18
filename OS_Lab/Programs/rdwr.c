#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<semaphore.h>
#include<string.h>

char data[40];

sem_t mutex, rw_mutex;
int read_count = 0;

char messages[10][40];

void *writer(void *arg) {
	long int wn = (long int)arg;
	char *s = messages[wn];
	size_t sz = strlen(s);
	sem_wait(&rw_mutex);
	memcpy(data,s,sz + 1); // writing
	printf("Writer %ld Wrote: %s\n", wn, data);
	sem_post(&rw_mutex);
	return NULL;
}

void *reader(void *arg) {
	long int rn = (long int) arg;
	sem_wait(&mutex);
	read_count ++;
	if (read_count == 1) {
		sem_wait(&rw_mutex);
	}
	sem_post(&mutex);
	// Reading
	printf("Reader %ld read: %s\n", rn, data);
	sem_wait(&mutex);
	read_count--;
	if (read_count == 0) sem_post(&rw_mutex);
	sem_post(&mutex);
	return NULL;
}

int main() {
	int nr, nw, i, j;
	pthread_t readers[10], writers[10];
	sem_init(&mutex,0,1);
	sem_init(&rw_mutex,0,1);

	memcpy(data, "(Nothing)", 10);
	printf("Numbers of readers & writers: ");
	scanf("%d %d", &nr, &nw);
	if (nr > 10 || nr <= 0 || nw > 10 || nw <= 0) {
		printf("Enter valid numbers!!\n");
		return 1;
	}

	for (i = 0; i < nw; i++) {
		printf("Data to write from writer %d: ", i);
		scanf(" %38[^\n]", messages[i]);
	}

	for (i = 0; i < nr; i++) {
		pthread_create(&readers[i], NULL, reader, (void *)i);
	}

	for (i = 0; i < nw; i++) {
		pthread_create(&writers[i], NULL, writer, (void *)i);
	}

	for (i = 0; i < nr; i++) {
		pthread_join(readers[i], NULL);
	}
	for (i = 0; i < nw; i++) {
		pthread_join(writers[i], NULL);
	}
}
