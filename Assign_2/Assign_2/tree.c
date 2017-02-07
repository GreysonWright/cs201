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

static const int BLACK = 0;
static const int RED =  1;

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

void insertBST(tree *items, void *value) {
	treenode *node = insertNode(items->root, value, items->compare);
	
	if (items->root == 0) {
		items->root = node;
	}
}

int getColor(treenode *node) {
	if (node == 0) {
		return BLACK;
	}
	return node->color;
}

int isLeftChild(treenode *node) {
	if (node->parent) {
		return node == node->parent->left;
	}
	return 0;
}

treenode *getUncle(treenode *node) {
	treenode *parent = node->parent;
	
	if (parent && parent->parent) {
		if (isLeftChild(parent)) {
			return parent->parent->right;
		}
		return parent->parent->left;
	}
	return 0;
}

int isLinear(treenode *node) {
	return (isLeftChild(node) && isLeftChild(node->parent)) || (!isLeftChild(node) && !isLeftChild(node->parent));
}

void rotateLeft(tree *items, treenode *node) {	
	treenode *right = node->right;
	node->right = right->left;
	
	if (node->right) {
		node->right->parent = node;
	}
	
	right->parent = node->parent;
 
	if (node->parent == 0) {
		items->root = right;
	} else if(node == node->parent->left) {
		node->parent->left = right;
	} else {
		node->parent->right = right;
	}
 
	right->left = node;
	node->parent = right;
}

void rotateRight(tree *items, treenode *node) {
	treenode *left = node->left;
	node->left = left->right;
 
	if (node->left) {
		node->left->parent = node;
	}
 
	left->parent = node->parent;
 
	if (node->parent == 0) {
		items->root = left;
	} else if (node == node->parent->left) {
		node->parent->left = left;
	} else {
		node->parent->right = left;
	}
 
	left->right = node;
	node->parent = left;
}

void rotate(tree *items, treenode *node) {
	if (isLeftChild(node)) {
		rotateRight(items, node->parent);
	} else {
		rotateLeft(items, node->parent);
	}
}

void insertFixUp(tree *items, treenode *node) {
	treenode *parent = node->parent;
	treenode *uncle = getUncle(node);
	
	while (node != items->root) {
		if (getColor(parent) == BLACK) {
			break;
		}
		
		if (getColor(uncle) == RED) {
			parent->color = BLACK;
			uncle->color = BLACK;
			parent->parent->color = RED;
			node = parent->parent;
		} else {
			if (!isLinear(node) && !isLinear(parent)) {
				rotate(items, node);
				treenode *tmp = parent;
				parent = node;
				node = tmp;
			}
			
			parent->color = BLACK;
			parent->parent->color = RED;
			rotate(items, parent);
			break;
		}
	}
}

void insertRBT(tree *items, void *value) {
	treenode *node = insertNode(items->root, value, items->compare);
	insertFixUp(items, node);
	
	if (items->root == 0) {
		node->color = BLACK;
		items->root = node;
	}
}

void removeBST(tree *items, void *value) {
	treenode *node = findNode(items->root, value, items->compare);
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
	
	if (node == items->root) {
		items->root = tmp;
	}
	
	free(node);
	node = 0;
}

void removeRBT(tree *items, void *value) {
	
}

void *searchTree(tree *items, void *value) {
	treenode *node = findNode(items->root, value, items->compare);
	
	return node;
}

void displayTree(FILE *file, tree *items) {
	treenode *node = items->root;
	queue *queueItems = newQueue(items->display);
	while (node) {
		items->display(file, node->value);
		printf("-%d", isLeftChild(node));
		printf(" ");
		if (node->left) {
			enqueue(queueItems, node->left);
		}
		
		if (node->right) {
			enqueue(queueItems, node->right);
		}
		
		node = dequeue(queueItems);
	}
}
