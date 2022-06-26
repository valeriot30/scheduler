#include <stdio.h>
#include <stdlib.h>

#include "state.h"

#ifndef TASK_H
#define TASK_H

#define MAX_TASK_LENGTH 36

struct task {
	int pid;

	int arrivalTime;

	int burstTime;

	int waitingTime;

	int remainingTime;

	State state;

	struct task* next;
};

typedef struct task* task;

int create_task(task* task, int pid, int arrivalTime, int burstTime);

void calc_waiting_time(int burstTime, int remainingTime);

void print_task(task task);

void print_task_full(task task);

int get_pid(task task);

int set_pid(task* task);

int get_time(task task);

int set_time(task* task);

int get_arrival_time(task task);

int get_remaining_time(task task);

int destroy_task(task* task);

char* getStateText(State state);

State get_state(task task);

int set_state(task task, State state);

#endif