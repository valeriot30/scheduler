#ifndef QUEUES_H
#define QUEUES_H

#include "queue.h"


struct queues {
	queue queue;
	struct queues *next;
};

typedef struct queues* queues;


int create_queues(queues* queues);

int add_queue(queues* queues, queue queue);

int delete_queue(queues* queues, queue* queue);

int get_queue(queues* queues, queue* queue);

int print_queues(queues queues);

#endif