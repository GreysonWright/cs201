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

void setColor(bstNode *node, int color) {
	rbtValue *nodeValue = node->value;
	nodeValue->color = color;
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
	
	if (parent && parent->parent) {
		if (isLeftChild(parent)) {
			return parent->parent->right;
		}
		return parent->parent->left;
	}
	return 0;
}

bstNode *getSibling(bstNode *node) {
	if (isLeftChild(node)) {
		return node->parent->right;
	}
	return node->parent->left;
}

bstNode *getNephew(bstNode *node) {
	bstNode *sibling = getSibling(node);
	if (isLeftChild(node)) {
		return sibling->right;
	}
	return sibling->left;
}

bstNode *getNiece(bstNode *node) {
	bstNode *sibling = getSibling(node);
	if (isLeftChild(node)) {
		return sibling->left;
	}
	return sibling->right;
}

int isLinear(bstNode *node) {
	return (isLeftChild(node) && isLeftChild(node->parent)) || (!isLeftChild(node) && !isLeftChild(node->parent));
}

void rotateLeft(rbt *tree, bstNode *node) {
	bstNode *right = node->right;
	node->right = right->left;
	
	if (node->right) {
		node->right->parent = node;
	}
	
	right->parent = node->parent;
 
	if (node->parent == 0) {
		tree->tree->root = right;
	} else if(node == node->parent->left) {
		node->parent->left = right;
	} else {
		node->parent->right = right;
	}
 
	right->left = node;
	node->parent = right;
}

void rotateRight(rbt *tree, bstNode *node) {
	bstNode *left = node->left;
	node->left = left->right;
 
	if (node->left) {
		node->left->parent = node;
	}
 
	left->parent = node->parent;
 
	if (node->parent == 0) {
		tree->tree->root = left;
	} else if (node == node->parent->left) {
		node->parent->left = left;
	} else {
		node->parent->right = left;
	}
 
	left->right = node;
	node->parent = left;
}

void rotate(rbt *tree, bstNode *node) {
	if (isLeftChild(node)) {
		rotateRight(tree, node->parent);
	} else {
		rotateLeft(tree, node->parent);
	}
}

void insertFixUp(rbt *tree, bstNode *node) {
	bstNode *parent = node->parent;
	bstNode *uncle = getUncle(node);
	
	while (node != tree->tree->root) {
		if (getColor(parent) == BLACK) {
			break;
		}
		
		if (getColor(uncle) == RED) {
			setColor(parent, BLACK);
			setColor(uncle, BLACK);
			setColor(parent->parent, RED);
			node = parent->parent;
			uncle = getUncle(node);
		} else {
			if (!isLinear(node) && !isLinear(parent)) {
				rotate(tree, node);
				bstNode *tmp = parent;
				parent = node;
				node = tmp;
				uncle = getUncle(node);
			}
			
			setColor(parent, BLACK);
			setColor(parent->parent, RED);
			rotate(tree, parent);
			break;
		}
	}
}

void deletionFixUp(rbt *tree, bstNode *node) {
	while (node != tree->tree->root) {
		if (getColor(node) == RED) {
			break;
		}
		
		bstNode *sibling = getSibling(node);
		bstNode *nephew = getNephew(node);
		bstNode *niece = getNiece(node);
		if (getColor(sibling) == RED) {
			setColor(node->parent, RED);
			setColor(sibling, RED);
			rotate(tree, sibling->parent);
		} else if(getColor(nephew) == RED) {
			setColor(sibling, getColor(node->parent));
			setColor(node->parent, BLACK);
			setColor(nephew, BLACK);
			//rotate
			node = tree->tree->root;
		} else if(getColor(niece) == RED) {
			setColor(niece, BLACK);
			setColor(sibling, RED);
			//rotate
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
	newNode->frequency = 0;
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
	tree->tree = newBST(display, compare);
	return tree;
}

void insertRBT(rbt *tree, void *value) {
	rbtValue *val = newRBTValue(value, tree->tree->display, tree->tree->compare);
	bstNode *node = findBSTNode(tree->tree, val);
	if (node) {
		((rbtValue *)node->value)->frequency++;
		return;
	}
	node = insertBST(tree->tree, val);
	insertFixUp(tree, node);
}

int findRBT(rbt *tree, void *value) {
	return findBST(tree->tree, value);
}

void deleteRBT(rbt *tree, void *value) {
	bstNode *node = findBSTNode(tree->tree, value);
	rbtValue *nodeValue = node->value;
	
	if (nodeValue->frequency > 1) {
		nodeValue->frequency--;
	} else {
		node = swapToLeafBSTNode(node);
		pruneBSTNode(node);
	}
}

void statisticsRBT(rbt *tree, FILE *file) {
	
}

void displayRBT(FILE *file, rbt *tree) {
	displayBST(tree->tree, file);
}
