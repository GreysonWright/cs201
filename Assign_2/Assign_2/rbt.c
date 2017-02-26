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
	
	if (parent && parent->parent) {
		if (isLeftChild(parent)) {
			return parent->parent->right;
		}
		return parent->parent->left;
	}
	return 0;
}

bstNode *getSibling(bstNode *node) {
	if (node->parent == 0) {
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

	if (parent->parent) {
		if (isLeftChild(parent)) {
			parent->parent->left = node;
		} else {
			parent->parent->right = node;
		}
		node->parent = parent->parent;
	} else {
		tree->tree->root = node;
		node->parent = 0;
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
	
	if (parent->parent) {
		if (isLeftChild(parent)) {
			parent->parent->left = node;
		} else {
			parent->parent->right = node;
		}
		node->parent = parent->parent;
	} else {
		tree->tree->root = node;
		node->parent = 0;
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

void insertFixUp(rbt *tree, bstNode *node) {
	bstNode *parent = node->parent;
	
	while (node != tree->tree->root) {
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
			if (!isLinear(node) && !isLinear(parent)) {
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
			rotate(tree, sibling);
		} else if(getColor(nephew) == RED) {
			setColor(sibling, getColor(node->parent));
			setColor(node->parent, BLACK);
			setColor(nephew, BLACK);
			rotate(tree, sibling);
			break;
		} else if(getColor(niece) == RED) {
			setColor(niece, BLACK);
			setColor(sibling->parent, RED);
			rotate(tree, niece);
		} else {
			setColor(sibling->parent, RED);
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
	rbtValue *val = newRBTValue(value, tree->tree->display, tree->tree->compare);
	bstNode *node = findBSTNode(tree->tree, val);
	if (node == 0) {
		fprintf(stderr, "Value ");
		val->display(stderr, val);
		fprintf(stderr, " not found.\n");
		return;
	}
	if (((rbtValue *)node->value)->frequency > 1) {
		((rbtValue *)node->value)->frequency--;
	} else {
		node = swapToLeafBSTNode(node);
		deletionFixUp(tree, node);
		pruneBSTNode(node);
	}
}

void statisticsRBT(rbt *tree, FILE *file) {
	
}

void displayRBT(FILE *file, rbt *tree) {
	displayBST(tree->tree, file);
}
