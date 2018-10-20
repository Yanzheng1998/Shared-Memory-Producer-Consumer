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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "Reader.h"
#include "writer.h"
#include "Munch1.h"
#include "Munch2.h"

int main() {
    //create 3 queues
    int size_q = 10;
    Queue* q1 = CreateStringQueue(size_q);
    Queue* q2 = CreateStringQueue(size_q);
    Queue* q3 = CreateStringQueue(size_q);
    //initialize the parameter for m1 and m2
    myarg_t m1 = {q1, q2};
    myarg_t m2 = {q2, q3};
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    //initialize 4 threads
    int err;
    err = pthread_create(&thread1, NULL, Reader, (void *)q1);
    if (err!=0) {
        fprintf(stderr,"thread1 creation failed");
    }
    err = pthread_create(&thread2, NULL, Munch1, (void *)&m1);
    if (err!=0) {
        fprintf(stderr,"thread2 creation failed");
    }
    err = pthread_create(&thread3, NULL, Munch2, (void *)&m2);
    if (err!=0) {
        fprintf(stderr,"thread3 creation failed");
    }
    err = pthread_create(&thread4, NULL, Writer, (void *)q3);
    if (err!=0) {
        fprintf(stderr,"thread4 creation failed");
    }
    // wait for threads to end
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    //print stats
    PrintQueueStats(q1);
    PrintQueueStats(q2);
    PrintQueueStats(q3);
    free(q1);
    free(q2);
    free(q3);
    return 0 ;
}

