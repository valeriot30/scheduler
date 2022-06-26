#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "queues.h"


queues global_queue;


void print_global_queue() {
	if(!is_queue_list_empty(global_queue)) {
		printf("\n\n");
		printf("\t*------------------------------------------------*\t\n");
		printf("\t|         Lista di code e processi attivi        |\n");
		printf("\t*------------------------------------------------*\t\n");


		print_queues_full(global_queue);

		

		/*  *---*
			| 2 |
			*---*
		*/

		/*printf("\t*---* *---* *---*\t\n");
		printf("\t| 1 | | 2 | | 3 |\n");
		printf("\t*---* *---* *---*\t\n");

		printf("\n\n");

		printf("\t*---* *---* *---*\t\n");
		printf("\t| 1 | | 2 | | 3 |\n");
		printf("\t*---* *---* *---*\t\n");


		printf("\n\n");

		printf("\t*---* *---* *---*\t\n");
		printf("\t| 1 | | 2 | | 3 |\n");
		printf("\t*---* *---* *---*\t\n");*/


	} else {
		printf("La coda di processi globale e\' vuota.");
	}

}

void kill_queue_menu() {

	if(is_queue_list_empty(global_queue)) {
		printf("La coda globale di processi è vuota.");
		return;
	}

	int pid = 0;
	char name[MAX_QUEUE_NLENGTH];

	printf("\n\n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Uccidi una coda.                   | \n");
	printf("\t*------------------------------------------------*\n");
	printf("\n");

	printf("\t| Inserisci il nome della coda: ");
	scanf("%s", name);

	int result = kill_queue(&global_queue, name);

	if(result == 2) {
		printf("\n\t[-] Errore nell'uccidere la coda");
	}
	else if(result == 1) {
		printf("\n\t[-] La coda non esiste");
	} else {
		printf("\n\t[+] Coda uccisa correttamente");
	}	
}

void search_task_menu() {

	if(is_queue_list_empty(global_queue)) {
		printf("La coda globale di processi è vuota.");
		return;
	}

	int pid = 0;

	printf("\n\n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Cerca un processo                  | \n");
	printf("\t*------------------------------------------------*\n");
	printf("\n");

	printf("\t| Inserisci il PID: ");
	scanf("%d", &pid);

	task resultTask = get_task(global_queue, pid);

	if(resultTask == NULL) {
		printf("\n\t[-] Errore nel cercare il processo");
	}
	else {
		printf("\t[+] Processo trovato: \n");

		print_task_full(resultTask);
	}	
}

void kill_task_menu() {

	if(is_queue_list_empty(global_queue)) {
		printf("La coda globale di processi è vuota.");
		return;
	}

	int pid = 0;
	char name[MAX_QUEUE_NLENGTH];

	printf("\n\n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Uccidi un processo                 | \n");
	printf("\t*------------------------------------------------*\n");
	printf("\n");

	printf("\t| Inserisci il nome della coda: ");
	scanf("%s", name);

	printf("\t| Inserisci il pid: ");
	scanf("%d", &pid);

	int result = kill_task(&global_queue, name, pid);

	if(result == 3) {
		printf("\n\t[-] Errore nell'uccidere il processo con PID [%d]", pid);
	}
	else if(result == 2) {
		printf("\n\t[-] Il processo con PID [%d] non esiste", pid);
	} 
	else if(result == 1) {
		printf("\n\t[-] La coda non esiste");
	}
	else {
		printf("\n\t[+] Processo [%d] ucciso correttamente", pid);
	}	
}

void toggle_task_menu() {

	if(is_queue_list_empty(global_queue)) {
		printf("La coda globale di processi è vuota.");
		return;
	}

	int pid = 0;

	printf("\n\n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Attiva/sospendi un processo        | \n");
	printf("\t*------------------------------------------------*\n");
	printf("\n");

	printf("\t| Inserisci il pid: ");
	scanf("%d", &pid);

	int result = toggle_task(global_queue, pid);

	if(result == 1) {
		printf("\n\n\t[-] Errore nel sospendere il processo con PID [%d]", pid);
	}
	else if(result == 0) {
		printf("\n\n\t[+] Processo [%d] sospeso correttamente", pid);
	}
	else {
		printf("\n\n\t[+] Processo [%d] attivato correttamente", pid);
	}
	
}

void toggle_queue_menu() {

	if(is_queue_list_empty(global_queue)) {
		printf("La coda globale di processi è vuota.");
		return;
	}

	char name[MAX_QUEUE_NLENGTH];

	printf("\n\n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Attiva/Sospendi una coda           |\n");
	printf("\t*------------------------------------------------*\n");
	printf("\n");

	printf("\t| Inserisci il nome: ");
	scanf("%s", name);

	int result = toggle_queue(global_queue, name);

	if(result == 2) {
		printf("\n\n\t[-] Errore nel sospendere la coda");
	}
	else if(result == 0) {
		printf("\n\n\t[+] Coda sospesa correttamente");
	}
	else {
		printf("\n\n\t[+] Coda attivata correttamente");
	}
	
}

void start_executing_menu() {
	if(is_queue_list_empty(global_queue)) {
		printf("La coda globale di processi è vuota.");
		return; 
	}

	char action;

	printf("\n\n");

	printf("\t*------------------------------------------------*\n");
	printf("\t|             Avvia lo scheduler                 | \n");
	printf("\t*------------------------------------------------*\n");


	printf("\tVuoi avviare lo scheduler? (y/n)");
	scanf(" %c", &action);

	if(action == 'y') {
		char choose;
		int result = -1;

		while(choose != 'n' && result != 0) {
			result = start_executing(global_queue);
			scanf("%c", &choose);
		}

		printf("\n\n\t[+] Scheduling completato");
	}
}


void add_task_queue_menu() {

	char action;
	int timeQuantum;
	char name[MAX_QUEUE_NLENGTH];

	printf("\n\n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Aggiungi una coda                  | \n");
	printf("\t|             2 code totali	                 | \n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Attualmente eseguendo:		 | \n");
	printf("\t|             Coda [1] con 16 processi		 | \n");
	printf("\t*------------------------------------------------*\n");
	printf("\n");
	printf("\t| Nome:");
	scanf("%s", name);

	if(strlen(name) > MAX_QUEUE_NLENGTH) {
		printf("Il nome scelto per la coda di processi e\' troppo lungo!");
	}

	printf("\t| Time Quantum:");

	scanf("%d", &timeQuantum);

	int result = add_queue(&global_queue, name, 1, timeQuantum);

	if(result == 1) {
		printf("\n\t[-]Errore nel creare la coda con priorità [1]");
	} else {
		printf("\n\t[+] Coda di processi con priorità: [1] creata correttamente");
	}
}


void add_task_menu() {

	char choose;
	
	int arrivalTime = 0;
	int pid, burstTime;


	if(is_queue_list_empty(global_queue)) {
		printf("[-] La coda globale di processi è vuota, vuoi aggiungere una coda? (y/n): ");
		

		scanf(" %c", &choose);

		if(choose == 'y') {
			add_task_queue_menu();
		}
	} 
	printf("\n\n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Aggiungi un processo               | \n");
	printf("\t*------------------------------------------------*\n");
	printf("\t|             Attualmente eseguendo:		 | \n");
	printf("\t|             Coda [1] con 16 processi		 | \n");
	printf("\t*------------------------------------------------*\n");
	printf("\n");
	
	printf("\n\n");
	printf("\n");

	printf("\t| PID:  ");
	scanf("%d", &pid);

	printf("\t| Tempo richiesto:  ");
	scanf("%d", &burstTime);

		// initialize

	arrivalTime = rand() % (16); // 0 - 15 

	int result = add_task(global_queue, pid, arrivalTime, burstTime); 

	if(result == 2) {
		printf("[-] Errore nella creazione del processo [%d]", pid);
	} else if(result == 1) {
		printf("[-] Il processo [%d] esiste già.", pid);
	}

	printf("\n\t [+] Processo creato correttamente.");
}

void menu() {
	//system("clear");
	
	printf("\n\n");
	printf("\t+---------------------------------------+\n");
    printf("\t|               Scheduler          	|\n");
    printf("\t|  a - Aggiungi un processo            	|\n");
    printf("\t|  b - Aggiungi una coda di processi  	|\n");
	printf("\t|  s - Avvia i processi       		|\n");
	printf("\t|  f - Cerca un processo per PID        |\n");
	printf("\t|  v - Visualizza i processi            |\n");
	printf("\t|  p - Attiva/disattiva un processo     |\n");
	printf("\t|  l - Attiva/disattiva una coda        |\n");
	printf("\t|  k - Uccidi un processo      		|\n");
	printf("\t|  m - Uccidi una coda      		|\n");
	printf("\t|  q - Esci                             |\n");
	printf("\t+---------------------------------------+\n");
}

int main() {
	char action = 'x';

	int create_result = create_queues_list(&global_queue);

	if(create_result == 1) {
		printf("Qualcosa e\' andato storto nell'inizializzazione dello scheduler.");
		return 1;
	}

	//system("clear");
	
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
			case 'b':
				add_task_queue_menu();
				action = '_';
				break;			
			case 'p':
				toggle_task_menu();
				action = '_';
				break;
			case 'v':
				print_global_queue();
				action = '_';
				break;		
			case 'k':
				kill_task_menu();
				action = '_';
				break;
			case 'l':
				toggle_queue_menu();
				action = '_';
				break;					
			case 'm':
				kill_queue_menu();
				action = '_';
				break;
			case 'f':
				search_task_menu();
				action = '_';
				break;		
			case 's':
				start_executing_menu();
				action = '_';
				break;			
			default:
				scanf("%c", &action); 	
				break;
		
		}
	}

	return 0;
}