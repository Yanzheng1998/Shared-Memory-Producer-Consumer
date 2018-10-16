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
#include <ctype.h>
#include "queue.h"

//use getc

#define BUFF_SIZE 1024
#define SPACE 32
#define ASTERISK 42

void reader(Queue *q);
void Munch1(Queue *q, Queue *p);
void Munch2(Queue *q, Queue *p);
void Writer(Queue *q);

int main(int argc, const char * argv[]) {
    Queue* test = CreateStringQueue(10);
    Queue* test2 = CreateStringQueue(10);
    Queue* test3 = CreateStringQueue(10);
    reader(test);
    Munch1(test,test2);
    Munch2(test2,test3);
    Writer(test3);
    free(test);
    free(test2);
    free(test3);
    return 0;
}

void reader(Queue *q) {
    char *input = (char *)malloc(BUFF_SIZE*sizeof(char));
//    char *count = (char *)malloc(BUFF_SIZE*sizeof(char));
    if(!input) {
        printf("malloc failed, null pointer");
        return;
    }
    //fix here, need to throw error message when stdin>BUFF_SIZE
    if (!fgets(input, BUFF_SIZE, stdin)) {
        printf("no inputs");
        return;
    }
//    count = index(input,SPACE);
//    while (count) {
//        count[0] = ASTERISK;
//        count = index(count,SPACE);
//    }
    EnqueueString(q, input);
    free(input);
    return;
}

void Munch1(Queue *q, Queue *p) {
    char *count = (char *)malloc(BUFF_SIZE*sizeof(char));
    char *input = DequeueString(q);
    //check
    count = index(input,SPACE);
    if (!count) {
        printf("There`s no SPACE in this line");
        return;
    }
    while (count) {
        count[0] = ASTERISK;
        count = index(count,SPACE);
    }
    EnqueueString(p, input);
    free(count);
    return;
}

void Munch2(Queue *q, Queue *p) {
    char *input = DequeueString(q);
    //check
    int count = 0;
    while(input[count]!='\0') {
        if(islower(input[count])) {
            input[count] = toupper(input[count]);
        }
        count++;
    }
    EnqueueString(p, input);
    return;
}

void Writer(Queue *q) {
    char *output = DequeueString(q);
    printf("%s",output);
}
