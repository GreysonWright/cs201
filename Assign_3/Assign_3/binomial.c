//
//  binomial.c
//  Assign_3
//
//  Created by Greyson Wright on 3/19/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "binomial.h"
#include "queue.h"

typedef struct BinomialNode {
	void *value;
	DArray *children;
	BinomialNode *parent;
	void (*display)(FILE *, void *);
} BinomialNode;

typedef struct Binomial {
	DArray *rootlist;
	BinomialNode *extreme;
	int size;
	int (*compare)(void *, void *);
	void (*update)(void *, BinomialNode *);
	void (*display)(FILE *, void *);
} Binomial;

// Bin Node
BinomialNode *newBinomialNode(void (*display)(FILE *file, void *value), void *value) {
	BinomialNode *node = malloc(sizeof *node);
	node->value = value;
	node->children = newDArray(display);
	node->parent = 0;
	node->display = display;
	return node;
}

void displayBinomialNode(FILE *file, void *value) {
	BinomialNode *node = value;
	node->display(file, node->value);
	fprintf(file, "-%d", sizeDArray(node->children));
}

//Bin Heap
int getDegree(BinomialNode *node) {
	return sizeDArray(node->children);
}

BinomialNode *combine(Binomial *binHeap, BinomialNode *x, BinomialNode *y) {
	int degree = 0;
	
	if (binHeap->compare(x->value, y->value) < 0) { //most extreme
		degree = getDegree(y);
		setDArray(x->children, degree, y);
		y->parent = x;
		
		return x;
	}
	
	degree = getDegree(x);
	setDArray(y->children, degree, x);
	x->parent = y;
	
	return y;
}

void consolidate(Binomial *binHeap, BinomialNode *node) {
	int degree = getDegree(node);
	
	while (getDArray(binHeap->rootlist, degree)) {
		node = combine(binHeap, node, getDArray(binHeap->rootlist, degree));
		setDArray(binHeap->rootlist, degree, 0);
		degree++;
	}
	setDArray(binHeap->rootlist, degree, node);
}

void merge(Binomial *binHeap, DArray *darray) {
	BinomialNode *node = 0;
	for (int i = 0; i < sizeDArray(darray); i++) {
		node = getDArray(darray, i);
		consolidate(binHeap, node);
		node->parent = node;
		binHeap->size++;
	}
	
	free(darray);
}

BinomialNode *bubbleUp(Binomial *binHeap, BinomialNode *node) {
	if (getDArray(binHeap->rootlist, 0) == node || binHeap->compare(node->value, node->parent->value) > 0) {
		return node;
	}
	
	binHeap->update(node->value, node->parent);
	binHeap->update(node->parent->value, node);
	
	void *tmp = node->value;
	node->value = node->parent->value;
	node->parent->value = tmp;
	
	return bubbleUp(binHeap, node->parent);
}

Binomial *newBinomial(void (*display)(FILE *file, void *value), int (*compare)(void *left,void *right), void (*update)(void *value, BinomialNode *node)) {
	Binomial *binHeap = malloc(sizeof *binHeap);
	binHeap->rootlist = newDArray(display);
	binHeap->extreme = 0;
	binHeap->size = 0;
	binHeap->compare = compare;
	binHeap->update = update;
	binHeap->display = display;
	return binHeap;
}

BinomialNode *insertBinomial(Binomial *binHeap, void *value) {
	BinomialNode *node = newBinomialNode(binHeap->display, value);
	node->parent = node;
	node->children = newDArray(binHeap->display);
	consolidate(binHeap, node);
	binHeap->size++;
	binHeap->extreme = getDArray(binHeap->rootlist, 0);
	return node;
}

int sizeBinomial(Binomial *binHeap) {
	return binHeap->size;
}

void deleteBinomial(Binomial *binHeap, BinomialNode *node) {
	decreaseKeyBinomial(binHeap, node, 0);
	extractBinomial(binHeap);
}

void decreaseKeyBinomial(Binomial *binHeap, BinomialNode *node, void *value) {
	node->value = value;
	node = bubbleUp(binHeap, node);
	if (binHeap->compare(node->value, binHeap->extreme->value) < 0) {
		binHeap->extreme = node;
	}
}

void *extractBinomial(Binomial *binHeap) {
	BinomialNode *extremeNode = binHeap->extreme;
	deleteBinomial(binHeap, extremeNode);
	merge(binHeap, extremeNode->children);
	binHeap->size--;
	
	void *value = extremeNode->value;
	free(extremeNode);
	return value;
}

void enqueueList(queue *items, DArray *list) {
	for (int i = 0; i < sizeDArray(list); i++) {
		enqueue(items, getDArray(list, i));
	}
}

void displayBinomial(FILE *file, Binomial *binHeap) {
	BinomialNode *node = 0;
	queue *queueItems = newQueue(binHeap->display);
	enqueueList(queueItems, binHeap->rootlist);
	enqueue(queueItems, 0);
	int count = 0;
	
	fprintf(file, "%d: ", count++);
	while (sizeQueue(queueItems) > 1) {
		node = dequeue(queueItems);
		
		if (node == 0) {
			node = dequeue(queueItems);
			fprintf(file, "\n");
			fprintf(file, "%d: ", count++);
			enqueue(queueItems, 0);
		}
		
		if (node) {
			displayBinomialNode(file, node);
			if (node->parent != node) {
				fprintf(file, "(");
				displayBinomialNode(file, node->parent);
				fprintf(file, ")");
			}
			
			if (peekQueue(queueItems) != 0) {
				fprintf(file, " ");
			}
			
			enqueueList(queueItems, node->children);
		}
	}
	fprintf(file, "\n");
}

