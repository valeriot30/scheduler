#include "queues.h"

int create_queues_list(queues* queues_list) {
	(*queues_list) = NULL;
	return 0;
}

int destroy_queues(queues* queue_list) {
	while(*queue_list != NULL) {
		int result = kill_queue(queue_list, (*queue_list)->queue->name);
		if(result) return 1;
	}

	free(*queue_list);
	*queue_list = NULL;
	return 0;
}

queue get_head_queue(queues queue_list) {
	if(queue_list == NULL) return NULL;

	return queue_list->queue;
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

int add_queue(queues* queue_list, char queue_name[], int timeQuantum, queue* queue) {

	// controlla che il time quantum scelto non sia troppo alto
	if(timeQuantum > MAX_QUEUE_QUANTUM) {
		return 2;
	}

	queues r = *queue_list;
	queues q = *queue_list;

	queues new_queue = (queues)malloc(sizeof(struct queues));

	if(new_queue == NULL) return 1;

	int result = create_queue(&(new_queue->queue), queue_name, timeQuantum);

	if(result == 1) {
		free(new_queue);
		return 1;
	}


	// inserisci ordinatamente in base al time quantum
	while((q != NULL) && (get_time_quantum(q->queue) < get_time_quantum(new_queue->queue))) {
		r = q;
		q = q->next;
	}

	if(q == *queue_list) {
		new_queue->next = *queue_list;
		*queue_list = new_queue;
	} else {
		r->next = new_queue;
		new_queue->next = q;
	}

	if(queue != NULL) {
		*queue = new_queue->queue;
	}

	return 0;

}

int add_task(queues queue_list, int pid, int burstTime, int remainingTime) {

	if(pid > MAX_TASK_PID) return 3; // controlla se non supera il PID massimo

	if(queue_list == NULL) return 1;

	task task = get_task(queue_list, pid);

	if(task != NULL) return 2; // controlla se il processo non esiste già
	
	// creo dinamicamente il processo
	int result = create_task(&task, pid, burstTime, remainingTime);

	if(result == 1) {
		free(task);
		return 1;
	}

	// incodo
	result = enqueue(queue_list->queue, task);

	if(result == 1) return 1;

	return 0;

}

task get_task(queues queue_list, int pid) {
	
	if(queue_list == NULL) return NULL;

	task task;

	while(queue_list != NULL) {
		
		int result = find(queue_list->queue, pid, &task);

		if(result == 1) {
			return task;
		}

		queue_list = queue_list->next;
	}

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

int kill_task(queues queue_list, char queue_name[], int pid) {

	if(queue_list == NULL) return 3;

	while(queue_list != NULL) {
		char name[MAX_QUEUE_NLENGTH];

		get_name(queue_list->queue, name);

		if(strcmp(name, queue_name) == 0) {
			int result = kill(((queue_list)->queue), pid);
			return result;
		}

		queue_list = queue_list->next;
	}

	return 1;
}

int kill_queue(queues *queue_list, char queue_name[]) {
	if((*queue_list) == NULL) return 2;

	queues r = *queue_list;
	queues q = *queue_list;

	char name[MAX_QUEUE_NLENGTH];

	get_name(q->queue, name);

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

	int result = destroy_queue(&(q->queue));

	free(q);

	if(result == 1) return 1;

	return 0;

}

int execute_queue(queues queue_node) {

	task frontTask;
    int result;

    // finchè non è vuota, o finchè non è sospesa
    while(!is_empty(queue_node->queue) && queue_node->queue->state != SUSPENDED) {

        result = dequeue(queue_node->queue, &frontTask);
        // qui lo tolgo dalla testa della coda e prendi il riferimento

        if(result) return 1; 

        execute_task(&frontTask); // levo il tempo rimanente e aumento il burstTime

        int burstTime = get_time(frontTask);
        int remainingTime = get_remaining_time(frontTask);
        int quantum = get_time_quantum(queue_node->queue);

        // se supera il tempo consentito per la sua coda, allora si sposta giù
        if(burstTime > quantum) {
            if(queue_node->next != NULL) {
            	
            	result = enqueue(queue_node->next->queue, frontTask);

            	if(result) {
            		free(frontTask);
            		return 1;
            	}
        	} else {
        		free(frontTask);

        	}
        } else {
        	// altrimenti controlla se ha ancora tempo da eseguire ed eventualmente lo rincodo
        	if(remainingTime > 0) {
                
	            result = enqueue(queue_node->queue, frontTask);

	            if(result) {
	            	free(frontTask);
	            	return 1;
	            }

	        } else {
	            // altrimenti se ha esaurito il tempo lo elimino definitivamente
	            result = destroy_task(&frontTask);
	            if(result) return 1;
	        }
        }

        print_queue(queue_node->queue);

        printf("\n");
    }

    return 0;
}

int start_executing(queues queue_list) {

	if(queue_list == NULL) return 1;

	// finchè tutte le code non sono vuote
	while(!is_queue_list_empty(queue_list)) {
		printf("\n\t%s \n", queue_list->queue->name);
		int result = execute_queue(queue_list); // esegui il nodo relativo della coda, con annessi processi

		if(result) return 1;

		queue_list = queue_list->next;
	}

	return 0;
}

int toggle_task(queues queue_list, int pid) {

	if(queue_list == NULL) return 1;

	task task = get_task(queue_list, pid);

	if(task == NULL) return 2;

	State state = get_state(task);

	int result = set_state(task, state == SUSPENDED ? ACTIVE : SUSPENDED); // setta attivo se è sospeso, altrimenti sospendi

	if(result) return 1;

	return get_state(task) == ACTIVE;

}

int toggle_queue(queues queue_list, char queue_name[]) {
	if(queue_list == NULL) return 1;

	queue queue = get_queue(queue_list, queue_name);

	if(queue == NULL) return 2;

	State state = get_queue_state(queue);

	int result = set_queue_state(queue, state == SUSPENDED ? ACTIVE : SUSPENDED);

	if(result) return 1;

	return get_queue_state(queue) == ACTIVE;

}

int save_data(queues queue_list, char* fileName) {
	FILE *f = fopen(fileName, "w");
	
	if(f == NULL) {
		printf("Impossibile scrivere su file.");
		exit(1);
	}

	while(queue_list != NULL) {
		save_queue(queue_list->queue, f);
		queue_list = queue_list->next;	
	}

	fclose(f);

	return 0;
}

int load_data(queues* queue_list, char* fileName) {
	FILE *f = fopen(fileName, "r");

	if(f == NULL) return 1;

	char name[MAX_QUEUE_NLENGTH];
	int quantum;

	queue queue;

	while(fscanf(f,"%s %d", name, &quantum) > 0){
		
       	if(name[0] != '-') {
       	   int result = add_queue(queue_list, name, quantum, &queue);
       	   if(result) return 1;
       	}

        load_queue(queue, f);
    }

    fclose(f);

    return 0;
}

int is_queue_list_empty(queues queue_list) {
	if(queue_list == NULL) return 1;

	return 0;
}