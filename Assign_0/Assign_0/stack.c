//
//  stack.c
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "stack.h"
#include <stdlib.h>

stack *newStack(void (*d)(FILE *,void *)) {
	stack *nStack = malloc(sizeof *newStack);
	if (nStack == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	nStack->list = newSLL(d);
	return nStack;
}

void push(stack *items, void *value) {
	insertSLL(items->list, 0, value);
}

void *pop(stack *items) {
	return removeSLL(items->list, 0);
}

void *peekStack(stack *items) {
	return getSLL(items->list, 0);
}

void displayStack(FILE *file ,stack *items) {
	displaySLL(file, items->list);
}
