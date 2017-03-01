//
//  vbst.c
//  Assign_2
//
//  Created by Greyson Wright on 2/22/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "vbst.h"

static int vbstComparator(void *left, void *right) {
	vbstValue *leftVal = left;
	vbstValue *rightVal = right;
	return leftVal->compare(leftVal->value, rightVal->value);
}

static void vbstDisplay(FILE *file, void *value) {
	vbstValue *val = value;
	val->display(file, val->value);
	fprintf(file, "-%d", val->frequency);
}

vbstValue *newVBSTValue(void *value, void (*display)(FILE *file, void *display), int (*compare)(void *left, void *right)) {
	vbstValue *newNode = newNode = malloc(sizeof *newNode);
	if (newNode == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	newNode->value = value;
	newNode->frequency = 1;
	newNode->display = display;
	newNode->compare = compare;
	return newNode;
}

vbst *newVBST(void (*display)(FILE *file, void *display), int (*compare)(void *left, void *right)) {
	vbst *tree = tree = malloc(sizeof *tree);
	if (tree == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	tree->display = display;
	tree->compare = compare;
	tree->tree = newBST(vbstDisplay, vbstComparator);
	tree->words = 0;
	return tree;
}

bstNode *insertVBST(vbst *tree, void *value) {
	vbstValue *val = newVBSTValue(value, tree->display, tree->compare);
	bstNode *node = findBSTNode(tree->tree, val);
	if (node) {
		((vbstValue *)node->value)->frequency++;
		tree->words++;
		return node;
	}
	tree->words++;
	return insertBST(tree->tree, val);
}

bstNode *deleteVBST(vbst *tree, void *value) {
	vbstValue *val = newVBSTValue(value, tree->display, tree->compare);
	bstNode *node = findBSTNode(tree->tree, val);
	
	if (node == 0) {
		fprintf(stderr, "Value ");
		val->display(stderr, val);
		fprintf(stderr, " not found.\n");
		return 0;
	}
	
	if (val->frequency > 1) {
		((vbstValue *)node->value)->frequency--;
	} else {
		node = swapToLeafBSTNode(node);
		pruneBSTNode(tree->tree, node);
	}
	tree->words--;
	return node;
}

int findVBST(vbst *tree, void *value) {
	bstNode *node = findBSTNode(tree->tree, newVBSTValue(value, tree->display, tree->compare));
	return  ((vbstValue *)node->value)->frequency;
}

int sizeVBST(vbst *tree) {
	return tree->tree->size;
}

int wordsVBST(vbst *tree) {
	return tree->words;
}

void statisticsVBST(vbst *tree, FILE *file) {
	fprintf(file, "nWords/Phrases: %d\n", tree->words);
	statisticsBST(tree->tree, file);
}

void displayVBST(FILE *file, vbst *tree){
	displayBST(tree->tree, file);
}
