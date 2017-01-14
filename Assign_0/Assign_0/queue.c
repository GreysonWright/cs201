//
//  queue.c
//  Assign_0
//
//  Created by Greyson Wright on 1/14/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "queue.h"
#include <stdlib.h>

queue *newQueue(void (*d)(FILE *, void *)) {
	queue *nQueue = malloc(sizeof *nQueue);
	if (nQueue == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	nQueue->list = newSLL(d);
	return nQueue;
}

void enqueue(queue *items, void *value) {
	insertSLL(items->list, 0, value);
}

void *dequeue(queue *items) {
	return removeSLL(items->list, items->list->size - 1);
}

void *peekQueue(queue *items) {
	return getSLL(items->list, items->list->size - 1);
}

void displayQueue(FILE *fp, queue *items) {
	displaySLL(fp, items->list);
}
