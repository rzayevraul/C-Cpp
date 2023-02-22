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
//#include <chrono>
//#include <thread>
using namespace std;
int library, numberOfWriters;
pthread_mutex_t mtx;
sem_t roomsOfReaders, roomOfWriters, semid;

void* pisatel(void* arg);
void* chitatel(void* arg);

int main(){
	pthread_t writers[70], readers[3];
	sem_init(&semid, 0, 0);
	sem_init(&roomsOfReaders, 0, 0);
	sem_init(&roomOfWriters, 0, 0);
	pthread_mutex_init(&mtx, NULL);
	for(int id = 0; id < 3; id++){
		pthread_create(&readers[id], NULL, chitatel, &id);
		sem_wait(&semid);
		//sleep(1);
    	//this_thread::sleep_for(chrono::milliseconds(100));
	}
	for(int id = 0; id < 70; id++){
		pthread_create(&writers[id], NULL, pisatel, &id);
		sem_wait(&semid);
	}
	pthread_join(writers[1], NULL);
	return 0;
}

void* pisatel(void* arg){
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
			printf("pisatel %d pishet\n", loc_id);
			sleep(1);
      //this_thread::sleep_for(chrono::milliseconds(200));
			library = 0;
			sem_post(&roomsOfReaders);
			sem_post(&roomOfWriters);
			pthread_mutex_unlock(&mtx);
			sleep(1);
      //this_thread::sleep_for(chrono::milliseconds(500));
		}
	}
	return NULL;
}

void* chitatel(void *arg){
	int loc_id = *(int *)arg;
	sem_post(&semid);
	int ind;
	while(true){
		ind = 0;
		pthread_mutex_lock(&mtx);
		if(library != -1 && numberOfWriters== 0) library++;
		else ind = 1;
		pthread_mutex_unlock(&mtx);
		if(ind == 1) sem_wait(&roomsOfReaders);
		else{
			sem_post(&roomsOfReaders);
			printf("chitatel %d chitaet\n", loc_id);
			sleep(10);
      		//this_thread::sleep_for(chrono::milliseconds(100));
			pthread_mutex_lock(&mtx);
			library--;
			if(library == 0) sem_post(&roomOfWriters);
			pthread_mutex_unlock(&mtx);
			//sleep(1);
		}
	}
	return NULL;
}

