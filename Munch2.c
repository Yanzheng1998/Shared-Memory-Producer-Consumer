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

#include "Munch2.h"
#include "Reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <ctype.h>

void *Munch2(void *args) {
    const char endline = '\n';
    const char endstr = '\0';
    myarg_t *m = (myarg_t *)args;
    char *input;
    input = DequeueString(m->in);
    int count = 0;
    //change the lower case into upper case
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
    //when meet the NULL, enqueue a NULL into the output queue
    EnqueueString(m->out, NULL);
    //then exit
    pthread_exit(NULL);
}
