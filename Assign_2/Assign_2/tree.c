//
//  tree.c
//  Assign_2
//
//  Created by Greyson Wright on 1/31/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "tree.h"
#include <stdlib.h>

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

treenode *findNode(tree *tree, void *value, Comparator *compare) {
	treenode *node = tree->root;
	
	while (node) {
		if (compare(value, node) < 0) {
			node = node->left;
		} else if (compare(value, node) > 0) {
			node = node->right;
		} else {
			break;
		}
	}
	
	return node;
}

treenode *insertNode(treenode *node, treenode *newNode, Comparator compare) {
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

void *removeBST(tree *tree) {
	return 0;
}

void *removeRBT(tree *tree) {
	return 0;
}

void *searchTree(tree *tree, void *value) {
	treenode *node = findNode(tree, value, tree->compare);
	
	return node;
}

void displayTree(FILE *file, tree *tree) {
	
}
