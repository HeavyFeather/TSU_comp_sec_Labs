#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define ERROR_CREATE_THREAD -11
#define SUCCESS        0
#define ERROR_JOIN_THREAD -12

typedef enum
{
    false,
    true
} bool;

struct monitor_t {
	pthread_cond_t cond;
	pthread_mutex_t lock;
	bool ready;
	char symb;
};

typedef struct monitor_t Monitor;

Monitor monitor = {PTHREAD_COND_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, false, 0};

void* provide(void* arg) {
	while (1) {
		char current = 43;

		pthread_mutex_lock(&monitor.lock);
		
		if (monitor.ready) {
			pthread_mutex_unlock(&monitor.lock);
			continue;
		}
		
		monitor.symb = current;
		monitor.ready = true;
		for (int i = 0; i < 5; i++) 
		{
			printf("%c", monitor.symb);
		}
		printf("\nprovider itteration end\n");
		sleep(1);

		pthread_cond_signal(&monitor.cond);
		pthread_mutex_unlock(&monitor.lock);
	}
}

void* consume(void* arg) {
	while (1) {
		char current = 45;

		pthread_mutex_lock(&monitor.lock);

		while (monitor.ready == false) {
			pthread_cond_wait(&monitor.cond, &monitor.lock);
		}

		monitor.symb = current;
		monitor.ready = false;
		for (int i = 0; i < 5; i++) 
		{
			printf("%c", monitor.symb);
		}
		printf("\nconsumer itteration end\n");
		sleep(1);

		pthread_mutex_unlock(&monitor.lock);
	}
}

int main() {
	pthread_t provider;
	pthread_t consumer;

	int status = 0;

	status = pthread_create(&provider, NULL, provide, NULL);
	if (status != 0) {
		printf("main error: can't create thread\n");
		return ERROR_CREATE_THREAD;
	}

	status = pthread_create(&consumer, NULL, consume, NULL);
	if (status != 0) {
		printf("main error: can't create thread\n");
		return ERROR_CREATE_THREAD;
	}

	pthread_join(provider, NULL);
	if (status != SUCCESS) {
		printf("main error: can't join thread\n");
		return ERROR_JOIN_THREAD;
	}

	pthread_join(consumer, NULL);
	if (status != SUCCESS) {
		printf("main error: can't join thread\n");
		return ERROR_JOIN_THREAD;
	}
	return 0;
}