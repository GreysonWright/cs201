//
//  tree.h
//  Assign_2
//
//  Created by Greyson Wright on 1/31/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include <stdio.h>

typedef int (Comparator)(void*, void*);
typedef void (Display)(FILE *, void *);

typedef struct treenode {
	void *value;
	unsigned color: 1;
	struct treenode *right;
	struct treenode *left;
} treenode;

typedef struct tree {
	treenode *root;
	Display *display;
	Comparator *compare;
} tree;

tree *newTree(Display *display, Comparator *compare);
void insertBST(tree *, void *);
void insertRBT(tree *, void *);
void *removeBST(tree *);
void *removeRBT(tree *);
void *searchTree(tree *, void *);
void displayTree(FILE *, tree *);
#endif /* tree_h */
