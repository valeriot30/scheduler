#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "multilevel_queue.h"
#include "task.h"
#include "queue.h"

#include "time.h"

#define BASIC_HIGHEST_PID 10522

multilevel_queue global_queue;

void print_global_queue() {
	printf("\n\n");
	printf("\t--------------------------------------------------\t\n");
	printf("\t          Lista di code e processi attivi		   \n");


	int result = print_multilevel_queue(global_queue);

	if(result == 1) {
		printf("Qualcosa e\' andato storto nella creazione della coda.");
	}
}

void add_task_queue_menu() {

	char action;
	char name[MAX_QUEUE_NLENGTH];

	printf("\n\n");
	printf("\t-------------------------------------------------\t\n");
	printf("\t          Aggiungi una coda di processi   \n");
	printf("\n");
	printf("\t| Nome:");
	scanf("%s", name);

	if(strlen(name) > MAX_QUEUE_NLENGTH) {
		printf("Il nome scelto per la coda di processi e\' troppo lungo!");
	}

	int result = add_queue(&global_queue, name);

	if(result == 1) {
		printf("\nErrore nel creare la coda con priorità [1]");
	} else {
		printf("\nCoda di processi con priorità: [1] creata correttamente");
	}
}


void add_task_menu() {

	char choose;
	char name[MAX_TASK_LENGTH];
	int arrivalTime, pid, burstTime;


	if(is_multilevel_queue_empty(global_queue)) {
		printf("La coda globale di processi e\' vuota, vuoi aggiungere una coda? (y/n): ");
		

		scanf(" %c", &choose);

		if(choose == 'y') {
			add_task_queue_menu();
			return;
		} else {
			exit(0);
		}
	} 
	else {

		printf("\n\n");
		printf("\t-----------------------------------------\n");
		printf("\t          Aggiungi un processo           \n");
		printf("\n");
		printf("\t| Nome: ");
		scanf("%s", name);

		printf("Inserisci il tempo totale del processo: ");
		scanf("%d", &burstTime);

		srand(time(NULL)); // initialize

		arrivalTime = rand() % (16); // 0 - 15 

		int result = add_task(&global_queue, name, arrivalTime, burstTime); 

		if(result == 1) {
			printf("Errore nella creazione del processo [%s]", name);
		}

		printf("\nProcesso creato correttamente.");
	} 
}

void menu() {
	system("clear");
	
	printf("\n\n");
	printf("\t+---------------------------------------+\n");
    printf("\t|               Scheduler          	|\n");
    printf("\t|  a - Aggiungi un processo            	|\n");
    printf("\t|  b - Aggiungi una coda di processi  	|\n");
	printf("\t|  s - Avvia i processi       		|\n");
	printf("\t|  f - Cerca un processo per PID        |\n");
	printf("\t|  v - Visualizza i processi            |\n");
	printf("\t|  q - Esci                             |\n");
	printf("\t+---------------------------------------+\n");
}

int main() {
	char action = 'x';

	int create_result = create_multilevel_queue(&global_queue);

	if(create_result == 1) {
		printf("Qualcosa e\' andato storto nell'inizializzazione dello scheduler.");
		return 1;
	}

	system("clear");
	
	while(action != 'q') {

	    printf("\n");
		switch(action) {
			case 'x':
				menu();
				action = '_';
				break;
			case 'a':
				//system("clear");
				add_task_menu();
				action = '_';
				break;
			case 'c':
				// avvia una coda di processi
				break;
			case 'v':
				print_global_queue();
				action = '_';
				break;		
			case 'k':
				// uccidi un processo in coda
				break;	
			default:
				scanf("%c", &action); 	
				break;
		
		}
	}

	return 0;
}