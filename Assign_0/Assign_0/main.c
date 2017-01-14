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

//
//static void showItems(sll *items) {
//	printf("The items are ");
//	displaySLL(stdout, items);
//	printf(".\n");
//}
//
//int main(int argc, char **argv) {
//	sll *items = newSLL(displayInteger);
//	showItems(items);
//	insertSLL(items, 0, newInteger(3));                //insert at front
//	insertSLL(items, sizeSLL(items), newInteger(2));   //insert at back
//	insertSLL(items, 1, newInteger(1));                //insert at middle
//	showItems(items);
//	
//	printf("The value ");
//	displayInteger(stdout, removeSLL(items, 0));       //remove from front
//	printf(" was removed.\n");
//	
//	showItems(items);
//	int x = getInteger((integer *) getSLL(items, 0));
//	printf("The first item is %d.\n", x);
//	
//	return 0;
//}

//static void showItems(dll *items) {
//	printf("The items are ");
//	displayDLL(stdout, items);
//	printf(".\n");
//}
//
//int main(int argc, char **argv) {
//	dll *items = newDLL(displayInteger);
//	showItems(items);
//	insertDLL(items, 0 ,newInteger(3));                //insert at front
//	insertDLL(items, sizeDLL(items), newInteger(2));   //insert at back
//	insertDLL(items, 1, newInteger(1));                //insert at middle
//	showItems(items);
//	
//	printf("The value ");
//	displayInteger(stdout, removeDLL(items, 0));       //remove from front
//	printf(" was removed.\n");
//	
//	showItems(items);
//	int x = getInteger((integer *) getDLL(items, 0));
//	printf("The first item is %d.\n", x);
//	
//	return 0;
//}

//static void showItems(stack *s) {
//	printf("The stack is ");
//	displayStack(stdout,s);
//	printf(".\n");
//}
//
//int main(int argc,char **argv) {
//	stack *items = newStack(displayInteger);
//	showItems(items);
//	push(items,newInteger(3));
//	push(items,newInteger(2));
//	showItems(items);
//	printf("The value ");
//	displayInteger(stdout, pop(items));
//	printf(" was popped.\n");
//	showItems(items);
//	return 0;
//}

static void showItems(queue *s) {
	printf("The queue is ");
	displayQueue(stdout, s);
	printf(".\n");
}

int main(int argc,char **argv) {
	queue *items = newQueue(displayInteger);
	showItems(items);
	enqueue(items,newInteger(3));
	enqueue(items,newInteger(2));
	showItems(items);
	printf("The value ");
	displayInteger(stdout, dequeue(items));
	printf(" was dequeued.\n");
	showItems(items);
	return 0;
}
