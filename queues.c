
#include "queues.h"

int print_queues(queues queues) {
	while(queues != NULL) {
		print_queue(queues->queue);
		queues = queues->next;
	}

	return 0;
}