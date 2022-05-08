#include <stdio.h>
#include <stdlib.h>

#include "queues.h"

#ifndef MULTILEVEL_QUEUE_H
#define MULTILEVEL_QUEUE_H

struct multilevel_queue {
    struct queues* head;
};

typedef struct multilevel_queue* multilevel_queue;

int create_multilevel_queue(multilevel_queue* queue);

int add_task_queue(multilevel_queue* queue, char name[]);

int is_multilevel_queue_empty(multilevel_queue queue);

int print_multilevel_queue(multilevel_queue queue);

int add_task(multilevel_queue* queue, char name[], int arrivalTime, int burstTime);

int clear_queue(queue* queue);

int clear_all(multilevel_queue* queue);

#endif