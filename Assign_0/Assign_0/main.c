//
//  main.c
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

//#include <stdio.h>
//
#include <stdio.h>
#include <stdlib.h>
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

static void showStack(stack *items) {
	printf("The stack is ");
	displayStack(stdout, items);
	printf(".\n");
}

static void showMinDLL(dll *items) {
	displayInteger(stdout, (integer *)removeDLL(items, findMinDLL(items)));
	printf("\n");
}

static void showMaxSLL(sll *items) {
	displayInteger(stdout, (integer *)removeSLL(items, findMaxSLL(items)));
	printf("\n");
}

int main(int argc, char **argv) {
	stack *stackItems = newStack(displayInteger);
	showStack(stackItems);
	push(stackItems, newInteger(3));
	showStack(stackItems);
	pop(stackItems);
	showStack(stackItems);
	
	dll *dllItems = newDLL(displayInteger);
	insertDLL(dllItems, 0, newInteger(0));
	insertDLL(dllItems, 1, newInteger(3));
	insertDLL(dllItems, 2, newInteger(2));
	showMinDLL(dllItems);
	
	sll *sllItems = newSLL(displayInteger);
	insertSLL(sllItems, 0, newInteger(0));
	insertSLL(sllItems, 1, newInteger(3));
	insertSLL(sllItems, 2, newInteger(2));
	showMaxSLL(sllItems);
	
	return 0;
}
