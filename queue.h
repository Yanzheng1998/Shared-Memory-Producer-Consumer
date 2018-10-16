//
//  queue.h
//  537program2
//
//  Created by Yanzheng Li on 10/15/18.
//  Copyright © 2018 Yanzheng Li. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <semaphore.h>

#endif /* queue_h */

typedef struct Queue
{
    int capacity;
    int size;
    int front;
    int end;
    int enqueueCount;
    int dequeueCount;
    int enqueueBlockCount;
    int dequeueBlockCount;
    pthread_mutex_t lock1;
//    pthread_mutex_t lock2;
    pthread_cond_t enQ;
    pthread_cond_t deQ;
    char** string;
}Queue;

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char *DequeueString(Queue *q);

void PrintQueueStats(Queue *q);

