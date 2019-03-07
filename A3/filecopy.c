/*
 * CS 4540 Assignment #3 - File Copy
 * PROGRAM    : filecopy.c
 * AUTHOR     : Brandon Scott Seager
 * DATE       : 2/18/2018
 * CLASS      : Operating Systems (CS 4540)
 * DESCRIPTION: This program copies a file from one pipe and reads to the other
 */

/*
TO RUN THE Program
make
make test
*/


//ALL Code is Referenced in the References document

#include "init.h"
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
 
int main( int argc, char* argv[] ) {

    int f[2];
    pid_t id;
    char readBuff[50];
    char writeBuff[50];
    int readCounter;
    pipe(f);

    //Open the files with the correct permissions
    int fo = open(argv[1], 0);
    int ft = open(argv[2], 0666);
     
    if (fo == -1 || ft == -1) {
        printf( "Failed Opening That File");
        exit(1);
    }

    id = fork();
 
    if(id == 0) {
        close(f[1]);
        read(f[0], readBuff, sizeof(readBuff));
        write(ft, readBuff, strlen(readBuff) + 1);
	printf("I just wrote your file on its on pipe to the next file");
	exit(1);
    } else {
        close(f[0]);
        while((readCounter = read( fo, readBuff, sizeof(readBuff)) > 0)){
        write(f[1], readBuff, sizeof(readBuff));
        }
        close(f[1]);
    }
}





























