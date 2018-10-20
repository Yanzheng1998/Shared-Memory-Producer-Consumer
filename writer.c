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

#include "writer.h"
#include "queue.h"
#include "Reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *Writer(void *q) {
    char *output;
    output = DequeueString(q);
    while (output!=NULL){
        printf("%s\n",output);
        //free after display it;
        free(output);
        //get next line
        output = DequeueString(q);
    }
    //when meet the NULL exit
    pthread_exit(NULL);
}
