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

#include "Reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <ctype.h>


//read from stdin
void *Reader(void *arg) {
    const char endline = '\n';
    const char endstr = '\0';
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
            index = input[count];
            free(input);
            if (index!=endline) {
                while ((index=getc(stdin))!=endline){
                    if (index==EOF) {
                        EnqueueString(q, NULL);
                        pthread_exit(NULL);
                    }
                }
            }
            //assign new mem for the pointer
            input = (char *)calloc(BUFF_SIZE,sizeof(char));
            count = 0;
            continue;
        }
        // enqueue the line
        else if(input[count]==endline) {
            input[count]=endstr;
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
