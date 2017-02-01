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

typedef int (Comparator)(void*,void*);

typedef struct treenode {
	void *value;
	unsigned color: 1;
	struct treenode *right;
	struct treenode *left;
} treenode;

typedef struct tree {
	treenode *root;
	void (*display)(FILE *, void *);
} tree;

tree *newTree(void (*)(FILE *, void *));
void insertBST(tree *, void *, Comparator *);
void insertRBT(tree *, void *, Comparator *);
void *removeBST(tree *);
void *removeRBT(tree *);
void *searchTree(tree *, void *, Comparator *);
void displayTree(FILE *, tree *);
#endif /* tree_h */
