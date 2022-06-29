
#include "queues.h"

int create_queues_list(queues* queues_list) {
	(*queues_list) = NULL;
	return 0;
}

void print_queues(queues queue_list) {

	while(queue_list != NULL) {
		print_queue(queue_list->queue);
		queue_list = queue_list->next;
	}
}

int print_queues_full(queues queue_list) {

	if(queue_list == NULL) return 1;

	while(queue_list != NULL) {
		print_queue_full(queue_list->queue);
		printf("\n");
		queue_list = queue_list->next;
	}

	return 0;
}

int add_queue(queues* queue_list, char queue_name[], int priority, int timeQuantum) {
	queues new_queue;

	new_queue = (queues)malloc(sizeof(struct queues));

	if(new_queue == NULL) return 1;

	int result = create_queue(&(new_queue->queue), queue_name, priority, timeQuantum);

	if(result == 1) {
		free(new_queue);
		return 1;
	}

	new_queue->next = *queue_list;
	*queue_list = new_queue;
	return 0;

}

int add_task(queues queue_list, int pid, int burstTime, int remainingTime) {


	if(queue_list == NULL) return 2;

	task task;
	
	int result = create_task(&task, pid, burstTime, remainingTime);

	if(result == 1) {
		free(task);
		return 1;
	}

	int enqueueResult = enqueue(queue_list->queue, task);

	if(enqueueResult == 1) return 2;

	return 0;

}

task get_task(queues queue_list, int pid) {
	
	if(queue_list == NULL) return NULL;

	task t = queue_list->queue->head;

	if(t == NULL) return NULL;

	while(queue_list != NULL && t != NULL) {
		
		if(t->pid == pid) {
			return t;
		}

		t = queue_list->queue->head;
		queue_list = queue_list->next;
	}

	//free(t);

	return NULL;
}

queue get_queue(queues queue_list, char queue_name[]) {
	if(queue_list == NULL) return NULL;

	while(queue_list != NULL) {

		if(strcmp(queue_list->queue->name, queue_name) == 0) {
			return queue_list->queue;
		}

		queue_list = queue_list->next;
	}

	return NULL;
}

int move_task(queues queue_list, task taskToMove) {

	task newTask;

	if(queue_list == NULL) return 1;

	if(taskToMove == NULL) return 1;

	//TODO should use getters 

	int result = create_task(&newTask, taskToMove->pid, taskToMove->burstTime, taskToMove->remainingTime);


	if(result == 1) {
		free(newTask);
		return 1;
	}

	if(queue_list->next == NULL) {
		destroy_task(&newTask);
		return 1;
	}

	int enqueueResult = enqueue(queue_list->next->queue, newTask);

	if(enqueueResult == 1) return 1;

	return 0;
}

int kill_task(queues *queue_list, char queue_name[], int pid) {

	if((*queue_list) == NULL) return 2;

	while(queue_list != NULL) {
		char name[MAX_QUEUE_NLENGTH];

		get_name((*queue_list)->queue, name);

		if(strcmp(name, queue_name) == 0) {
			int result = kill(&((*queue_list)->queue), pid);
			return result;
		}
	}

	return 1;
}

int kill_queue(queues *queue_list, char queue_name[]) {
	if((*queue_list) == NULL) return 2;

	queues r = *queue_list;
	queues q = *queue_list;

	char name[MAX_QUEUE_NLENGTH];

	int result = get_name(q->queue, name);

	if(result == 1) return 1;

	while((q != NULL) && (strcmp(name, queue_name) != 0)) {
		r = q;
		q = q->next;
		get_name(q->queue, name);
	}

	if(q == NULL) {
		return 1;
	}
	if(q == *queue_list) {
		(*queue_list) = (*queue_list)->next;
	} else {
		r->next = q->next;
	}

	if(!is_empty(q->queue)) {
		result = clear(q->queue); // clear the queue

		if(result == 1) return 1;
	}

	free(q);

	return 0;

}

int execute_queue(queues queue_node) {



    while(!is_empty(queue_node->queue)) {

        task frontTask;

        int result = dequeue(queue_node->queue, &frontTask);

        if(result) return 1;     

	    frontTask->burstTime++;

        frontTask->remainingTime--;

        int burstTime = frontTask->burstTime;
        int remainingTime = frontTask->remainingTime;
        int quantum = queue_node->queue->timeQuantum;

        printf("%d", remainingTime);

        if(remainingTime > 0) {

            task taskToEnqueue;

            int newResult = create_task(&taskToEnqueue, frontTask->pid, remainingTime, remainingTime); // copy

            if(newResult == 1) return 1;

            newResult = enqueue(queue_node->queue, taskToEnqueue);

            if(newResult == 1) return 1;

        } else {
        	//kill_task(&queue_node, queue_node->queue->name, frontTask->pid);
        	return 1;
        }

        print_queue(queue_node->queue);

        printf("\n");
    }

    return 0;
}

int start_executing(queues queue_list) {

	if(queue_list == NULL) return 1;

	while(!is_queue_list_empty(queue_list)) {
		int result = execute_queue(queue_list); // as queue node

		if(result) return 1;

		queue_list = queue_list->next;
	}

	return 0;
}



int toggle_task(queues queue_list, int pid) {

	if(queue_list == NULL) return 2;

	task task = get_task(queue_list, pid);

	if(task == NULL) return 2;

	int result = set_state(task, task->state == SUSPENDED ? ACTIVE : SUSPENDED);

	if(result == 1) return 2;

	return task->state == ACTIVE;

}

int toggle_queue(queues queue_list, char queue_name[]) {
	if(queue_list == NULL) return 1;

	queue queue = get_queue(queue_list, queue_name);

	if(queue == NULL) return 1;

	int result = set_queue_state(queue, queue->state == SUSPENDED ? ACTIVE : SUSPENDED);

	if(result == 1) return 1;

	return queue->state == ACTIVE;

}

int is_queue_list_empty(queues queue_list) {
	if(queue_list == NULL) return 1;

	return 0;
}