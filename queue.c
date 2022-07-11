#include "queue.h"

int create_queue(queue* my_queue, char name[], int timeQuantum) {
	*my_queue = (queue) malloc(sizeof(struct queue));

	if((*my_queue) == NULL) return 1;

	(*my_queue)->head = NULL;
	(*my_queue)->tail = NULL;

	(*my_queue)->size = 0;

    (*my_queue)->timeQuantum = timeQuantum;

    set_queue_state(*my_queue, ACTIVE);

	set_name((*my_queue), name);

	return 0;
}

int destroy_queue(queue* queue) {
    if(*queue == NULL) return 1;

    // ci assicuriamo di svuotare la coda prima
    int result = clear(queue);
    
    if(result == 1) return 1;

    free(*queue);
    *queue = NULL;
    return 0;
}

int enqueue(queue queue, task task) {

    if(task == NULL) return 1;

    if(queue == NULL) return 1;

    task->next = NULL;
    
    if(is_empty(queue)) {
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

    if(task == NULL) return 1;
    
    if(is_empty(queue)) return 1;
    
    *task = queue->head;
    
    if(queue->head->next == NULL) {
        queue->tail = NULL;
    }
    

    queue->head = queue->head->next;
   
    decrement_size(queue);

    //tutto e' andato a buon fine
    return 0;
}

int find(queue queue, int pid, task* task) {
    struct task* t = queue->head;

    while(t != NULL) {
        if(get_pid(t) == pid) {
            *task = t; // copio
            return 1;
        }
        t = t->next;
    }

    return 0;
}

int clear(queue* queue) {

    if(*queue == NULL) return 1;

    // svuota la coda
    while((*queue)->head != NULL) {
        task tmp = (*queue)->head;
        (*queue)->head = (*queue)->head->next;
        free(tmp);
    }
    return 0;
}

task peek(queue queue) {
    if(queue == NULL) return NULL;

    return queue->head;
}

int is_empty(queue queue){
    if(queue->head == NULL && queue->tail == NULL) {
        return 1;
    } else {
        return 0;
    }
}


void print_queue(queue queue) {

	struct task *temp = queue->head;

    while(temp != NULL) {
        print_task(temp);
        temp = temp->next;
    }

    free(temp);
    
    printf("\n");
}

int print_queue_full(queue queue) {
    if(queue == NULL) {
        return 1;
    }

    task p = queue->head;
    
    printf("\n\tNome \t Stato \t Processi \t Quantum \n");
    printf("\t%s \t %s \t %d \t %d \t \n", queue->name, getStateText(queue->state), queue->size, queue->timeQuantum);
    printf("\t---------------------------------------\n");

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

int get_queue_state(queue queue) {
    return queue->state;
}

int get_name(queue queue, char name[]) {
    if(queue == NULL) return 1;
    strcpy(name, queue->name);
    return 0;
}

int get_time_quantum(queue queue) {
    return queue->timeQuantum;
}

int set_queue_state(queue queue, State state) {
    if(queue == NULL) return 1;

    queue->state = state;
    return 0;
}

int kill(queue queue, int pid) {


    task r = queue->head;
    task q = queue->head;

    while((q != NULL) && (q->pid != pid)) {

        r = q;
        q = q->next;
    } 

    if(q == NULL) return 2;

    if(q == queue->head) {
        queue->head =  queue->head->next;
    } else {
        r->next = q->next;
    }

    int result = destroy_task(&(q));

    if(result == 1) return 3;

    decrement_size(queue);

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

void save_queue(queue queue, FILE* f) {

    if(is_empty(queue)) return; // se è vuota non ha senso salvarla
    
    char name[MAX_QUEUE_NLENGTH];

    get_name(queue, name);

    int quantum = get_time_quantum(queue);

    fprintf(f,"%s %d\n", name, quantum);

    task t = queue->head;

    while(t != NULL) {
        save_task(t, f);
        t = t->next;
    }
    fprintf(f, "-\n"); 
}

void load_queue(queue queue, FILE* f) {
    // carico i processi

    int pid, burstTime, remainingTime;

    while(fscanf(f,"%d %d %d", &pid, &burstTime, &remainingTime) > 0){
        
        task task;

        int result = create_task(&task, pid, burstTime, remainingTime);

        if(result) return;

        result = enqueue(queue, task);

        if(result == 1) return;

    };
}