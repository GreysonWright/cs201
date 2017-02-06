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

#define BLACK 0;
#define RED 1;

treenode *newTreeNode(void *value) {
	treenode *newNode = malloc(sizeof *newNode);
	if (newNode == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	newNode->value = value;
	newNode->frequency = 1;
	newNode->color = RED;
	newNode->parent = 0;
	newNode->left = 0;
	newNode->right = 0;
	
	return newNode;
}

tree *newTree(Display *display, Comparator *compare) {
	tree *tree = malloc(sizeof *tree);
	if (tree == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	tree->root = 0;
	tree->display = display;
	tree->compare = compare;
	
	return tree;
}

treenode *findNode(treenode *node, void *value, Comparator *compare) {
	if (node == 0) {
		return node;
	}
	
	if (compare(value, node->value) == 0) {
		return node;
	}
	
	if (compare(value, node->value) < 0) {
		return findNode(node->left, value, compare);
	}
	
	return findNode(node->right, value, compare);
}

treenode *insertNode(treenode *node, void *value, Comparator *compare) {
	treenode *current = node;
	
	if (node == 0) {
		return newTreeNode(value);
	}
	
	while (current) {
		if (compare(value, current->value) < 0) {
			if (current->left) {
				current = current->left;
			} else {
				current->left = newTreeNode(value);
				current->left->parent = current;
				current = current->left;
				break;
			}
		} else if (compare(value, current->value) > 0) {
			if (current->right) {
				current = current->right;
			} else {
				current->right = newTreeNode(value);
				current->right->parent = current;
				current = current->right;
				break;
			}
		} else {
			current->frequency++;
			break;
		}
	}
	
	return current;
}

treenode *extractPredecessor(treenode *node) {
	treenode *predecessor = 0;
	
	if (node->left == 0 && node->right == 0) {
		return predecessor;
	}
	
	if (node->left && node->right) {
		predecessor = node->left;
		
		while (predecessor->right) {
			predecessor = predecessor->right;
		}
		predecessor->parent->right = 0;
	} else if (node->right == 0) {
		predecessor = node->left;
		predecessor->parent->left = 0;
	} else if (node->right) {
		predecessor = node->right;
		predecessor->parent->right = 0;
	}
	
	return predecessor;
}

void insertBST(tree *tree, void *value) {
	treenode *node = insertNode(tree->root, value, tree->compare);
	
	if (tree->root == 0) {
		tree->root = node;
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
	
	if (node->frequency > 1) {
		node->frequency--;
		return;
	}
	
	tmp = extractPredecessor(node);
	
	if (tmp) {
		tmp->parent = node->parent;
		if (tmp->right == 0) {
			tmp->right = node->right;
		}
		
		if (tmp->left == 0) {
			tmp->left = node->left;
		}
	}
	
	if (node->parent) {
		if (node == node->parent->left) {
			node->parent->left = tmp;
		} else {
			node->parent->right = tmp;
		}
	}
	
	if (node == tree->root) {
		tree->root = tmp;
	}
	
	free(node);
	node = 0;
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
		printf("-%d", node->frequency);
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
