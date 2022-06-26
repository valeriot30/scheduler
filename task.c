#include "task.h"

int create_task(task *my_task, int pid, int arrivalTime, int burstTime) {
	(*my_task) = (task) malloc(sizeof(struct task));

	if((*my_task) == NULL) return 1;

	(*my_task)->pid = pid;
	(*my_task)->arrivalTime = arrivalTime;
	(*my_task)->waitingTime = 0;
	(*my_task)->remainingTime = burstTime;
	(*my_task)->state = ACTIVE;

	return 0;
}

void print_task(task task) {
	printf("\t| %d |", task->pid);
	/*printf("\t*------*");
	printf("\t|  %d  |", task->pid);
	printf("\t*------*");*/
}

void print_task_full(task task) {
	printf("\n");

	printf("\t| PID: %d \n", task->pid);
	printf("\t| Tempo rimanente: %ds \n", task->remainingTime);
	printf("\t| Status: %s \n", getStateText(task->state));
}

char* getStateText(State state) {
	switch(state) {
		case SUSPENDED:
			return "Suspended";
		default:		
		case ACTIVE:
			return "Active";
	}
}

int destroy_task(task* task) {
	if((*task) == NULL) return 1;

	free(*task);
	*task = NULL;
	return 0;
}

State get_state(task task) {
	return task->state;
}

int set_state(task task, State state) {
	if(task == NULL) return 1;

	int stateInt = (int) state;

	if(state > 1 || state < 0) {
		return 1;
	}

	task->state = state;
	return 0;
}