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
#include <chrono>
#include <thread>
using namespace std;

pthread_mutex_t forks[5];
sem_t semid, wink;

void *philosopher(void *arg);
void *glutton(void *arg);
int main(){
	srand(time(NULL));
	pthread_t people[5];
	sem_init(&semid, 0, 0);
	sem_init(&wink, 0, 0);
	for(int i = 0; i < 5; i++)
		pthread_mutex_init(&forks[i], NULL);
	int id = 1;
	pthread_create(&people[1], NULL, glutton, &id);
	sem_wait(&semid);
	sem_wait(&wink);
	//sleep(1);
  this_thread::sleep_for(chrono::milliseconds(100));
	id = 0;
	pthread_create(&people[0], NULL, philosopher, &id);
	sem_wait(&semid);
	for(id = 2; id < 5; id++){
		if(id%2 == 0){
      this_thread::sleep_for(chrono::milliseconds(500));
			pthread_create(&people[id], NULL, philosopher, &id);
			sem_wait(&semid);
		}
		else{
      sleep(2);
			pthread_create(&people[id], NULL, glutton, &id);
			sem_wait(&semid);
		}
	}
	pthread_join(people[2], NULL);
}

void *philosopher(void *arg){
	int loc_id = *(int*)arg;
	sem_post(&semid);
	int hunger_lvl = 0, attempts, try_res, v1 = loc_id, v2 = (loc_id +1)%5;
	while(true){
		//sleep(1);
    	this_thread::sleep_for(chrono::milliseconds(100));
		try_res = 666; attempts = 20;
		pthread_mutex_lock(&forks[v1]);
		while(attempts--){
      		this_thread::sleep_for(chrono::milliseconds(20));
      		//printf("attempts = %d\n #%d", attempts, loc_id);
			try_res = pthread_mutex_trylock(&forks[v2]);
			if(try_res == 0) break;
		}
		if(try_res == 0){
			hunger_lvl = 0;
			printf("philosopher %d is eating\n", loc_id);
			//sleep(1);
      		this_thread::sleep_for(chrono::milliseconds(100));
			pthread_mutex_unlock(&forks[v2]);
			pthread_mutex_unlock(&forks[v1]);
      		//this_thread::sleep_for(chrono::milliseconds(1000));
		}
		else{
			//sleep(1);
      		//this_thread::sleep_for(chrono::milliseconds(100));
			hunger_lvl++;
			pthread_mutex_unlock(&forks[v2]);
			swap(v1, v2);
			printf("philosopher %d is starving %d times\n", loc_id, hunger_lvl);
      		//sleep(1);
      		this_thread::sleep_for(chrono::milliseconds(100));
		}
		if(hunger_lvl == 20){
			printf("philosopher %d has dead\n", loc_id);
			//sleep(1);
      		this_thread::sleep_for(chrono::milliseconds(100));
			return NULL;
		}
	}
	return NULL;
}

void *glutton(void *arg){
	int loc_id = *(int*)arg;
	sem_post(&semid);
	while(true){
		//sleep(1); 
		this_thread::sleep_for(chrono::milliseconds(100));
		pthread_mutex_lock(&forks[loc_id]);
		pthread_mutex_lock(&forks[(loc_id + 1)%5]);
		sem_post(&wink);
		printf("glutton %d is eating\n", loc_id);
		//sleep(1);
		this_thread::sleep_for(chrono::milliseconds(100));
		printf("glutton %d finished eating\n", loc_id);
		sem_wait(&wink);
		pthread_mutex_unlock(&forks[(loc_id + 1)%5]);
		pthread_mutex_unlock(&forks[loc_id]);
		//sleep(5);
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	return NULL;
}
