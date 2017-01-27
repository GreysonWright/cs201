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

typedef int (*Comparator)(void *, void *);
typedef void (*Printer)(FILE *, void *);
typedef void *(*Scanner)(FILE*);

void sort(queue *front, Comparator compare, Printer print) {
	queue *back = newQueue(print);
	stack *stackItems = newStack(print);
	void *element = 0;
	void *frontTop = 0;
	void *stackTop = 0;
	int swapped = 0;
	
	while (peekQueue(front)) {
		element = dequeue(front);
		frontTop = peekQueue(front);
		stackTop = peekStack(stackItems);
		
		if (stackTop && compare(stackTop, element) >= 0) {
			enqueue(back, pop(stackItems));
			enqueue(front, element);
			swapped = 1;
		} else if (frontTop && compare(element, frontTop) < 0) {
			push(stackItems, element);
			swapped = 1;
		} else {
			enqueue(back, element);
		}
	}
	
	while (peekStack(stackItems)) {
		enqueue(back, pop(stackItems));
	}
	
	if (swapped) {
		displayQueue(stdout, back);
		printf("\n");
//		return sort(back, compare, print);
		sort(back, compare, print);
	}
	
//	return back;
}

void *scanInteger(FILE *file) {
	int token = readInt(file);
	if (token == 0) {
		return 0;
	}
	integer *newInt = newInteger(token);
	return newInt;
}

void *scanReal(FILE *file) {
	float token = readReal(file);
	if (token == 0) {
		return 0;
	}
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

int main(int argc, const char * argv[]) {
	Comparator comp = 0;
	Printer print = 0;
	Scanner scan = 0;
	FILE *file = stdin;
	
	if (argc < 2) {
		fprintf(stdout, "unknown flag 'q', valid flags are -d, -r, -s, and -v\n");
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
			break;
		case 'r':
			print = displayReal;
			comp = compareReal;
			scan = scanReal;
			break;
		case 's':
			print = displayString;
			comp = compareString;
			scan = scanString;
			break;
		default:
			fprintf(stdout, "unknown flag 'q', valid flags are -d, -r, -s, and -v\n");
			exit(-2);
			break;
	}
	
	queue *inputQueue = newQueue(print);
//	readChar(file);
	void *token = scan(file);
	
	while (!feof(file)) {
		if (token == 0) {
			break;
		}
		
		enqueue(inputQueue, token);
		readChar(file);
		token = scan(file);
	}
	
	displayQueue(stdout, inputQueue);
	printf("\n");
	sort(inputQueue, comp, print);
	
	return 0;
}
