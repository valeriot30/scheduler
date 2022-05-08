#include <stdio.h>
#include <stdlib.h>

#include "state.h"

#ifndef TASK_H
#define TASK_H

#define MAX_TASK_LENGTH 36

struct task {
	int pid;
	char name[MAX_TASK_LENGTH];

	int arrivalTime;
	int burstTime;
	int waitingTime;
	int remainingTime;

	State state;

	struct task* next;
};

typedef struct task* task;

int create_task(task* task, int pid, char name[], int arrivalTime, int burstTime);

void calcWaitingTime(int burstTime, int remainingTime);

void print_task(task task);

int get_pid(task task);

int set_pid(task* task);

int get_time(task task);

int set_time(task* task);

#endif