#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"

#include "state.h"

#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_NLENGTH 36

#define MAX_QUEUE_QUANTUM 320

struct queue {
	char name[MAX_QUEUE_NLENGTH];
	int timeQuantum;
	int size;
	State state;
	struct task* head;
	struct task* tail;
};

typedef struct queue* queue;

task peek(queue queue); // leggi il primo elemento in testa, ma non rimuoverlo

int enqueue(queue queue, task task);

int dequeue(queue queue, task* task);

int clear(queue* queue); // svuota la coda

int is_empty(queue queue); // controlla se la testa e la coda puntano a NULL per verificare che sia vuota 

int size(queue queue); // ritorna la dimensione effettiva della coda

int create_queue(queue* queue, char name[], int timeQuantum);

int destroy_queue(queue* queue);

int kill(queue queue, int pid);

int find(queue queue, int pid, task* task);

void print_queue(queue queue);

int print_queue_full(queue queue);

int set_queue_state(queue queue, State state);
int get_queue_state(queue queue);
int set_name(queue queue, char name[]);
int get_name(queue queue, char name[]);
int get_time_quantum(queue queue);

void increment_size(queue queue);
void decrement_size(queue queue);

void save_queue(queue queue, FILE* f);
void load_queue(queue queue, FILE* f);

#endif
