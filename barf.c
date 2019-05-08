/*
 * Copyright (c) 2019, Nathan Jenne
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int, char**)
{
    struct timespec ts = { 0, 5000000 };
    struct timespec r = {};
    while (1)
    {
        int words = rand() % 12 + 1;
        for (int i = 0; i < words; i++)
        {
            if (i > 0)
            {
                printf(" ");
            }
            printf("%d", rand() % (1 << (rand() % 24)));
        }
        printf("\n");

        nanosleep(&ts, &r);
    }
    return 0;
}

