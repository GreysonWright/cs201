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
#include "comparator.h"

typedef void (Printer)(FILE *, void *);
typedef void *(Scanner)(FILE*);
typedef void (GC)(void *);

void *sort(queue *front, Comparator *compare, Printer *print, int *sorted) {
	queue *back = newQueue(print);
	stack *stackItems = newStack(print);
	void *backTail = 0;
	void *element = dequeue(front);
	void *frontTop = peekQueue(front);
	void *stackTop = peekStack(stackItems);
	
	while (element) {
		if (stackTop && compare(stackTop, element) >= 0) {
			if (backTail && compare(backTail, stackTop) < 0) {
				continue;
			}
			backTail = pop(stackItems);
			enqueue(back, backTail);
			*sorted = 0;
		} else if (frontTop && compare(element, frontTop) < 0) {
			push(stackItems, element);
			element = dequeue(front);
			*sorted = 0;
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
	
	free(stackItems);
	stackItems = 0;
	
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

void setOptions(const char **argv, Comparator **comp, Printer **print, Scanner **scan, GC **gc) {
	switch (argv[1][1]) {
		case 'v':
			fprintf(stdout, "Greyson M. Wright\n");
			exit(0);
			break;
		case 'd':
			*print = displayInteger;
			*comp = intComparator;
			*scan = scanInteger;
			*gc = gcInteger;
			break;
		case 'r':
			*print = displayReal;
			*comp = realComparator;
			*scan = scanReal;
			*gc = gcReal;
			break;
		case 's':
			*print = displayString;
			*comp = stringComparator;
			*scan = scanString;
			*gc = gcString;
			break;
		default:
			fprintf(stdout, "unknown flag '%c', valid flags are -d, -r, -s, and -v\n", argv[1][1]);
			exit(-2);
			break;
	}
}

queue *getFileContent(FILE *file, Scanner *scan, Printer *print) {
	queue *inputQueue = newQueue(*print);
	void *token = scan(file);
	
	while (!feof(file)) {
		enqueue(inputQueue, token);
		token = scan(file);
	}
	
	fclose(file);
	file = 0;
	
	return inputQueue;
}

void freeQueue(queue *items, GC *gc) {
	while (peekQueue(items)) {
		void *value = dequeue(items);
		gc(value);
	}
	
	free(items);
}

int main(int argc, const char *argv[]) {
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
	
	setOptions(argv, &comp, &print, &scan, &gc);
	queue *inputQueue = getFileContent(file, scan, print);
	
	displayQueue(stdout, inputQueue);
	printf("\n");
	
	queue *outputQueue = 0;
	
	int sorted = 0;
	outputQueue = sort(inputQueue, comp, print, &sorted);
	freeQueue(inputQueue, gc);
	inputQueue = outputQueue;
	
	while (!sorted) {
		sorted = 1;
		displayQueue(stdout, outputQueue);
		printf("\n");
		outputQueue = sort(inputQueue, comp, print, &sorted);
		freeQueue(inputQueue, gc);
		inputQueue = outputQueue;
	}
	
	if (outputQueue) {
		freeQueue(outputQueue, gc);
		outputQueue = 0;
	}
	
	return 0;
}
