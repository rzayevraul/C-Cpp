#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <semaphore.h>
using namespace std;

int arr[25] = {0}, bul_p = 0,  bul_c = 0, i = 0;
sem_t fr33, taken, semid, sem_binary;

void* producer(void* arg){
	int loc_id = *(int*)arg;
	sem_post(&semid);
	while(bul_p < 100){
		sem_wait(&fr33);
		sleep(rand()%5 + 1);
		bul_p++;
		sem_wait(&sem_binary);
		arr[i] = loc_id;
		i++;
		sem_post(&sem_binary);
		sem_post(&taken);
	}
	return NULL;
}

void* consumer(void* arg){
	int loc_id = *(int*)arg;
	sem_post(&semid);
	while(bul_c < 85){
		sem_wait(&taken);
		sem_wait(&sem_binary);
		cout << "consumer# " << loc_id << " bul# " << arr[i-1] << endl;
		bul_c++;
		i--;
		sem_post(&sem_binary);
		sem_post(&fr33);
	}
	return NULL;
}

int main(void){
	int id;
	sem_init(&fr33, 0, 25);
	sem_init(&taken, 0, 0);
	sem_init(&semid, 0, 0);
	sem_init(&sem_binary, 0, 1);
	pthread_t produce[15], consume[11];
	for(id = 1; id <= 15; id++){
		pthread_create(&produce[id-1], NULL, producer, &id);
		sem_wait(&semid);
	}
	for(id = 1; id <= 11; id++){
		pthread_create(&consume[id-1], NULL, consumer, &id);
		sem_wait(&semid);
	}
	for(id = 1; id <= 15; id++){
		pthread_join(produce[id-1], NULL);
	}
	for(id = 1; id <= 11; id++){
		pthread_join(consume[id-1], NULL);
	}
	return EXIT_SUCCESS;
}
