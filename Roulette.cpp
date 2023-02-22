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

sem_t firstDoor, secondDoor, semid;
int amount = 20, aliveLeft = 0, indicator = 1;
pthread_mutex_t mtx;

void * guardian(void * arg);

int main() {
    srand(time(NULL));
    pthread_t guardians[20];
    sem_init( & firstDoor, 0, 20);
    sem_init( & secondDoor, 0, 0);
    for (int id = 0; id < 20; id++) {
        pthread_create( & guardians[id], NULL, guardian, & id);
        sem_wait( & semid);
    }
    for (int i = 0; i < 20; i++)
        pthread_join(guardians[i], NULL);
    if (indicator != 0) printf("all dead\n");
    return 0;
}

void * guardian(void * arg) {
    //this_thread::sleep_for(chrono::milliseconds(50));
    int loc_id = * (int * ) arg;
    sem_post( & semid);
    while (indicator != 0) {
        sem_wait( & firstDoor);
        int result = rand() % 7;
        pthread_mutex_lock( & mtx);
        amount--;
        if (result != 0) { //survived
            //printf("%d survived\n", loc_id);
            aliveLeft++;
        }
        if (amount == 0) { //last one
            //printf("\next round\n\n");
            amount = aliveLeft;
            for (int i = 0; i < aliveLeft; i++)
                sem_post( & secondDoor);
        }
        if (result == 0) { //dead
            printf("%d dead\n", loc_id);
            pthread_mutex_unlock( & mtx);
            return NULL;
        }
        pthread_mutex_unlock( & mtx);

        sem_wait( & secondDoor);
        pthread_mutex_lock( & mtx);
        printf("%d survived\n", loc_id);
        if (amount == 1) indicator = 0;
        aliveLeft--;
        if (aliveLeft == 0) { //last one
            for (int i = 0; i < amount; i++)
                sem_post( & firstDoor);
            printf("\next round\n\n");
        }
        pthread_mutex_unlock( & mtx);
    }
    printf("%d won\n", loc_id);
    return NULL;
}