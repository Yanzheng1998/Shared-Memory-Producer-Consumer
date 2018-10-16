//
//  main.c
//  queue.c
//
//  Created by Yanzheng Li on 10/15/18.
//  Copyright © 2018 Yanzheng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#define BUFF_SIZE 10

void reader(Queue *q);

int main(int argc, const char * argv[]) {
    Queue* test = CreateStringQueue(10);
    EnqueueString(test, "1213123");
    reader(test);
    printf("%d",test->size);
    char * temp = DequeueString(test);
    temp = DequeueString(test);
    printf("%d",test->size);
    puts(temp);
    free(temp);
    free(test);
    return 0;
}

void reader(Queue *q) {
    char *input = (char *)malloc(BUFF_SIZE*sizeof(char));
    if(!input) {
        printf("malloc failed, null pointer");
        return;
    }
    if (!fgets(input, BUFF_SIZE, stdin)) {
        printf("no inputs");
        return;
    }
    EnqueueString(q, input);
    return;
}
