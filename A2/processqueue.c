/*
 * CS 4540 Assignment #2 - Scheduling
 * PROGRAM    : processqueue.c
 * AUTHOR     : Brandon Scott Seager
 * DATE       : 1/28/2018
 * CLASS      : Operating Systems (CS 4540)
 * DESCRIPTION: This program simulates a running operating system's
 * scheduling of processes
 */

/*
TO RUN THE QUEUE
make
make test
*/

#include "init.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define NUM_PROCESSES 5 * 20

int main(int argc, char *argv[]){

	Process processes[NUM_PROCESSES];
	Process_queue *ready_queue;
	Process *proc_arr_ptr;
	proc_arr_ptr = processes;
	int quantum_time = 20;
	clock_t start, end;
     	double cpu_time_used;

	proc_arr_ptr = process_gen_arr(proc_arr_ptr, NUM_PROCESSES, quantum_time);

	if(proc_arr_ptr != NULL){
	  printf("I just Made 100 Processes");
	}
	else{
	  printf("Something Went Wrong");
	}

	proc_arr_ptr = queueInitializeAndStore(ready_queue, proc_arr_ptr, NUM_PROCESSES);

	if(&ready_queue != NULL){
	  printf("I Made The Queue For You And I Stored All The Processes In It By Priority");
	}
	else{
	  printf("Something Went Wrong");
	}
	printf("\n");

	printf("About To Run The Process Loop And Take Items Out Of The Priority Queue");
	printf("\n");
	start = clock();
	int test = runTheProcessLoop(proc_arr_ptr, NUM_PROCESSES);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	double averagePerProcess = cpu_time_used / NUM_PROCESSES;
	
	printf("Time It took for all Processes to Run is %f",cpu_time_used);
	printf("\n");
	printf("Average Time Per Process %f",averagePerProcess);
	printf("\n");
	if(test == 1){
	  printf("Completed");
	}
	else{
	  printf("Something Went Wrong");
	}
        printf("\n");
	
	return 0;
}

void remove_element(Process *array, int index, int array_length)
{
   int i;
   for(i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}

int runTheProcessLoop(Process *arr,int numberOfProcesses){

    int errorCheck;
    for(int i = 0;i < numberOfProcesses;i++){
	//printf("%d",arr[i].priority_starting);
	remove_element(arr,1,numberOfProcesses);
	errorCheck = 0;
    }
    errorCheck = 1;

return errorCheck;
    
}

/*This array generator was referenced*/
Process *
process_gen_arr(Process *arr, int len, int quantum)
{
    int err_num = 1;
    int min_heavy = quantum + 1;
    int heavy, max_rem, remain, even_one, even_two;

    if (arr != NULL) {
        for (int i = 0; i < len; i++) {
            /* Select CPU and I/O times for the "heavy" processes */
            heavy = min_heavy + (rand() % (STATE_MAX + 1 - min_heavy));
            max_rem = (heavy / 3);
            remain = max_rem - (rand() % (max_rem - STATE_MIN + 1));

            /* Select CPU and I/O times for the "even" processes */
            even_one = (quantum / 3) + (rand() % (((quantum * 2) / 3)
                    - (quantum / 3)));
            even_two = even_one + ((rand() % 5) - 2);


            if (i % 3 == 0) {
                arr[i] = process_create(i, (i / 3), heavy, remain);
            }else if (i % 3 == 1) {
                arr[i] = process_create(i, (i / 3), remain, heavy);
            }else{
                arr[i] = process_create(i, (i / 3), even_one, even_two);
            }
        }

        err_num = 0;
    }

    return arr;
}

Process process_create(int id, int priority, int cpu, int io)
{
    /*Create A New Process*/
    Process proc;

    /*Store items in the Struct*/
    char str[10] = "Process";
    strcpy(proc.name, str);
    proc.priority_starting = rand() % 21;
    proc.num = id;
    proc.priority_current = proc.priority_starting;
    proc.cpu_required = cpu;
    proc.io_required = io;
    proc.machine_total = -1;
    proc.cpu_current = 0;
    proc.io_remaining = proc.io_required;
    proc.ready_current = 0;
    proc.cpu_total = 0;
    proc.io_total = 0;
    proc.ready_total = 0;
    proc.ready_shortest = 1;
    proc.ready_longest = 0;
    proc.state_current = -1;

    return proc;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int queue_isfull(Process_queue *queue)
{
    int status;

    if (queue == NULL) {
        status = 0;
    }else{
        status = queue->is_full;
    }

    return status;
}

Process * queueInitializeAndStore(Process_queue *queue, Process *arr, int NUM_OF_PROCESSES)
{

    //CHECK IF QUEUE IS FULL
    int k = queue_isfull(queue);

    if (queue != NULL) {
        queue->is_empty = 1;
        queue->is_full = 0;
        queue->num_elements = 0;
        queue->front = 0;
        queue->back = 0;
    }
     
    //SORT THE PRIORITY QUEUE
    qsort(arr, NUM_OF_PROCESSES, sizeof(Process), cmpfunc);

    printf("\n");
//RETURN THE QUEUE
    return arr;
}






























