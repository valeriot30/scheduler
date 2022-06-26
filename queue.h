#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"

#include "state.h"

#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_NLENGTH 36

struct queue {
	char name[MAX_QUEUE_NLENGTH];

	int timeQuantum;

	int priority; 

	int size;

	State state;
	
	struct task* head;
	struct task* tail;
};

typedef struct queue* queue;

task peek(queue queue); // leggi il primo elemento in testa, ma non rimuoverlo

int enqueue(queue queue, task task);

void execute(queue queue);

int dequeue(queue queue, task* task);

int clear(queue queue); // svuota la coda

int is_empty(queue queue); // controlla se la testa e la coda puntano a NULL per verificare che sia vuota 

int size(queue queue); // ritorna la dimensione logica della coda

int create_queue(queue* queue, char name[], int priority, int timeQuantum);

int destroy_queue(queue* queue, char queue_name[]);

int kill(queue* queue, int pid);

void print_queue(queue queue);

int print_queue_full(queue queue);

int set_name(queue queue, char name[]);

int get_name(queue queue, char name[]);
int get_time_quantum(queue queue, int* timeQuantum);
int get_priority(queue queue, int* priority);
int set_priority(queue queue, int* priority);

void increment_size(queue queue);
void decrement_size(queue queue);

int set_queue_state(queue queue, State state);



#endif
