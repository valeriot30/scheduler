#include "task.h"

int create_task(task *my_task, int pid, int burstTime, int remainingTime) {
	(*my_task) = (task) malloc(sizeof(struct task));

	if((*my_task) == NULL) return 1;

	(*my_task)->pid = pid;

	(*my_task)->burstTime = burstTime;
	
	(*my_task)->remainingTime = remainingTime;
	(*my_task)->state = ACTIVE;

	return 0;
}

void print_task(task task) {
	printf("\t| %d |", task->pid);
}

void print_task_full(task task) {
	printf("\n");
	printf("\t| PID: %d \n", task->pid);
	printf("\t| Tempo occorrente: %ds \n", task->burstTime);
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
	if(task == NULL) return 1;

	free(*task);
	*task = NULL;
	return 0;
}

// modifica i tempi del processo
void execute_task(task* task) {
	if(task == NULL) return;

	int burstTime = get_time(*task);
	int remainingTime = get_remaining_time(*task);

    (*task)->burstTime++;
    //set_time(task, (burstTime++));
    set_remaining_time(task, (remainingTime--));
}

State get_state(task task) {
	return task->state;
}

int get_time(task task) {
	return task->burstTime;
}

int set_time(task* task, int burstTime) {

	if(*task == NULL) return 1;

	(*task)->burstTime = burstTime;
	return 0;
}

int set_pid(task task, int pid) {
	if(task == NULL) return 1;

	task->pid = pid;
	return 0;
}

int get_pid(task task) {
	if(task == NULL) return -1;

	return task->pid;
}

int get_remaining_time(task task) {
	return task->remainingTime;
}

int set_remaining_time(task* task, int remainingTime) {
	if(*task == NULL) return 1;

	(*task)->remainingTime = remainingTime;
	return 0;
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

void save_task(task task, FILE* f) {

	int pid = get_pid(task);
	int burstTime = get_time(task);
	int remainingTime = get_remaining_time(task);

	fprintf(f, "%d %d %d \n", pid, burstTime, remainingTime);
}

