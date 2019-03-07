/*
 * CS 4540 Assignment #4 - PRODUCER AND CONSUMER PROGRAM
 * PROGRAM    : a4.c
 * AUTHOR     : Brandon Scott Seager
 * DATE       : 3/12/2018
 * CLASS      : Operating Systems (CS 4540)
 * DESCRIPTION: This program is the matrix multiplication project
 */
//All items in this program are referenced in a seprate reference document
/*
TO RUN THE Program
make
make test
*/

#include "init.h"
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h>
#include <unistd.h>
#define sizeOfBuffer 5

int mutex = 1;
int full = 0;
int empty = sizeOfBuffer;
int x = 0;
int putToSleep();
//create buffer with set size
int buffer[sizeOfBuffer];
int wait();

int main(int argc, char *argv[]) {

    int n;
    void producer();
    void consumer();

    printf("\nPress 1 to Produce\nPress 2 to Consume\nPress 3 to Exit");
    do{
        printf("\nEnter your choice:");
        scanf("%d",&n);
        switch(n)
        {
            case 1:    if((mutex==1)&&(empty!=0))
                        producer();
                    else
                        printf("Buffer is full!!");
                    break;
            case 2:    if((mutex==1)&&(full!=0))
                        consumer();
                    else
                        printf("Buffer is empty!!");
                    break;
            case 3:
                    exit(0);
                    break;
        }
    }while(1);
    return 0;
}

void producer()
{
    int r = rand() % 100;
    printf("time to sleep \n");
    putToSleep(r);
    mutex = --mutex;
    full = ++full;
    empty = --empty;
    x++;
    printf("Putting number into buffer");
    //putting random number in buffer
    buffer[x] = r;
    printf("\nI have produced 1 item we now have %d items",x);
    mutex = ++mutex;
}

void consumer()
{
    int r = rand() % 100;
    printf("time to sleep");
    putToSleep(r);
    mutex = --mutex;
    full = --full;
    empty = ++empty;
    printf("Taking number out of buffer");
    //taking number out of buffer
    buffer[x] = 0;
    printf("\nI have consumed 1 item we now have %d items",x);
    x--;
    mutex = ++mutex;
}

int putToSleep(int randomNumber){
 wait(randomNumber);
}
