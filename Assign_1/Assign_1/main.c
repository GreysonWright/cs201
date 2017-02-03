//
//  main.c
//  Assign_1
//
//  Created by Greyson Wright on 1/24/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "scanner.h"

typedef int (Comparator)(void *, void *);
typedef void (Printer)(FILE *, void *);
typedef void *(Scanner)(FILE*);
typedef void (GC)(void *);

void *sort(queue *front, Comparator *compare, Printer *print) {
	queue *back = newQueue(print);
	stack *stackItems = newStack(print);
	void *backTail = 0;
	void *element = dequeue(front);
	void *frontTop = peekQueue(front);
	void *stackTop = peekStack(stackItems);
	int swapped = 0;
	
	while (element) {
		if (frontTop && compare(element, frontTop) < 0) {
			push(stackItems, element);
			element = dequeue(front);
			swapped = 1;
		} else if (stackTop && compare(stackTop, element) >= 0) {
			backTail = pop(stackItems);
			enqueue(back, backTail);
			swapped = 1;
		} else {
			backTail = element;
			enqueue(back, element);
			element = dequeue(front);
		}
		
		frontTop = peekQueue(front);
		stackTop = peekStack(stackItems);
	}
	
	while (peekStack(stackItems)) {
		enqueue(back, pop(stackItems));
	}
	
	free(front);
	front = 0;
	free(stackItems);
	stackItems = 0;
	
	if (swapped) {
		displayQueue(stdout, back);
		printf("\n");
		return sort(back, compare, print);
	}
	
	return back;
}

void *scanInteger(FILE *file) {
	int token = readInt(file);
	integer *newInt = newInteger(token);
	return newInt;
}

void *scanReal(FILE *file) {
	double token = readReal(file);
	real *newRl = newReal(token);
	return newRl;
}

void *scanString(FILE *file) {
	char *token = readString(file);
	if (token == 0) {
		return 0;
	}
	string *newStr = newString(token);
	return newStr;
}

void gcInteger(void *integer) {
	freeInteger(integer);
}

void gcReal(void *real) {
	freeReal(real);
}

void gcString(void *string) {
	freeString(string);
}

int main(int argc, const char * argv[]) {
	Comparator *comp = 0;
	Printer *print = 0;
	Scanner *scan = 0;
	GC *gc = 0;
	FILE *file = stdin;
	
	if (argc < 2) {
		fprintf(stdout, "unknown flag '', valid flags are -d, -r, -s, and -v\n");
		exit(-2);
	}
	
	if (argv[2]) {
		file = fopen(argv[2], "r");
	}
	
	switch (argv[1][1]) {
		case 'v':
			fprintf(stdout, "Greyson M. Wright\n");
			exit(0);
			break;
		case 'd':
			print = displayInteger;
			comp = compareInteger;
			scan = scanInteger;
			gc = gcInteger;
			break;
		case 'r':
			print = displayReal;
			comp = compareReal;
			scan = scanReal;
			gc = gcReal;
			break;
		case 's':
			print = displayString;
			comp = compareString;
			scan = scanString;
			gc = gcString;
			break;
		default:
			fprintf(stdout, "unknown flag '%c', valid flags are -d, -r, -s, and -v\n", argv[1][1]);
			exit(-2);
			break;
	}
	
	queue *inputQueue = newQueue(print);
	void *token = scan(file);
	
	while (!feof(file)) {
		enqueue(inputQueue, token);
		token = scan(file);
	}
	
	fclose(file);
	file = 0;
	
	displayQueue(stdout, inputQueue);
	printf("\n");
	queue *outputQueue = sort(inputQueue, comp, print);
	
	while (peekQueue(outputQueue)) {
		void *value = dequeue(outputQueue);
		gc(value);
	}
	
	return 0;
}
