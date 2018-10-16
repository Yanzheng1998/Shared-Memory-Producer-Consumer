//
//  queue.c
//  537program2
//
//  Created by Yanzheng Li on 10/15/18.
//  Copyright © 2018 Yanzheng Li. All rights reserved.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

Queue *CreateStringQueue(int size) {
    Queue *newQ = (Queue *)malloc(sizeof(Queue));
    if (!newQ) {
        printf("malloc failed, null pointer");
        return NULL;
    }
    newQ->string = (char **)malloc(sizeof(char *)*size);
    if (!newQ->string) {
        printf("malloc failed, null pointer");
        return NULL;
    }
    newQ->capacity = size;
    newQ->lock1 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
//    newQ->lock2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    newQ->enQ = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    newQ->deQ = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    newQ->size = 0;
    newQ->dequeueBlockCount = 0;
    newQ->dequeueCount = 0;
    newQ->enqueueBlockCount = 0;
    newQ->enqueueCount = 0;
    newQ->front = 0;
    newQ->end = -1;
    return newQ;
}

void EnqueueString(Queue *q, char *string) {
    pthread_mutex_lock(&(q->lock1));
    if(q->size == q->capacity) {
        q->enqueueBlockCount++;
        pthread_cond_wait(&(q->enQ),&(q->lock1));
    }
    q->size++;
    q->end++;
    if (q->end == q->capacity) {
        q->end = 0;
    }
    q->string[q->end] = string;
    q->enqueueCount++;
    pthread_mutex_unlock(&(q->lock1));
    pthread_cond_signal(&(q->deQ));
}

char *DequeueString(Queue *q) {
    pthread_mutex_lock(&(q->lock1));
    if(q->size == 0) {
        q->dequeueBlockCount++;
        pthread_cond_wait(&(q->deQ),&(q->lock1)); 
    }
    char *temp = q->string[q->front];
    q->string[q->front] = "";
    q->dequeueCount--;
    q->size--;
    q->front++;
    if (q->front == q->capacity) {
        q->front = 0;
    }
    pthread_mutex_unlock(&(q->lock1));
    pthread_cond_signal(&(q->enQ));
    return temp;
}

void PrintQueueStats(Queue *q) {
    printf("enqueue count: %d\n", q->enqueueCount);
    printf("dequeue count: %d\n", q->dequeueCount);
    printf("enqueueblocked count: %d\n", q->enqueueBlockCount);
    printf("dequeueblocked count: %d\n", q->dequeueBlockCount);
}

