#include <stdio.h>
#include <stdlib.h>

#include "state.h"

#ifndef TASK_H
#define TASK_H

#define MAX_TASK_LENGTH 36

#define MAX_TASK_TIME 50000

#define MAX_TASK_PID 99999

struct task {
	int pid;

	int burstTime;

	int remainingTime;

	State state;

	struct task* next;
};

typedef struct task* task;

int create_task(task* task, int pid, int burstTime, int remainingTime);

void calc_waiting_time(int burstTime, int remainingTime);

void print_task(task task); // stampa solo graficamente il processo con all'interno il PID (per lo scheduling)

void print_task_full(task task); // stampa tutti i campi del processo.

int get_pid(task task);

int set_pid(task task, int pid);

int get_time(task task);

int set_time(task* task, int burstTime);

int set_remaining_time(task* task, int remainingTime);

int get_remaining_time(task task);

int destroy_task(task* task);

void execute_task(task* task);

char* getStateText(State state);

State get_state(task task);

int set_state(task task, State state);

void save_task(task task, FILE* f);

#endif