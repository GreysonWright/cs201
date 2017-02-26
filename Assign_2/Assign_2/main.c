//
//  main.c
//  Assign_2
//
//  Created by Greyson Wright on 1/31/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "bst.h"
#include "vbst.h"
#include "rbt.h"
#include "comparator.h"

void vbstIntDisplay(FILE *file, void *integer) {
	vbstValue *intVal = integer;
	displayInteger(file, intVal->value);
}

void vbstRealDisplay(FILE *file, void *real) {
	vbstValue *realVal = real;
	displayInteger(file, realVal->value);
}

void vbstStringDisplay(FILE *file, void *string) {
	vbstValue *stringVal = string;
	displayInteger(file, stringVal->value);
}

void rbtIntDisplay(FILE *file, void *integer) {
	rbtValue *intVal = integer;
	displayInteger(file, intVal->value);
}

void rbtRealDisplay(FILE *file, void *real) {
	rbtValue *realVal = real;
	displayInteger(file, realVal->value);
}

void rbtStringDisplay(FILE *file, void *string) {
	rbtValue *stringVal = string;
	displayInteger(file, stringVal->value);
}

int main(int argc, const char * argv[]) {
//	vbst *bst = newVBST(vbstIntDisplay, vbstIntComparator);
//	insertVBST(bst, newInteger(10));
//	insertVBST(bst, newInteger(10));
//	insertVBST(bst, newInteger(5));
//	insertVBST(bst, newInteger(20));
//	insertVBST(bst, newInteger(2));
//	insertVBST(bst, newInteger(17));
//	insertVBST(bst, newInteger(9));
//	removeBST(bst, newInteger(10));
//	removeBST(bst, newInteger(10));
//	removeBST(bst, newInteger(9));
//	removeBST(bst, newInteger(2));
//	displayVBST(bst, stdout);
	
//	tree *rbt = newTree(displayInteger, compareInteger);
//	insertRBT(rbt, newInteger(10));
//	insertRBT(rbt, newInteger(9));
//	insertRBT(rbt, newInteger(8));
//	displayTree(stdout, rbt);

	rbt *tree = newRBT(rbtIntDisplay, rbtIntComparator);
	insertRBT(tree, newInteger(100));
	insertRBT(tree, newInteger(20));
	insertRBT(tree, newInteger(21));
	insertRBT(tree, newInteger(19));
	deleteRBT(tree, newInteger(100));
//	insertRBT(tree, newInteger(10));
//	insertRBT(tree, newInteger(10));
//	insertRBT(tree, newInteger(5));
//	insertRBT(tree, newInteger(20));
//	insertRBT(tree, newInteger(2));
//	insertRBT(tree, newInteger(17));
//	deleteRBT(tree, newInteger(10));
//	deleteRBT(tree, newInteger(10));
//	deleteRBT(tree, newInteger(17));
	displayRBT(stdout, tree);
	
	return 0;
}
