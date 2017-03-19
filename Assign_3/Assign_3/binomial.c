//
//  binomial.c
//  Assign_3
//
//  Created by Greyson Wright on 3/19/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "binomial.h"

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
	// unimplemented
}

//Bin Heap
int getDegree(BinomialNode *node) {
	return sizeDArray(node->children);
}

BinomialNode *combine(Binomial *binHeap, BinomialNode *x, BinomialNode *y) {
	int degree = 0;
	
	if (binHeap->compare(x->value, y->value) < 0) { //not sure if this should be > or <
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

void merge(Binomial *recipient, DArray *donor) {
	// unimplemented
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
	return node;
}

int sizeBinomial(Binomial *binHeap) {
	return binHeap->size;
}

void deleteBinomial(Binomial *binHeap, BinomialNode *node) {
	// unimplemented
}

void decreaseKeyBinomial(Binomial *binHeap, BinomialNode *node, void *value) {
	// unimplemented
}

void *extractBinomial(Binomial *binHeap) {
	// unimplemented
	return 0;
}

void displayBinomial(FILE *file, Binomial *binHeap) {
	// unimplemented
}

