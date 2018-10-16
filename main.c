//
//  main.c
//  queue.c
//
//  Created by Yanzheng Li on 10/15/18.
//  Copyright © 2018 Yanzheng Li. All rights reserved.
//

#include <stdio.h>
#include "queue.h"

int main(int argc, const char * argv[]) {
    Queue* test = CreateStringQueue(10);
    EnqueueString(test, "1213123");
    printf("%d",test->size);
    char * temp = DequeueString(test);
    printf("%d",test->size);
    puts(temp);
    return 0;
}
