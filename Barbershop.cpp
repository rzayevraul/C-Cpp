#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <semaphore.h>
using namespace std;

pthread_mutex_t chair;
sem_t frontDoor, sofa, barberIsWaiting, semid, clientIsWaiting;

void *barber(void *arg);
void *client(void *arg);

int main(){
	sem_init(&frontDoor, 0, 10);
	sem_init(&sofa, 0, 3);
	sem_init(&barberIsWaiting, 0, 0);
	sem_init(&semid, 0, 0);
	sem_init(&clientIsWaiting, 0, 0);
	pthread_t clients[60];
	pthread_t barber_t;
	pthread_mutex_init(&chair, NULL);
	pthread_create(&barber_t, NULL, barber, NULL);
	for(int id = 1; id <= 60; id++){
		pthread_create(&clients[id - 1], NULL, client, &id);
		sem_wait(&semid);
	}
	for(int id = 1; id <= 60; id++){
		pthread_join(clients[id - 1], NULL);
		printf("%d has ended\n", id);
	}
	return EXIT_SUCCESS;
}

void *barber(void *arg){
	while(true){
		sem_wait(&barberIsWaiting);
		sleep(2);
		sem_post(&clientIsWaiting);
	}
	return NULL;
}

void *client(void *arg){
	int loc_id = *(int*)arg;
	sem_post(&semid);
	sem_wait(&frontDoor);
	sem_wait(&sofa);
	sem_post(&frontDoor);
	pthread_mutex_lock(&chair);
	sem_post(&sofa);
	sem_post(&barberIsWaiting);
	sleep(1);
	printf("%d is getting a haircut\n", loc_id);
	sem_wait(&clientIsWaiting);
	pthread_mutex_unlock(&chair);
	return NULL;
}
