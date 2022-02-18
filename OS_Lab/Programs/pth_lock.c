#include<stdio.h>
#include<pthread.h>

int main() {
	pthread_mutex_t lock;
	pthread_mutex_lock(&lock);
	pthread_mutex_unlock(&lock);
	return 0;
}
