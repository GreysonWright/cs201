//
//  dll.c
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "dll.h"
#include <stdlib.h>
#include "integer.h"

dllnode *newDLLNode(void *value) {
	dllnode *node = malloc(sizeof *node);
	if (node == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	node->value = value;
	node->prev = 0;
	node->next = 0;
	
	return node;
}

dllnode *findDLLNode(dll *items, int index) {
	dllnode *node = items->head;
	
	for (int i = 0; i < index - 1; i++) {
		if (node->next == 0) {
			break;
		}
		node = node->next;
	}
	
	return node;
}

dll *newDLL(void (*d) (FILE *, void *)) { //d is the display function
	dll *items = malloc(sizeof *items);
	
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

void insertDLL(dll *items, int index, void *value) {
	dllnode *node = items->head;
	dllnode *newNode = newDLLNode(value);
	
	items->size++;
	
	if (node == 0) {
		items->head = newNode;
		items->tail = newNode;
		return;
	}
	
	node = findDLLNode(items, index);
	
	newNode->next = node->next;
	node->next = newNode;
	newNode->prev = node;
	if (newNode->next) {
		newNode->next->prev = newNode;
	}
	
	if (index == items->size - 1) {
		items->tail = newNode;
	}
}

void *getDLL(dll *items, int index) {
	dllnode *node = findDLLNode(items, index);
	
	return node->value;
}

void *removeDLL(dll *items, int index) {
	dllnode *node = node = findDLLNode(items, index);
	void *value = node->value;
	
	if (index == 0) {
		items->head = node->next;
	}
	
	if (index == items->size) {
		items->tail = node->prev;
	}
	
	node->prev = node->next;
	free(node);
	node = 0;
	
	return value;
}

void unionDLL(dll *recipient, dll *donor) {
	dll *donorCPY = newDLL(0);
	donorCPY = &(*donor);
	
	recipient->tail->next = donorCPY->head;
	donorCPY->head->prev = recipient->tail;
	recipient->tail = donor->tail;
	
	donorCPY = 0;
}

int sizeDLL(dll *items) {
	return items->size;
}

void displayDLL(FILE *file, dll *items) {
	dllnode *node = items->head;
	
	fprintf(file, "[");
	while (node) {
		integer *value = (integer*) node->value;
		fprintf(file, "%d", value->value);
		if (node->next) {
			fprintf(file, ",");
		}
		node = node->next;
	}
	fprintf(file, "]");
}
