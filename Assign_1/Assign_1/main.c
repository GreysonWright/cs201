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

typedef int (*Comparator)(void *, void *);
typedef void (*Printer)(FILE *, void *);

void *sort(queue *front, Comparator compare, Printer print) {
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
		return sort(back, compare, print);
	}
	
	return back;
}

int main(int argc, const char * argv[]) {
	Comparator comp = compareInteger;
	Printer print = displayInteger;
	
	if (argc < 2) {
		fprintf(stdout, "unknown flag 'q', valid flags are -d, -r, -s, and -v\n");
		exit(-2);
	}
	
	switch (argv[1][1]) {
		case 'v':
			fprintf(stdout, "Greyson M. Wright\n");
			exit(0);
			break;
		case 'd':
			print = displayInteger;
			comp = compareInteger;
			break;
		case 'r':
			print = displayReal;
			comp = compareReal;
			break;
		case 's':
			print = displayString;
			comp = compareString;
			break;
		default:
			fprintf(stdout, "unknown flag 'q', valid flags are -d, -r, -s, and -v\n");
			exit(-2);
			break;
	}
	
	queue *inputQueue = newQueue(print);
//	enqueue(inputQueue, newInteger(2));
//	enqueue(inputQueue, newInteger(4));
//	enqueue(inputQueue, newInteger(5));
//	enqueue(inputQueue, newInteger(3));
//	enqueue(inputQueue, newInteger(1));
	
	enqueue(inputQueue, newInteger(6));
	enqueue(inputQueue, newInteger(5));
	enqueue(inputQueue, newInteger(4));
	enqueue(inputQueue, newInteger(3));
	enqueue(inputQueue, newInteger(2));
	enqueue(inputQueue, newInteger(1));
	
//	enqueue(inputQueue, newString("goodbye"));
//	enqueue(inputQueue, newString("c is the best"));
//	enqueue(inputQueue, newString("hello"));
//	enqueue(inputQueue, newString("please compile"));
//	enqueue(inputQueue, newString("0"));
	
//	enqueue(inputQueue, newReal(1.5));
//	enqueue(inputQueue, newReal(2.6));
//	enqueue(inputQueue, newReal(3.8));
//	enqueue(inputQueue, newReal(1.9));
	
	displayQueue(stdout, inputQueue);
	printf("\n");
	queue *sortedQueue = sort(inputQueue, comp, print);
	
	return 0;
}
