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

#include "Munch1.h"
#include "queue.h"
#include "Reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
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
    //when meet a NULL, enqueue a NULL to the output queue
    EnqueueString(m->out, NULL);
    //then exit
    pthread_exit(NULL);
}
