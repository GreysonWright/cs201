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

static int min(int right, int left) {
	return right > left ? left : right;
}

static int max(int right, int left) {
	return right < left ? left : right;
}

static int isLeaf(bstNode *node) {
	if (node->left || node->right) {
		return 0;
	}
	
	return 1;
}

static int isRoot(bstNode *node) {
	if (node->parent == node) {
		return 1;
	}
	
	return 0;
}

static int isLeftChild(bstNode *node) {
	if (node->parent) {
		return node == node->parent->left;
	}
	return 0;
}

static int findMinHeight(bstNode *node) {
	if (node == 0) {
		return 0;
	}
	
	int right = findMinHeight(node->right);
	int left = findMinHeight(node->left);
	
	return min(right, left) + 1;
}

static int findMaxHeight(bstNode *node) {
	if (node == 0) {
		return 0;
	}
	
	int right = findMaxHeight(node->right);
	int left = findMaxHeight(node->left);
	
	return max(right, left) + 1;
}

bstNode *findPredecessor(bstNode *node) {
	bstNode *predecessor = 0;
	
	if (node->left == 0 && node->right == 0) {
		return predecessor;
	}
	
	if (node->left) {
		predecessor = node->left;
		
		while (predecessor->right) {
			predecessor = predecessor->right;
		}
	} else if (node->right) {
		predecessor = node->right;
		
		while (predecessor->left) {
			predecessor = predecessor->left;
		}
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
	bst *tree = tree = malloc(sizeof *tree);
	if (tree == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	tree->root = 0;
	tree->size = 0;
	tree->display = display;
	tree->compare = compare;
	return tree;
}

bstNode *insertBST(bst *tree, void *value) {
	bstNode *node = tree->root;
	bstNode *current = node;
	bstNode *newNode = newBSTNode(value);
	tree->size++;
	
	if (node == 0) {
		tree->root = newNode;
		newNode->parent = newNode;
		return newNode;
	}
	
	while (current) {
		if (tree->compare(value, current->value) < 0) {
			if (current->left) {
				current = current->left;
			} else {
				current->left = newNode;
				newNode->parent = current;
				current = current->left;
				break;
			}
		} else { //if (tree->compare(value, current->value) > 0) {
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

int findBST(bst *tree, void *value) {
	return findBSTNode(tree, value) != 0;
}

bstNode *findBSTNode(bst *tree, void *value) {
	bstNode *node = tree->root;
	bstNode *current = node;
	
	if (node == 0) {
		return node;
	}
	
	while (current) {
		if (tree->compare(value, current->value) < 0) {
			current = current->left;
		} else if (tree->compare(value, current->value) > 0) {
			current = current->right;
		} else {
			return current;
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
	} else {
		return node;
	}
	
	if (predecessor && (predecessor->left || predecessor->right)) {
		return swapToLeafBSTNode(predecessor);
	}
	
	return predecessor;
}

int sizeBST(bst *tree) {
	return tree->size;
}

void pruneBSTNode(bst* tree, bstNode *node) {
	if (node->parent != node) {
		if (node->parent->left == node) {
			node->parent->left = 0;
		} else {
			node->parent->right = 0;
		}
	} else {
		tree->root = 0;
	}
}

void statisticsBST(bst *tree, FILE *file) {
	int minDepth = findMinHeight(tree->root);
	int maxDepth = findMaxHeight(tree->root);
	fprintf(file, "Nodes: %d\nMinimum depth: %d\nMaximum depth: %d\n", tree->size, minDepth, maxDepth);
}

void displayBST(FILE * file, bst *tree) {
	bstNode *node = tree->root;
	queue *queueItems = newQueue(tree->display);
	enqueue(queueItems, node);
	enqueue(queueItems, 0);
	int count = 0;
	
	if (node == 0) {
		fprintf(file, "%d:\n", count);
		return;
	}

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
			if (isLeaf(node)) {
				fprintf(file, "=");
			}
			
			tree->display(file, node->value);
			fprintf(file, "(");
			tree->display(file, node->parent->value);
			fprintf(file, ")");
			
			if (isRoot(node)) {
				fprintf(file, "-");
			} else {
				if (isLeftChild(node)) {
					fprintf(file, "-l");
				} else {
					fprintf(file, "-r");
				}
			}
			
			if (peekQueue(queueItems) != 0) {
				fprintf(file, " ");
			}
			
			if (node->left) {
				enqueue(queueItems, node->left);
			}
			
			if (node->right) {
				enqueue(queueItems, node->right);
			}
		}
	}
	fprintf(file, "\n");
}
