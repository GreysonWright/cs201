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

struct BinomialNode {
	void *value;
	DArray *children;
	BinomialNode *parent;
	void (*display)(FILE *, void *);
};

struct Binomial {
	DArray *rootlist;
	BinomialNode *extreme;
	int size;
	int (*compare)(void *, void *);
	void (*update)(void *, BinomialNode *);
	void (*display)(FILE *, void *);
};

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
static void enqueueList(queue *items, DArray *list) {
	BinomialNode *node = 0;
	for (int i = 0; i < sizeDArray(list); i++) {
		node = getDArray(list, i);
		if (node) {
			enqueue(items, node);
		}
	}
}

BinomialNode *findMin(Binomial *binHeap, DArray *darray) {
	BinomialNode *current = 0;
	BinomialNode *minVal = getDArray(darray, 0);
	for (int i = 0; i < sizeDArray(darray); i++) {
		current = getDArray(darray, i);
		if (minVal == 0) {
			minVal = current;
		} else if (current && binHeap->compare(current->value, minVal->value) < 0) {
			minVal = getDArray(darray, i);
		}
	}
	return minVal;
}

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
		node->parent = node;
		consolidate(binHeap, node);
	}
	
	for (int i = 0; i < sizeDArray(darray); i++) {
		removeDArray(darray);
	}
	
	free(darray);
}

BinomialNode *bubbleUp(Binomial *binHeap, BinomialNode *node) {
	if (node->parent == node) {
		return node;
	}
		
	if (binHeap->compare(node->value, node->parent->value) >= 0) {
		return node;
	}
	
	if (binHeap->update) {
		binHeap->update(node->value, node->parent);
		binHeap->update(node->parent->value, node);
	}
	
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
	if (binHeap->extreme == 0 || (node->parent == node && binHeap->compare(node->value, binHeap->extreme->value) < 0)) {
		binHeap->extreme = node;
	}
	binHeap->size++;
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
	setDArray(binHeap->rootlist, getDegree(extremeNode), 0);
	void *value = 0;
	merge(binHeap, extremeNode->children);
	binHeap->size--;
	value = extremeNode->value;
	if (binHeap->update) {
		binHeap->update(extremeNode->value, 0);
	}
	free(extremeNode);
	extremeNode = 0;
	binHeap->extreme = findMin(binHeap, binHeap->rootlist);
	return value;
}

void displayBinomial(FILE *file, Binomial *binHeap) {
	BinomialNode *node = 0;
	queue *queueItems = newQueue(binHeap->display);
	int count = 0;
	
	fprintf(file, "%d :", count++);
	if (sizeBinomial(binHeap) == 0) {
		fprintf(file, "\n----");
	}
	
	for (int i = 0; i < sizeDArray(binHeap->rootlist); i++) {
		node = getDArray(binHeap->rootlist, i);
		if (node) {
			fprintf(stdout, " ");
			enqueue(queueItems, node);
			enqueue(queueItems, 0);
		}
		while (sizeQueue(queueItems) > 1) {
			node = dequeue(queueItems);
			
			if (node == 0) {
				node = dequeue(queueItems);
				fprintf(file, "\n");
				fprintf(file, "%d : ", count++);
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
				} else if (sizeDArray(node->children) == 0) {
					count = 0;
					fprintf(file, "\n----");
				}
				
				enqueueList(queueItems, node->children);
			}
		}
	}
	fprintf(file, "\n");
}

