#ifndef QUEUES_H
#define QUEUES_H

#include "queue.h"


struct queues {
	queue queue;
	struct queues *next;
};

typedef struct queues* queues;


int create_queues_list(queues *queues); // crea la lista

int add_queue(queues* queues, char queue_name[], int priority, int timeQuantum); // aggiunge una coda alla lista di code

int add_task(queues queues, int pid, int burstTime, int remainingTime); // aggiunge un processo alla prima coda

int move_task(queues queues, task task); // muove un processo alla coda successiva

int kill_queue(queues* queues, char queue_name[]); // elimina una coda

queue get_queue(queues queues, char queue_name[]); // restituisce una coda

task get_task(queues queue_list, int pid);

void print_queues(queues queue_list);

int print_queues_full(queues queue_list);

int is_queue_list_empty(queues queue_list); // controlla se tutte le code sono vuote

int start_executing(queues queue_list); // inizia a schedulare tutte le code 

int is_queue_empty(queues queue_list, char queue_name[]);

int execute_queue(queues queue_node);

int kill_task(queues* queue_list, char queue_name[], int pid);

int toggle_task(queues queue_list, int pid);

int toggle_queue(queues queue_list, char queue_name[]);

#endif