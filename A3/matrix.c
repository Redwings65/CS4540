/*
 * CS 4540 Assignment #3 - Matrix
 * PROGRAM    : filecopy.c
 * AUTHOR     : Brandon Scott Seager
 * DATE       : 2/18/2018
 * CLASS      : Operating Systems (CS 4540)
 * DESCRIPTION: This program is the matrix multiplication project
 */

/*
TO RUN THE Program
make
make run
*/

#include "init.h"
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
 
//LIke OUR Assignment Explains it!! ALL Code is Referenced in the References document
#define M 3
#define K 2
#define N 3
#define NUM_THREADS 10

int A [M][K] = { {1,4}, {2,5}, {3,6} };
int B [K][N] = { {8,7,6}, {5,4,3} };
int C [M][N];

int main(int argc, char *argv[]) {

   printf("This Program will use data described in the Readme for Input");
   printf("\n");
   int i,j, count = 0;
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         struct rc *data = (struct rc *) malloc(sizeof(struct rc));
         data->row = i;
         data->column = j;
         pthread_t tid;
         pthread_attr_t attr;
         pthread_attr_init(&attr);
         pthread_create(&tid,&attr,threadControl,data);
         pthread_join(tid, NULL);
         count++;
      }
   }
   printf("This Is The Output of The Multiplication");
   printf("\n");
   //Print the Result
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
}

void *threadControl(void *param) {
   struct rc *data = param;
   int n;
   int total = 0;
   for(n = 0; n< K; n++){
      total += A[data->row][n] * B[n][data->column];
   }
   C[data->row][data->column] = total;
   pthread_exit(0);
}

