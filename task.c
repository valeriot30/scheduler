#include "task.h"

int create_task(task *task, int pid, char name[], int arrivalTime, int burstTime) {
	(*task) = malloc(sizeof(task));

	if((*task) == NULL) { return 1;}

	(*task)->pid = pid;
	(*task)->arrivalTime = arrivalTime;
	(*task)->waitingTime = 0;
	(*task)->remainingTime = burstTime;
	//(*task)->name = name;

	return 0;
}

void print_task(task task) {
	printf("%d | %s, %d", task->pid, task->name, task->state);
}