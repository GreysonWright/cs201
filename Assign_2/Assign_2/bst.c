//
//  bst.c
//  Assign_2
//
//  Created by Greyson Wright on 2/14/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "bst.h"
#include "queue.h"

bstNode *findPredecessor(bstNode *node) {
	bstNode *predecessor = 0;
	
	if (node->left == 0 && node->right == 0) {
		return predecessor;
	}
	
	if (node->left && node->right) {
		predecessor = node->left;
		
		while (predecessor->right) {
			predecessor = predecessor->right;
		}
	} else if (node->right == 0) {
		predecessor = node->left;
	} else if (node->right) {
		predecessor = node->right;
	}
	
	return predecessor;
}

bstNode *newBSTNode(void *value) {
	bstNode *newNode = newNode = malloc(sizeof *newNode);
	if (newNode == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	newNode->parent = 0;
	newNode->left = 0;
	newNode->right = 0;
	newNode->value = value;
	return newNode;
}

bst *newBST(void (*display)(FILE *file, void *display), int (*compare)(void *left, void *right)) {
	bst *items = items = malloc(sizeof *items);
	if (items == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	items->root = 0;
	items->display = display;
	items->compare = compare;
	return items;
}

bstNode *insertBST(bst *items, void *value) {
	bstNode *node = items->root;
	bstNode *current = node;
	bstNode *newNode = newBSTNode(value);
	
	if (node == 0) {
		items->root = newNode;
		return newNode;
	}
	
	while (current) {
		if (items->compare(value, current->value) < 0) {
			if (current->left) {
				current = current->left;
			} else {
				current->left = newNode;
				newNode->parent = current;
				current = current->left;
				break;
			}
		} else { //if (items->compare(value, current->value) > 0) {
			if (current->right) {
				current = current->right;
			} else {
				current->right = newNode;
				newNode->parent = current;
				current = current->right;
				break;
			}
		}
	}
	
	return current;
}

int findBST(bst *items, void *value) {
	return findBSTNode(items, value) != 0;
}

bstNode *findBSTNode(bst *items, void *value) {
	bstNode *node = items->root;
	bstNode *current = node;
	
	if (node == 0) {
		return node;
	}
	
	while (current) {
		if (items->compare(value, current->value) < 0) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	
	return current;
}

bstNode *swapToLeafBSTNode(bstNode *node) {
	bstNode *predecessor = findPredecessor(node);
	if (predecessor) {
		void *tmp = node->value;
		node->value = predecessor->value;
		predecessor->value = tmp;
	}
	
	return predecessor;
}

void pruneBSTNode(bstNode *node) {
	if (node->parent) {
		if (node->parent->left == node) {
			node->parent->left = 0;
		} else {
			node->parent->right = 0;
		}
	}
}

void statisticsBST(bst *items, FILE *file) {
	
}

void displayBST(bst *items, FILE *file) {
	bstNode *node = items->root;
	queue *queueItems = newQueue(items->display);
	enqueue(queueItems, node);
	enqueue(queueItems, 0);
	
	while (sizeQueue(queueItems) > 1) {
		node = dequeue(queueItems);
		
		if (node == 0) {
			node = dequeue(queueItems);
			printf("\n");
			enqueue(queueItems, 0);
		}
		
		if (node) {
			items->display(file, node->value);
			printf(" ");
			
			if (node->left) {
				enqueue(queueItems, node->left);
			}
			
			if (node->right) {
				enqueue(queueItems, node->right);
			}
		}
	}
}
