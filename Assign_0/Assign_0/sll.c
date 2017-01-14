//
//  sll.c
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "sll.h"
#include <stdlib.h>
#include "integer.h"

sllnode *newSLLNode(void *value) {
	sllnode *node = malloc(sizeof *node);
	if (node == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	node->value = value;
	node->next = 0;
	
	return node;
}

//sllnode *findSLLNode(sll *items, int index) {
//	sllnode *node = items->head;
//	
//	for (int i = 0; i < index; i++) {
//		if (node->next == 0) {
//			break;
//		}
//		node = node->next;
//	}
//	
//	return node;
//}

sll *newSLL(void (*d) (FILE *, void *)) { //d is the display function
	sll *items = malloc(sizeof *items);
	
	if (items == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	items->head = 0;
	items->tail = 0;
	items->size = 0;
	items->display = d;
	
	return items;
}

void insertSLL(sll *items, int index, void *value) {
	sllnode *node = items->head;
	sllnode *prevNode = node;
	sllnode *newNode = newSLLNode(value);
	
	items->size++;
	
	if (node == 0) {
		items->head = newNode;
		items->tail = newNode;
		return;
	}
	
	if (index == 0) {
		items->head = newNode;
		newNode->next = node;
		return;
	}
	
	for (int i = 0; i < index; i++) {
		if (node->next == 0) {
			break;
		}
		
		prevNode = node;
		node = node->next;
	}
	
	if (prevNode != node) {
		prevNode->next = newNode;
		newNode->next = node;
	} else {
		newNode->next = node->next;
		node->next = newNode;
	}
	
	if (index >= items->size - 1) {
		items->tail = newNode;
	}
}

void *getSLL(sll *items, int index) {
//	sllnode *node = findSLLNode(items, index);
	sllnode *node = items->head;
	
	for (int i = 0; i < index; i++) {
		if (node->next == 0) {
			break;
		}
		node = node->next;
	}
	
	return node->value;
}

void *removeSLL(sll *items, int index) {
	sllnode *node = items->head;
	sllnode *prevNode = node;
	void *value = 0;
	
	for (int i = 0; i < index; i++) {
		if (node->next == 0) {
			return 0;
		}
		
		prevNode = node;
		node = node->next;
	}
	
	if (index == 0) {
		items->head = node->next;
	}
	
	if (index >= items->size - 1) {
		items->tail = prevNode;
	}
	
	value = node->value;
	prevNode->next = node->next;
	free(node);
	node = 0;
	
	items->size--;
	
	return value;
}

void unionSLL(sll *recipient, sll *donor) {
	if (donor == 0) {
		return;
	}
	
	if (recipient->size < 1) {
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = donor->size;
	} else {
		recipient->tail->next = donor->head;
		recipient->tail = donor->tail;
		recipient->size += donor->size;
	}
	
	donor->head = 0;
	donor->tail = 0;
	donor->size = 0;
}

int sizeSLL(sll *items) {
	return items->size;
}

void displaySLL(FILE *file, sll *items) {
	sllnode *node = items->head;
	
	fprintf(file, "[");
	while (node) {
		integer *value = (integer*) node->value;
		items->display(file, value);
		if (node->next) {
			fprintf(file, ",");
		}
		node = node->next;
	}
	fprintf(file, "]");
}
