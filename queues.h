#ifndef QUEUES_H
#define QUEUES_H

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "queue.h"


struct queues {
	queue queue;
	struct queues *next;
};

typedef struct queues* queues;


int create_queues_list(queues *queue_list); // crea la lista, ritorna 1 se qualcosa è andato storto, 0 altrimenti

int destroy_queues(queues* queue_list);

int add_queue(queues* queue_list, char queue_name[], int timeQuantum, queue* queue); // aggiunge una coda alla lista di code, ritorna 2 se il time quantum è elevato, 1 se qualcosa è andato storto, 0 altrimenti

int add_task(queues queue_list, int pid, int burstTime, int remainingTime); // aggiunge un processo alla prima coda, ritorna 3 se il pid è elevato, 2 se esiste già, 1 se qualcosa è andato storto.

int kill_queue(queues* queue_list, char queue_name[]); // elimina una coda, ritorna 2 se qualcosa è andato storto, 1 se la coda non esiste, 0 altrimenti.

queue get_queue(queues queue_list, char queue_name[]); // restituisce una coda

task get_task(queues queue_list, int pid);

void print_queues(queues queue_list); // stampa le code per visualizzare graficamente lo scheduling.

int execute_queue(queues queue_node);

int print_queues_full(queues queue_list); // stampa le code in modo completo, visualizzando tutte le caratteristiche dei processi nelle code.

int is_queue_list_empty(queues queue_list); // controlla se tutte le code sono vuote

int start_executing(queues queue_list); // inizia a schedulare tutte le code 

int kill_task(queues queue_list, char queue_name[], int pid); // uccidi un processo a partire dal nome della coda e dal pid

int toggle_task(queues queue_list, int pid); // attiva/sospendi un processo, ritorna 2 se il processo non esiste, 1 se qualcosa è andato storto, 0 altrimenti.

int toggle_queue(queues queue_list, char queue_name[]); // attiva/sospendi una coda, ritorna 2 se la coda non esiste, 1 se qualcosa è andato storto, 0 altrimenti.

queue get_head_queue(queues queue_list);

int save_data(queues queue_list, char* fileName);

int load_data(queues* queue_list, char* fileName);

#endif