#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"

#include "state.h"

#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_NLENGTH 36

struct queue {
	char name[MAX_QUEUE_NLENGTH];

	int size;

	State state;
	
	struct task* head;
	struct task* tail;
};

typedef struct queue* queue;

int peek(queue queue);

int enqueue(queue queue, task task);

int dequeue(queue queue, task* task);

int clear(queue queue);

int size(queue queue);

int is_empty(queue queue);

int create_queue(queue* queue, char name[]);

int print_queue(queue queue);

int set_name(queue queue, char name[]);

#endif
