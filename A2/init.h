#define PROCESS_H

#define PROC_NAME_LEN 16

#define STATE_MIN 3
#define STATE_MAX 80

typedef struct {
    char name[PROC_NAME_LEN];
    int num;
    int priority_starting;
    int priority_current;
    int cpu_required;     
    int io_required;       
    int machine_total;     
    int cpu_current;      
    int io_remaining;      
    int ready_current;     
    int cpu_total;        
    int io_total;          
    int ready_total;       
    int ready_shortest;    
    int ready_longest;     
    int state_current;
} Process;

#define QUEUE_SIZE 200

typedef struct {
    int is_empty;
    int is_full;
    int front;
    int back;
    int num_elements;

    Process array[QUEUE_SIZE];
} Process_queue;

Process * queueInitializeAndStore(Process_queue *queue, Process *arr, int NUM_OF_PROCESSES);
int queue_isempty(Process_queue *queue);
int queue_isfull(Process_queue *queue);
int runTheProcessLoop(Process *arr,int NUM_PROCESSES);
int queue_add(Process_queue *queue, int len, Process proc);
Process * process_gen_arr(Process *arr, int len, int quantum);
Process process_create(int id, int priority, int cpu, int io);







