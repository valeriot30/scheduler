#include "multilevel_queue.h"

#include "queue.h"
#include "queues.h"

#include "task.h"


int create_multilevel_queue(multilevel_queue* queue) {
	(*queue) = malloc(sizeof(multilevel_queue));

	if((*queue) == NULL) { return 1; }

	(*queue)->head = NULL;
	return 0;
}

int add_queue(multilevel_queue* queue, char name[]) {
	queues new_queue;

	new_queue = (queues) malloc(sizeof(struct queues));

	if(new_queue == NULL) return 1;

	int result = create_queue(&(new_queue->queue), name);

	if(result == 1) return 1;

	new_queue->next = (*queue)->head;
	(*queue)->head = new_queue;
	return 0;
}

int add_task(multilevel_queue *queue, char name[], int arrivalTime, int burstTime) {

	task task;

	if((*queue) == NULL) return 1;

	int create_result = create_task(&task, 10, name, arrivalTime, burstTime);

	if(create_result == 1) return 1;

	int insert_result = enqueue(((*queue)->head)->queue, task);

	if(insert_result == 1) return 1;

	(((*queue)->head)->queue)->size++;


	return 0;
}	

int is_multilevel_queue_empty(multilevel_queue queue) {
	if(queue == NULL) {
		return 1;
	}

	if(queue->head == NULL) {
		return 1;
	}

	return 0;
}

int print_multilevel_queue(multilevel_queue multilevel_queue) {
	if(multilevel_queue == NULL) {
		return 1;
	}

	queues queues = multilevel_queue->head;


	printf("\n\t Nome \t Priorità \tProcessi \n");
	print_queues(queues);

	return 0;
}