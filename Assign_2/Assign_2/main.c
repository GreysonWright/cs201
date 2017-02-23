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

int main(int argc, const char * argv[]) {
	vbst *bst = newVBST(displayInteger, compareInteger);
	insertVBST(bst, newInteger(10));
	insertVBST(bst, newInteger(10));
	insertVBST(bst, newInteger(5));
	insertVBST(bst, newInteger(20));
	insertVBST(bst, newInteger(2));
	insertVBST(bst, newInteger(17));
	insertVBST(bst, newInteger(9));
//	removeBST(bst, newInteger(10));
//	removeBST(bst, newInteger(10));
//	removeBST(bst, newInteger(9));
//	removeBST(bst, newInteger(2));
	displayVBST(bst, stdout);
	
//	tree *rbt = newTree(displayInteger, compareInteger);
//	insertRBT(rbt, newInteger(10));
//	insertRBT(rbt, newInteger(9));
//	insertRBT(rbt, newInteger(8));
//	displayTree(stdout, rbt);
	
	return 0;
}
