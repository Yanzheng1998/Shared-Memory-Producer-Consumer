//
//  main.c
//  queue.c
//
//  Created by Yanzheng Li on 10/15/18.
//  Copyright © 2018 Yanzheng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <ctype.h>
#include "queue.h"

#define BUFF_SIZE 1024
#define SPACE 32
#define ASTERISK 42

const char endline = '\n';
const char endstr = '\0';

//used as parameter for munch1 and munch2
typedef struct myarg_t{
    Queue *in;
    Queue *out;
} myarg_t;

void *Reader(void *q);
void *Munch1(void *arg);
void *Munch2(void *arg);
void *Writer(void *q);

int main() {
    //create 3 queues
    Queue* q1 = CreateStringQueue(10);
    Queue* q2 = CreateStringQueue(10);
    Queue* q3 = CreateStringQueue(10);
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
    //for better readability
    printf("%c",endline);
    //print stats
    PrintQueueStats(q1);
    PrintQueueStats(q2);
    PrintQueueStats(q3);
    free(q1);
    free(q2);
    free(q3);
    return 0;
}

//read from stdin
void *Reader(void *arg) {
    int count = 0;
    Queue *q = (Queue *)arg;
    char *input = (char *)calloc(BUFF_SIZE,sizeof(char));
    char index = SPACE;
    //repeatedly read one char from stdin until EOF read
    while ((input[count]=getc(stdin))!=EOF) {
        //if the line exceed buffersize,dicard it
        if(count>BUFF_SIZE-1) {
            fprintf(stderr, "This line exceeds the max length, dicarded.\n");
            //the line discarded, so it should be freed here.
            free(input);
            while ((index=getc(stdin))!=endline){
                if (index==EOF) {
                    EnqueueString(q, NULL);
                    pthread_exit(NULL);
                }
            }
            //assign new mem for the pointer
            input = (char *)calloc(BUFF_SIZE,sizeof(char));
            count = 0;
            continue;
        }
        // enqueue the line
        else if(input[count]==endline) {
            EnqueueString(q, input);
            input = (char *)calloc(BUFF_SIZE,sizeof(char));
            count = 0;
            continue;
        }
        count++;
    }
    //check if the first char of the file is EOF
    if (count!=0){
        input[count] = endstr;
        EnqueueString(q, input);
    }
    EnqueueString(q, NULL);
    pthread_exit(NULL);
}

//change the space in the content read from stdin to asterisk
void *Munch1(void *arg) {
    char *count;
    myarg_t *m = (myarg_t *) arg;
    //get a line  read by reader from queue
    char *input = DequeueString(m->in);
    while (input!=NULL) {
        count = index(input,SPACE);
        while (count!=NULL) {
            count[0] = ASTERISK;
            count = index(count,SPACE);
        }
        EnqueueString(m->out, input);
        input = DequeueString(m->in);
    }
    EnqueueString(m->out, NULL);
    pthread_exit(NULL);
}

void *Munch2(void *args) {
    myarg_t *m = (myarg_t *)args;
    char *input = DequeueString(m->in);
    //check
    int count = 0;
    while(input!=NULL) {
        while(input[count]!=endstr && input[count]!=endline) {
            if(islower(input[count])) {
                input[count] = toupper(input[count]);
            }
            count++;
        }
        count = 0;
        EnqueueString(m->out, input);
        input = DequeueString(m->in);
    }
    EnqueueString(m->out, NULL);
    pthread_exit(NULL);
}

void *Writer(void *q) {
    char *output;
    output = DequeueString(q);
    while (output!=NULL){
        printf("%s",output);
        fflush(stdout);
        free(output);
        output = DequeueString(q);
    }
    pthread_exit(NULL);
}
