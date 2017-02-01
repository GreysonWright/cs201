//
//  tree.c
//  Assign_2
//
//  Created by Greyson Wright on 1/31/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "tree.h"
#include <stdlib.h>

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

tree *newTree(void (*display)(FILE *, void *)) {
	tree *newTree = malloc(sizeof *newTree);
	if (newTree == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	newTree->root = 0;
	newTree->display = display;
	
	return newTree;
}

treenode *findNode(tree *tree, void *value, Comparator compare) {
	treenode *node = tree->root;
	
	if (compare(value, node) < 0) {
		node = findNode(<#tree *tree#>, <#void *value#>, <#Comparator compare#>)
	}
	
	if (compare(value, node) > 0) {
		
	}
	
	return node;
}

void insertBST(tree *tree, void *value, Comparator compare) {
	treenode *root = tree->root;
	
	if (root == 0) {
		tree->root = newBSNode(value);
		return;
	}
	
	if (compare(value, root->value) < 0) {
		
	} else {
		
	}
	
}

void insertRBT(tree *tree, void *value, Comparator compare) {
	
}

void *removeBST(tree *tree) {
	return 0;
}

void *removeRBT(tree *tree) {
	return 0;
}

void displayTree(FILE *file, tree *tree) {
	
}
