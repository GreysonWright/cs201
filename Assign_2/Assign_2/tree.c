//
//  tree.c
//  Assign_2
//
//  Created by Greyson Wright on 1/31/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "tree.h"
#include <stdlib.h>
#include "queue.h"

#define BLACK = 0;
#define RED = 1;

treenode *newRBNode(void *value, unsigned color) {
	treenode *newNode = malloc(sizeof *newNode);
	if (newNode == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	newNode->value = value;
	newNode->color = color;
	newNode->parent = 0;
	newNode->left = 0;
	newNode->right = 0;
	
	return newNode;
}

treenode *newBSNode(void *value) {
	return newRBNode(value, 0);
}

tree *newTree(Display *display, Comparator *compare) {
	tree *newTree = malloc(sizeof *newTree);
	if (newTree == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	newTree->root = 0;
	newTree->display = display;
	newTree->compare = compare;
	
	return newTree;
}

treenode *findNode(treenode *node, void *value, Comparator *compare) {
	if (node == 0) {
		return node;
	}
	
	if (compare(value, node) < 0) {
		return findNode(node->right, value, compare);
	}
	
	return findNode(node->left, value, compare);
}

treenode *insertNode(treenode *node, treenode *newNode, Comparator *compare) {
	if (node == 0) {
		return newNode;
	}
	
	if (compare(newNode->value, node->value) < 0) {
		node->left = insertNode(node->left, newNode, compare);
	} else if (compare(newNode->value, node->value) >= 0) {
		node->right = insertNode(node->right, newNode, compare);
	}
	
	return node;
}

treenode *findPredecessor(treenode *node) {
	treenode *predecessor = 0;
	
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

void insertBST(tree *tree, void *value) {
	treenode *newNode = newBSNode(value);
	if (tree->root == 0) {
		tree->root = insertNode(tree->root, newNode, tree->compare);
	} else {
		insertNode(tree->root, newNode, tree->compare);
	}
}

void insertRBT(tree *tree, void *value) {
	
}

void removeBST(tree *tree, void *value) {
	treenode *node = findNode(tree->root, value, tree->compare);
	treenode *tmp = 0;
	
	if (node == 0) {
		return;
	}
	
	tmp = findPredecessor(node);
	if (tmp->right == 0) {
		tmp->right = node->right;
	}
	
	if (tmp->left == 0) {
		tmp->left = node->left;
	}
	
	tmp->parent = node->parent;
	*node = *tmp;
	
//	if (node == tree->root) {
//		tree->root = tmp;
//	}
	
	free(tmp);
	node = tmp;
}

void removeRBT(tree *tree, void *value) {
	
}

void *searchTree(tree *tree, void *value) {
	treenode *node = findNode(tree->root, value, tree->compare);
	
	return node;
}

void displayTree(FILE *file, tree *tree) {
	treenode *node = tree->root;
	queue *items = newQueue(tree->display);
	while (node) {
		tree->display(file, node->value);
		printf(" ");
		if (node->left) {
			enqueue(items, node->left);
		}
		
		if (node->right) {
			enqueue(items, node->right);
		}
		
		node = dequeue(items);
	}
}
