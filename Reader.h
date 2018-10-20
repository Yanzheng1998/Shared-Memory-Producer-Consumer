//
//  Reader.h
//  537program2
//
//  Created by Yanzheng Li on 10/19/18.
//  Copyright © 2018 Yanzheng Li. All rights reserved.
//

#ifndef Reader_h
#define Reader_h

#include <stdio.h>
#include "queue.h"

#endif /* Reader_h */

#define BUFF_SIZE 1024
#define SPACE 32
#define ASTERISK 42

//used as parameter for munch1 and munch2
typedef struct myarg_t{
    Queue *in;
    Queue *out;
} myarg_t;

void *Reader(void *arg);
