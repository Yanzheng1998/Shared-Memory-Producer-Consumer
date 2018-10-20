//
//  main.c
//  queue.c
//  Reader.c
//  Munch1.c
//  Munch2.c
//  writer.c
//
//  Created by Yanzheng Li on 10/15/18.
//  Completed by Yanzheng Li, net id: 9075265638, cs login: yanzheng
//  and Yi Tong net id: 9075617911, cs login: ytong
//  Copyright © 2018 Yanzheng Li. All rights reserved.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//This function initialize the queue;
Queue *CreateStringQueue(int size) {
    Queue *newQ = (Queue *)malloc(sizeof(Queue));
    if (newQ==NULL) {
        fprintf(stderr,"malloc failed, null pointer");
        free(newQ);
        return NULL;
    }
    newQ->string = (char **)malloc(sizeof(char *)*size);
    if (newQ->string==NULL) {
        fprintf(stderr,"malloc failed, null pointer");
        free(newQ->string);
        free(newQ);
        return NULL;
    }
    newQ->capacity = size;
    //initialize the mutex lock;
    newQ->lock1 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    newQ->enQ = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    newQ->deQ = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    newQ->size = 0;
    newQ->dequeueBlockCount = 0;
    newQ->dequeueCount = 0;
    newQ->enqueueBlockCount = 0;
    newQ->enqueueCount = 0;
    //initialize the head and tail pointers of the queue
    newQ->front = 0;
    newQ->end = -1;
    return newQ;
}

//implement enqueue
void EnqueueString(Queue *q, char *string) {
    //enter critical seciton
    pthread_mutex_lock(&(q->lock1));
    //if the queue if full, wait for space
    if(q->size == q->capacity) {
        q->enqueueBlockCount++;
        pthread_cond_wait(&(q->enQ),&(q->lock1));
    }
    q->size++;
    q->end++;
    //keep a circle manner
    if (q->end == q->capacity) {
        q->end = 0;
    }
    //assign the value after the tail of the queue
    if (((q->string)[q->end] = string)!=NULL)
        q->enqueueCount++;
    //signal there is element in queue
    pthread_cond_signal(&(q->deQ));
    pthread_mutex_unlock(&(q->lock1));

}

//implement dequeue
char *DequeueString(Queue *q) {
    //enter critical section
    pthread_mutex_lock(&(q->lock1));
    //if it is empty, wait until it has valid element
    if(q->size == 0) {
        q->dequeueBlockCount++;
        pthread_cond_wait(&(q->deQ),&(q->lock1));
    }
    //assign the head pointer to the return value
    char *temp = q->string[q->front];
        if (temp!=NULL) {
            q->dequeueCount++;
        }
    //set the front to NULL
    q->string[q->front] = NULL;
    q->size--;
    //keep a circle manner of the queue
    q->front++;
    if (q->front == q->capacity) {
        q->front = 0;
    }
    //signal that there is space in queueu
    pthread_cond_signal(&(q->enQ));
    pthread_mutex_unlock(&(q->lock1));
    return temp;
}

void PrintQueueStats(Queue *q) {
    printf("enqueue count: %d\n", q->enqueueCount);
    printf("dequeue count: %d\n", q->dequeueCount);
    printf("enqueueblocked count: %d\n", q->enqueueBlockCount);
    printf("dequeueblocked count: %d\n", q->dequeueBlockCount);
}

