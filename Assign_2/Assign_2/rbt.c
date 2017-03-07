//
//  rbt.c
//  Assign_2
//
//  Created by Greyson Wright on 2/24/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "rbt.h"

static const int BLACK = 0;
static const int RED =  1;

static int rbtComparator(void *left, void *right) {
	rbtValue *leftVal = left;
	rbtValue *rightVal = right;
	return leftVal->compare(leftVal->value, rightVal->value);
}

static void rbtDisplay(FILE *file, void *value) {
	rbtValue *val = value;
	val->display(file, val->value);
	if (val->frequency > 1) {
		fprintf(file, "-%d", val->frequency);
	}
	
	if (val->color == RED) {
		fprintf(file, "-R");
	} else {
		fprintf(file, "-B");
	}
}

void setColor(bstNode *node, int color) {
	if (node != 0) {
		rbtValue *nodeValue = node->value;
		nodeValue->color = color;
	}
}

int getColor(bstNode *node) {
	if (node == 0) {
		return BLACK;
	}
	return ((rbtValue *)node->value)->color;
}

int isLeftChild(bstNode *node) {
	if (node->parent) {
		return node == node->parent->left;
	}
	return 0;
}

bstNode *getUncle(bstNode *node) {
	bstNode *parent = node->parent;
	
	if (parent != node && parent->parent) {
		if (isLeftChild(parent)) {
			return parent->parent->right;
		}
		return parent->parent->left;
	}
	return 0;
}

bstNode *getSibling(bstNode *node) {
	if (node->parent == node) {
		return 0;
	}
	if (isLeftChild(node)) {
		return node->parent->right;
	}
	return node->parent->left;
}

bstNode *getNephew(bstNode *node) {
	bstNode *sibling = getSibling(node);
	if (sibling == 0) {
		return 0;
	}
	if (isLeftChild(node)) {
		return sibling->right;
	}
	return sibling->left;
}

bstNode *getNiece(bstNode *node) {
	bstNode *sibling = getSibling(node);
	if (sibling == 0) {
		return 0;
	}
	if (isLeftChild(node)) {
		return sibling->left;
	}
	return sibling->right;
}

int isLinear(bstNode *node) {
	return (isLeftChild(node) && isLeftChild(node->parent)) || (!isLeftChild(node) && !isLeftChild(node->parent));
}

void rotateLeft(rbt *tree, bstNode *node) {
	bstNode *parent = node->parent;
	bstNode *left = node->left;

	if (parent->parent != parent) {
		if (isLeftChild(parent)) {
			parent->parent->left = node;
		} else {
			parent->parent->right = node;
		}
		node->parent = parent->parent;
	} else {
		tree->tree->root = node;
		node->parent = node;
	}
	
	parent->right = left;
	if (left) {
		left->parent = parent;
	}
	
	node->left = parent;
	parent->parent = node;
}

void rotateRight(rbt *tree, bstNode *node) {
	bstNode *parent = node->parent;
	bstNode *right = node->right;
	
	if (parent->parent != parent) {
		if (isLeftChild(parent)) {
			parent->parent->left = node;
		} else {
			parent->parent->right = node;
		}
		node->parent = parent->parent;
	} else {
		tree->tree->root = node;
		node->parent = node;
	}
	
	parent->left = right;
	if (right) {
		right->parent = parent;
	}
	
	node->right = parent;
	parent->parent = node;
}

void rotate(rbt *tree, bstNode *node) {
	if (isLeftChild(node)) {
		rotateRight(tree, node);
	} else {
		rotateLeft(tree, node);
	}
}

void insertionFixUp(rbt *tree, bstNode *node) {
	bstNode *parent = node->parent;
	
	while (1) {
		if (node == tree->tree->root) {
			break;
		}
		
		if (getColor(parent) == BLACK) {
			break;
		}
		
		if (getColor(getUncle(node)) == RED) {
			setColor(parent, BLACK);
			setColor(getUncle(node), BLACK);
			setColor(parent->parent, RED);
			node = parent->parent;
			parent = node->parent;
		} else {
			if (!isLinear(node)) {
				rotate(tree, node);
				bstNode *tmp = parent;
				parent = node;
				node = tmp;
			}
			
			setColor(parent, BLACK);
			setColor(parent->parent, RED);
			rotate(tree, parent);
			break;
		}
	}
	setColor(tree->tree->root, BLACK);
}

void deletionFixUp(rbt *tree, bstNode *node) {
	bstNode *sibling = 0;
	bstNode *nephew = 0;
	bstNode *niece = 0;
	
	while (node != tree->tree->root) {
		if (getColor(node) == RED) {
			break;
		}
		
		sibling = getSibling(node);
		nephew = getNephew(node);
		niece = getNiece(node);
		if (getColor(sibling) == RED) {
			setColor(node->parent, RED);
			setColor(sibling, BLACK);
			rotate(tree, sibling);
		} else if(getColor(nephew) == RED) {
			setColor(sibling, getColor(node->parent));
			setColor(node->parent, BLACK);
			setColor(nephew, BLACK);
			rotate(tree, sibling);
			break;
		} else if(getColor(niece) == RED) {
			setColor(niece, BLACK);
			setColor(sibling, RED);
			rotate(tree, niece);
		} else {
			setColor(sibling, RED);
			node = node->parent;
		}
	}
	setColor(node, BLACK);
}

rbtValue *newRBTValue(void *value, void (*display)(FILE *file, void *display), int (*compare)(void *left, void *right)) {
	rbtValue *newNode = newNode = malloc(sizeof *newNode);
	if (newNode == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	newNode->value = value;
	newNode->frequency = 1;
	newNode->color = RED;
	newNode->display = display;
	newNode->compare = compare;
	return newNode;
}

rbt *newRBT(void (*display)(FILE *file, void *display), int (*compare)(void *left, void *right)) {
	rbt *tree = tree = malloc(sizeof *tree);
	if (tree == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	tree->display = display;
	tree->compare = compare;
	tree->tree = newBST(rbtDisplay, rbtComparator);
	tree->size = 0;
	tree->words = 0;
	return tree;
}

void insertRBT(rbt *tree, void *value) {
	rbtValue *val = newRBTValue(value, tree->display, tree->compare);
	bstNode *node = findBSTNode(tree->tree, val);
	
	if (node) {
		((rbtValue *)node->value)->frequency++;
	} else {
		node = insertBST(tree->tree, val);
		insertionFixUp(tree, node);
	}
	tree->size = tree->tree->size;
	tree->words++;
}

int findRBT(rbt *tree, void *value) {
	rbtValue *val =  newRBTValue(value, tree->display, tree->compare);
	bstNode *node = findBSTNode(tree->tree, val);
	
//	free(val->value);
//	free(val);
//	val = 0;
	
	if (node == 0) {
		return 0;
	}
	return ((rbtValue *)node->value)->frequency;
}

void deleteRBT(rbt *tree, void *value) {
	rbtValue *val = newRBTValue(value, tree->display, tree->compare);
	bstNode *node = findBSTNode(tree->tree, val);
	
	if (node == 0) {
		fprintf(stderr, "Value ");
		val->display(stderr, val);
		fprintf(stderr, " not found.\n");
		return;
	}
	
//	free(val->value);
//	free(val);
//	val = 0;
//	
	if (((rbtValue *)node->value)->frequency > 1) {
		((rbtValue *)node->value)->frequency--;
	} else {
		node = swapToLeafBSTNode(node);
		deletionFixUp(tree, node);
		pruneBSTNode(tree->tree, node);
	}
	tree->size = tree->tree->size;
	tree->words--;
	
	if (node) {
//		free(((rbtValue *)node->value)->value);
//		free(node->value);
//		free(node);
//		node = 0;
	}
}

int sizeRBT(rbt *tree) {
	return tree->tree->size;
}

int wordsRBT(rbt *tree) {
	return tree->words;
}

void statisticsRBT(rbt *tree, FILE *file) {
	fprintf(file, "Words/Phrases: %d\n", tree->words);
	statisticsBST(tree->tree, file);
}

void displayRBT(FILE *file, rbt *tree) {
	displayBST(file, tree->tree);
}
