#include "queue.h"

int create_queue(queue* queue, char name[]) {
	*queue = malloc(sizeof(queue));

	if((*queue) == NULL) { return 1; }

	(*queue)->head = NULL;
	(*queue)->tail = NULL;

	(*queue)->size = 0;

	set_name((*queue), name);
	return 0;
}

int enqueue(queue queue, task task) {

    if(queue == NULL) return 2;

    task->next = NULL;

    if(is_empty(queue) == 1)

        queue->head = task;
    else {
        queue->tail->next = task;
    }

    queue->tail = task;

    return 0;
}

int is_empty(queue queue){
    if(queue == NULL) return 2;
    if(queue->head == NULL && queue->tail == NULL)
        return 1;
    else
        return 0;
}


int print_queue(queue queue) {
	if(queue == NULL) {
		return 1;
	}

	printf("\t %s \t %d \t %d", queue->name, 1, queue->size);
	return 0;
}

int set_name(queue queue, char name[]) {
	if(queue == NULL) return 1;

	strcpy(queue->name, name);

	return 0;
}

int size(queue queue) {

	if(queue == NULL) { return 0; }

	return queue->size;
}