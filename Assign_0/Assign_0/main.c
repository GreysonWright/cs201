//
//  main.c
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sll.h"
#include "dll.h"
#include "integer.h"
#include "queue.h"
#include "stack.h"

int findMinDLL(dll *items) {
	integer *minVal = getDLL(items, 0);
	int minValIndex = 0;
	
	for (int i = 0; i < items->size; i++) {
		integer *val = getDLL(items, i);
		
		if (val->value < minVal->value) {
			minVal = val;
			minValIndex = i;
		}
	}
	
	return minValIndex;
}

int findMaxSLL(sll *items) {
	integer *maxVal = getSLL(items, 0);
	int maxValIndex = 0;
	
	for (int i = 0; i < items->size; i++) {
		integer *val = getSLL(items, i);
		
		if (val->value > maxVal->value) {
			maxVal = val;
			maxValIndex = i;
		}
	}
	
	return maxValIndex;
}

void showStack(stack *items) {
	printf("The stack is ");
	displayStack(stdout, items);
	printf(".\n");
}

void showSLL(sll *items) {
	printf("The sll is ");
	displaySLL(stdout, items);
	printf(".\n");
}

void showMinDLL(dll *items) {
	printf("The min value is ");
	displayInteger(stdout, (integer *)removeDLL(items, findMinDLL(items)));
	printf("\n");
}

void showMaxSLL(sll *items) {
	printf("The max value is ");
	displayInteger(stdout, (integer *)removeSLL(items, findMaxSLL(items)));
	printf("\n");
}

int main() {
	sll *a = newSLL(displayInteger);
	sll *b = newSLL(displayInteger);
	
	srand((unsigned)time(NULL));
	int rando = 0;
	
	for (int i = 0; i < 10000; i++) {
		if (a->size == 0) {
			insertSLL(a, 0, newInteger(i));
		} else {
			rando = rand() % a->size;
			insertSLL(a, rando, newInteger(i));
		}
	}
	
	for (int i = 0; i < 100000000; i++) {
		unionSLL(a, b);
		unionSLL(b, a);
	}
	
	showSLL(a);
	showSLL(b);
	
	for (int i = 0; i < 10000; i++) {
		if (b->size == 0) {
			insertSLL(b, 0, newInteger(i));
		} else {
			rando = rand() % b->size;
			insertSLL(b, rando, newInteger(i));
		}
	}
	
	for (int i = 0; i < 100000000; i++) {
		unionSLL(b, a);
		unionSLL(a, b);
	}
	
	showSLL(a);
	showSLL(b);
	
//	stack *emptyStack = newStack(displayInteger);
//	showStack(emptyStack);
//	
//	stack *stackItems = newStack(displayInteger);
//	showStack(stackItems);
//	push(stackItems, newInteger(3));
//	showStack(stackItems);
//	pop(stackItems);
//	showStack(stackItems);
//	
//	dll *dllItems = newDLL(displayInteger);
//	insertDLL(dllItems, 0, newInteger(0));
//	insertDLL(dllItems, 1, newInteger(3));
//	insertDLL(dllItems, 2, newInteger(4));
//	removeDLL(dllItems, 3);
//	showMinDLL(dllItems);
//	
//	sll *sllItems = newSLL(displayInteger);
//	insertSLL(sllItems, 0, newInteger(0));
//	insertSLL(sllItems, 1, newInteger(3));
//	insertSLL(sllItems, 2, newInteger(2));
//	showMaxSLL(sllItems);
//	
//	queue *queueItems = newQueue(displayInteger);
//	printf("The size of the queue is %d\n", queueItems->list->size);
//	
//	sll *sllMassItems = newSLL(displayInteger);
//	for (int i = 1; i < 10000; i++) {
//		insertSLL(sllMassItems, 0, newInteger(i));
//	}
//	showSLL(sllMassItems);
	
	return 0;
}
