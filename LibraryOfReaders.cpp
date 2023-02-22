#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <semaphore.h>
#include <algorithm>
#include <time.h>

int library, numberOfWriters;
pthread_mutex_t mtx;
sem_t roomOfReaders, roomOfWriters, semid;

void* writer(void* arg);
void* reader(void* arg);

int main(){
	pthread_t writers[2], readers[14];
	sem_init(&semid, 0, 0);
	sem_init(&roomOfReaders, 0, 0);
	sem_init(&roomOfWriters, 0, 0);
	pthread_mutex_init(&mtx, NULL);
	for(int id = 0; id < 14; id++){
		pthread_create(&readers[id], NULL, reader, &id);
		sem_wait(&semid);
		sleep(1);
	}
	for(int id = 0; id < 2; id++){
		pthread_create(&writers[id], NULL, writer, &id);
		sem_wait(&semid);
	}
	pthread_join(writers[1], NULL);
	return 0;
}

void* writer(void* arg){
	int loc_id = *(int *)arg;
	sem_post(&semid);
	int ind;
	while(true){
		ind = 0;
		pthread_mutex_lock(&mtx);
		if(library == 0) library = -1;
		else{
			ind = 1;
			numberOfWriters++;
			pthread_mutex_unlock(&mtx);
		}
		if(ind == 1){
			sem_wait(&roomOfWriters);
			pthread_mutex_lock(&mtx);
			numberOfWriters--;
			pthread_mutex_unlock(&mtx);
		}
		else{
			printf("writer %d pishet\n", loc_id);
			sleep(2);
			library = 0;
			sem_post(&roomOfReaders);
			sem_post(&roomOfWriters);
			pthread_mutex_unlock(&mtx);
			sleep(3);
		}
	}
	return NULL;
}

void* reader(void *arg){
	int loc_id = *(int *)arg;
	sem_post(&semid);
	int ind;
	while(true){
		ind = 0;
		pthread_mutex_lock(&mtx);
		if(library != -1 /*&& numberOfWriters == 0*/) library++;
		else ind = 1;
		pthread_mutex_unlock(&mtx);
		if(ind == 1) sem_wait(&roomOfReaders);
		else{
			sem_post(&roomOfReaders);
			printf("reader %d chitaet\n", loc_id);
			sleep(7);
			pthread_mutex_lock(&mtx);
			library--;
			if(library == 0) sem_post(&roomOfWriters);
			pthread_mutex_unlock(&mtx);
			sleep(1);
		}
  }
	return NULL;
}
