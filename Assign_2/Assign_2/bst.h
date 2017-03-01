//
//  bst.h
//  Assign_2
//
//  Created by Greyson Wright on 2/14/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef bst_h
#define bst_h

#include <stdio.h>

typedef struct bstNode {
	struct bstNode *parent;
	struct bstNode *left;
	struct bstNode *right;
	void *value;
} bstNode;

typedef struct bst {
	bstNode *root;
	int size;
	void (*display)(FILE *, void *);
	int (*compare)(void *, void *);
} bst;

bst *newBST(void (*)(FILE *, void *), int (*)(void *, void *));
bstNode *insertBST(bst *, void *);
int findBST(bst *, void *);
bstNode *findBSTNode(bst *, void *);
bstNode *swapToLeafBSTNode(bstNode *);
void pruneBSTNode(bst *tree, bstNode *);
int sizeBST(bst *);
void statisticsBST(bst *, FILE *);
void displayBST(bst *, FILE *);
#endif /* bst_h */
