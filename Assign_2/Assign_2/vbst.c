//
//  vbst.c
//  Assign_2
//
//  Created by Greyson Wright on 2/22/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "vbst.h"

vbstValue *newVBSTValue(void *value, void (*display)(FILE *file, void *display), int (*compare)(void *left, void *right)) {
	vbstValue *newNode = newNode = malloc(sizeof *newNode);
	if (newNode == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	newNode->value = value;
	newNode->frequency = 0;
	return newNode;
}

vbst *newVBST(void (*display)(FILE *file, void *display), int (*compare)(void *left, void *right)) {
	vbst *tree = tree = malloc(sizeof *tree);
	if (tree == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	tree->store = newBST(display, compare);
	return tree;
}

bstNode *insertVBST(vbst *tree, void *value) {
	bstNode *node = findBSTNode(tree->store, value);
	if (node) {
		((vbstValue *)node->value)->frequency++;
		return node;
	}
	vbstValue *val = newVBSTValue(value, tree->store->display, tree->store->compare);
	return insertBST(tree->store, val);
}

bstNode *deleteVBST(vbst *tree, void *value) {
	bstNode *node = findBSTNode(tree->store, value);
	node = swapToLeafBSTNode(node);
	pruneBSTNode(node);
	
	return node;
}

int findVBST(vbst *tree, void *value) {
	return findBST(tree->store, value);
}

void statisticsVBST(vbst *tree, FILE *file) {
	
}

void displayVBST(vbst *tree, FILE *file){
	displayBST(tree->store, file);
}
