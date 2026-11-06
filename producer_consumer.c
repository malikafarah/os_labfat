#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5

int buffer[SIZE];
int in=0,out=0;
pthread_mutex_t mutex;
sem_t empty,full;


void *producer(void *args){
    int item;
    for(int i = 1; i<=10; i++){
        item = i;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        in = (in +1)%SIZE;
        printf("Producer : %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *args){
    int item;
    for(int i = 1; i<=10; i++){
        item = i;
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        buffer[out] = item;
        out = (out+1)%SIZE;
        printf("Consumer: %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main(){
    pthread_t p,c;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}