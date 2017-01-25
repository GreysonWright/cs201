//
//  main.c
//  Assign_1
//
//  Created by Greyson Wright on 1/24/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include "integer.h"

int stackIsEmpty(stack *items) {
	if (peekStack(items)) {
		return 0;
	}
	
	return 1;
}

int queueIsEmpty(queue *items) {
	if (peekQueue(items)) {
		return 0;
	}
	
	return 1;
}

void *sort(queue *queue0) {
	queue *queue1 = newQueue(displayInteger);
	stack *stackItems = newStack(displayInteger);
	integer *element = 0;
	int storeSwitch = 1;
	
	while (!queueIsEmpty(queue0)) {
		element = dequeue(queue0);
		integer *top = peekQueue(queue0);
		if (queueIsEmpty(queue1) && top && element->value > top->value) { //((integer *)peekQueue(queue0))->value
//			enqueue(queue1, element);
//			push(stackItems, element);
			if (storeSwitch == 1) {
				push(stackItems, element);
			} else {
				enqueue(queue1, element);
			}
			
			if (storeSwitch != 1) {
				enqueue(queue1, pop(stackItems));
				push(stackItems, dequeue(queue0));
			}
			
			storeSwitch *= -1;
		} else {
//			push(stackItems, element);
			if (storeSwitch == 1) {
				push(stackItems, element);
			} else {
				enqueue(queue1, element);
			}
		}
	}

	while (!queueIsEmpty(queue1)) {
		push(stackItems, dequeue(queue1));
	}
	
	while (!stackIsEmpty(stackItems)) {
		enqueue(queue1, pop(stackItems));
	}
//	if (!stackIsEmpty(stackItems)) {
//		enqueue(queue1, pop(stackItems));
//		displayStack(stdout, stackItems);
//	}
	
	return queue1;
}

int main(int argc, const char * argv[]) {
	queue *inputQueue = newQueue(displayInteger);
	enqueue(inputQueue, newInteger(2));
	enqueue(inputQueue, newInteger(4));
	enqueue(inputQueue, newInteger(5));
	enqueue(inputQueue, newInteger(3));
	enqueue(inputQueue, newInteger(1));
	
	displayQueue(stdout, inputQueue);
	queue *sortedQueue = sort(inputQueue);
	sortedQueue = sort(sortedQueue);
	displayQueue(stdout, sortedQueue);
	return 0;
}
