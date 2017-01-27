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

void *sort(queue *front) {
	queue *back = newQueue(displayInteger);
	stack *stackItems = newStack(displayInteger);
	integer *element = 0;
	integer *frontTop = 0;
	integer *stackTop = 0;
	integer *backTop = 0;
	
	while (peekQueue(front)) {
		element = dequeue(front);
		frontTop = peekQueue(front);
		stackTop = peekStack(stackItems);
		backTop = peekQueue(back);
		
		if (stackTop && stackTop->value > element->value) {
			enqueue(back, pop(stackItems));
		}
		
		if (frontTop && element->value < frontTop->value) {
			push(stackItems, element);
		} else {
			enqueue(back, element);
		}
	}
	
	while (peekStack(stackItems)) {
		enqueue(back, pop(stackItems));
	}
	
	return back;
}

int main(int argc, const char * argv[]) {
	queue *inputQueue = newQueue(displayInteger);
	enqueue(inputQueue, newInteger(1));
	enqueue(inputQueue, newInteger(2));
	enqueue(inputQueue, newInteger(3));
	enqueue(inputQueue, newInteger(4));
	enqueue(inputQueue, newInteger(5));
	
	displayQueue(stdout, inputQueue);
	queue *sortedQueue = sort(inputQueue);
//	sortedQueue = sort(sortedQueue);
	displayQueue(stdout, sortedQueue);
	return 0;
}
