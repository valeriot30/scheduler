#include "queue.h"

int create_queue(queue* my_queue, char name[], int priority, int timeQuantum) {
	*my_queue = (queue) malloc(sizeof(queue));

	if((*my_queue) == NULL) return 1;

	(*my_queue)->head = NULL;
	(*my_queue)->tail = NULL;

	(*my_queue)->size = 0;

    (*my_queue)->timeQuantum = timeQuantum;

    (*my_queue)->state = ACTIVE;  

    (*my_queue)->priority = 0;  

	set_name((*my_queue), name);

	return 0;
}

int enqueue(queue queue, task task) {

    if(task == NULL) return 1;

    if(queue == NULL) return 1;

    task->next = NULL;
    
    if(is_empty(queue) == 1) {
        queue->head = task;
    }
    else {
        queue->tail->next = task;
    }
    
    queue->tail = task;
    
    increment_size(queue);

    return 0;
}

int dequeue(queue queue, task* task){

    if(queue == NULL) return 2;
    
    if(is_empty(queue)) return 1;

    if(task == NULL) return 1;

    *task = queue->head;

    struct task* temp = queue->head;

    if(queue->head->next == NULL) {
        queue->tail = NULL;
    }

    queue->head = queue->head->next;

    decrement_size(queue);
    free(temp);
    return 0;
}

int clear(queue queue) {

    if(queue == NULL) return 1;

    while(queue->head != NULL) {
        task tmp = queue->head;

        queue->head = queue->head->next;

        free(tmp);

    }

    //free(queue);

    return 0;
}

task peek(queue queue) {
    if(queue == NULL) return NULL;

    return queue->head;
}

int is_empty(queue queue){
    if(queue == NULL) return 2;
    
    if(queue->head == NULL && queue->tail == NULL)
        return 1;
    else
        return 0;
}


void print_queue(queue queue) {
	if(queue == NULL) {
		printf("Coda [%s] non inizializzata.", queue->name);
	}

	struct task *temp = queue->head;

    if(is_empty(queue) == 1) {
        printf("\t Coda [%s] vuota.", queue->name);
    }

    while(temp != NULL) {
        print_task(temp);
        temp = temp->next;
    }

    //printf("%d", temp->pid);

    printf("\n");
}

int print_queue_full(queue queue) {
    if(queue == NULL) {
        return 1;
    }

    task p = queue->head;
    

    printf("\n\tNome \t Stato \t Processi \n");
    printf("\t%s \t %d \t %d \n", queue->name, (int) queue->state, queue->size);
    printf("\t--------------------\n");

    while(p != NULL){
        print_task(p);
        p = p->next;
    }

    return 0;
}

int set_name(queue queue, char name[]) {
	if(queue == NULL) return 1;

	strcpy(queue->name, name);

	return 0;
}

int get_name(queue queue, char name[]) {
    if(queue == NULL) return 1;
    strcpy(name, queue->name);
    return 0;
}

int set_queue_state(queue queue, State state) {
    if(queue == NULL) return 1;

    queue->state = state;
    return 0;
}

int kill(queue* queue, int pid) {
    struct task* r = (*queue)->head;
    struct task* q = (*queue)->head;

    while((q != NULL) && (q->pid != pid)) {
        r = q;
        q = q->next;
        pid = q->pid;
    } 

    if(q == NULL) return 2;

    if(q == (*queue)->head) {
        (*queue)->head =  (*queue)->head->next;
    } else {
        r->next = q->next;
    }

    int result = destroy_task(&(q));

    if(result == 1) return 2;

    decrement_size((*queue));

    free(q);
    return 0;
}

void increment_size(queue queue) {
    if(queue == NULL) return;

    queue->size++;
}

void decrement_size(queue queue) {
    if(queue == NULL) return;

    queue->size--;
}



int size(queue queue) {

	if(queue == NULL) { return 0; }

	return queue->size;
}